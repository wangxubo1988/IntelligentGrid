#include <stdio.h>
#include "IEC103.h"
#include <string.h>
#include <FuncPKG.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <limits.h>
#include <time.h>
#include <netdb.h>
#include <misc.h>
#include <stdlib.h>
#include <log.h>
#include <mysocket.h>
#include <math.h>

mysocket *IEC103Socket;

int IEC103Sleep()
{
        if(deviceMgmt->systemconfig.server.Interval > 5)
        {
                sleep(deviceMgmt->systemconfig.server.Interval);
        }
        else
        {
                sleep(5);
        }

        return 0;
}

int IEC103Init()
{
        IEC103Socket = mysocketCreate();
        return 0;
}

int IEC103UnInitialize()
{
        mysocketDestroy(IEC103Socket);
        return 0;
}



int IEC103ASDU10(char buf[], int datalen, int datanum)  //���ݷ���
{
        buf[0] = 0x68;
        buf[1] = 4 + 9 + datalen;
        buf[6 + 0] = 0x0a;
        buf[6 + 1] = 0x81;
        buf[6 + 2] = 0x28;
        buf[6 + 5] = 0xfe;
        buf[6 + 6] = 0xf1;
        buf[6 + 7] = 0;
        buf[6 + 8] = datanum<<2;

        return datanum;
}

int IEC103ASDU8(char buf[])  //��ֹ
{
        buf[0] = 0x68;
        buf[1] = 4 + 8;
        buf[6 + 0] = 0x08;
        buf[6 + 1] = 0x81;
        buf[6 + 2] = 0x09;
        buf[6 + 5] = 0xff;
        buf[6 + 6] = 0x00;
        buf[6 + 7] = 0x00;

        return 0;
}



int SetIECTime(char buf[], time_t time)
{
        struct tm *gm = gmtime(&time);

        memset(buf, 0, sizeof(buf));
        buf[0] = (gm->tm_sec * 1000) & 0xff;
        buf[1] = (gm->tm_sec * 1000) >> 8;
        buf[2] = gm->tm_min;
        buf[3] = gm->tm_hour;
        buf[4] = ((gm->tm_wday==0?7:gm->tm_wday)<<5) | gm->tm_mday;
        buf[5] = gm->tm_mon + 1;
        buf[6] = gm->tm_year % 100;

        return 0;
}

time_t GetIECTime(char buf[])
{
        struct tm gm;
        char tmp[50];
        bzero(&gm, sizeof(gm));


        int msec = (buf[1] * 256 + buf[0]);
        sprintf(tmp, "%d", msec);
        double dsec = atof(tmp);
        gm.tm_sec = dsec/1000;

        gm.tm_min = buf[2];

        gm.tm_hour = buf[3];

        gm.tm_mday = buf[4] & 0x1f;

        gm.tm_mon = buf[5] - 1;

        gm.tm_year = 100 + buf[6];

        gm.tm_isdst=0;

        time_t timep = mktime(&gm);
        PrintfGreen("%s", asctime(gmtime(&timep)));
        return timep;
}

int IEC103DataPKG\
        (struct datastoreunit dataunit[], struct IEC103DataUnit IEC103data[], int num)
{
        int i;

        union Data{
                char ch[4];
                float f;
                }data;
        memset(IEC103data, 0, num * sizeof(struct IEC103DataUnit));
        for(i=0;i<num;i++)
        {
                IEC103data[i].buffer[2] = 1;
                IEC103data[i].buffer[3] = 7;
                IEC103data[i].buffer[4] = 4;
                IEC103data[i].buffer[5] = 4;
                SetIECTime(&IEC103data[i].buffer[6], dataunit[i].time);
                data.f = dataunit[i].data;
                PrintfRed("data:%.2f", data.f);
                StrNCpy(&IEC103data[i].buffer[13], data.ch, 4);
                IEC103data[i].buffer[22] = dataunit[i].sensorID >> 8;
                IEC103data[i].buffer[21] = dataunit[i].sensorID & 0xff;
        }

        return 0;
}

int IEC103TimeSync(char buf[], int len)
{
        if(buf[6] == 0x67)
        {
                time_t synctime = GetIECTime(buf + 15);
                time_t nowtime = time(NULL);
                if(abs(synctime - nowtime) > 20)
                {
                        SyncTime(synctime);
                }
        }
        return 0;
}


int IEC103ReportData(struct IEC103DataUnit IEC103data[], int datanum)
{
        char buffer[500];
        int count = 0;
        int i;
        
        while(datanum > 0)
        {
                memset(buffer, 0, 500);
                StrNCpy(buffer + 15, IEC103data[count].buffer,  \
                        (datanum>10?10:datanum)*sizeof(struct IEC103DataUnit));
				
                count += IEC103ASDU10(buffer, (datanum>10?10:datanum) * \
                        sizeof(struct IEC103DataUnit), datanum>10?10:datanum);
                IEC103Socket->len = \
                        (datanum>10?10:datanum) * sizeof(struct IEC103DataUnit) + 15;
                PrintfGreen("IEC103Socket->len:%d", IEC103Socket->len);
                StrNCpy(IEC103Socket->buffer, buffer, IEC103Socket->len);
                
                PrintfGreen("IEC103 send");
                for(i=0;i<IEC103Socket->len;i++)
                        printf("%02x ", IEC103Socket->buffer[i]);
                printf("\n");
                IEC103Socket->open(IEC103Socket);
                IEC103Socket->writen(IEC103Socket);
                IEC103Socket->len = 1000;
                IEC103Socket->readn(IEC103Socket);
                IEC103Socket->close(IEC103Socket);
                if(IEC103Socket->len > 0)
                {
                        PrintfRed("IEC103 rec");
                        for(i=0;i<IEC103Socket->len;i++)
                                printf("%02x ", IEC103Socket->buffer[i]);
                        printf("\n");
                }
                datanum -= count;
                
        }
        memset(buffer, 0, 500);
        IEC103ASDU8(buffer);
        IEC103Socket->len = 14;
        PrintfGreen("IEC103 send:");
        StrNCpy(IEC103Socket->buffer, buffer, IEC103Socket->len);
        for(i=0;i<IEC103Socket->len;i++)
        {
                printf("%02x ", IEC103Socket->buffer[i]);
        }
        printf("\n");
        IEC103Socket->open(IEC103Socket);
        IEC103Socket->writen(IEC103Socket);
        
        IEC103Socket->len = 1000;
        
        IEC103Socket->readn(IEC103Socket);
        IEC103Socket->close(IEC103Socket);
        if(IEC103Socket->len > 0)
        {
                
                PrintfRed("IEC103 rec");
                for(i=0;i<IEC103Socket->len;i++)
                        printf("%02x ", IEC103Socket->buffer[i]);
                printf("\n");
                IEC103TimeSync(IEC103Socket->buffer, IEC103Socket->len);
                
        }
        

        return IEC103Socket->len > 0;
        
}

int IEC103Execute()
{
        int datanum = dataStore->reportgetcount(dataStore, "report");

        strcpy(IEC103Socket->ip, deviceMgmt->systemconfig.server.IP);
        PrintfGreen("IEC103  Connection--%s:%d", IEC103Socket->ip, IEC103Socket->port);
        IEC103Socket->port = deviceMgmt->systemconfig.server.DataPort;
        
        if(datanum > 0)
        {
                struct datastoreunit *dataunit  = Malloc(datanum * sizeof(struct datastoreunit));
                struct IEC103DataUnit *IEC103data  = \
                        Malloc(datanum * sizeof(struct IEC103DataUnit));
                if(dataStore->reportscan(dataStore, "report", dataunit) == 0)
		{
			IEC103ReportData(NULL, 0);
			Free(dataunit);
			return 0;
		}
                PrintfGreen("datanum:%d", datanum);
                IEC103DataPKG(dataunit, IEC103data, datanum);
                
                
                
                if(IEC103ReportData(IEC103data, datanum) > 0)
                {
                        dataStore->reportdel(dataStore, "report");
                }

                Free(dataunit);
        }
        else
        {
                IEC103ReportData(NULL, 0);
        }

        return 0;

}

void IEC103Progress(void)
{
 
        IEC103Init();
        while(1)
        {
                IEC103Execute();
                IEC103Sleep();
        }
        IEC103UnInitialize();

        return;
}
            
