#include<stdio.h>
#include"IEC103.h"
#include<string.h>
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
#include <reportdata.h>

int reportdata()
{
        switch(deviceMgmt->systemconfig.system.ProtocolType)
        {
                case IEC103:
                        
                        IEC103Progress();
                        break;
                default:
                        break;
                        
        }
        return 0;
}

int deviceMgmtReport(char buf[])
{
        char tmp[200];
        int i;
        sprintf(tmp, "<message code=\"%s\">", deviceMgmt->systemconfig.system.Code);
        strcat(buf, tmp);
        int uintcount = dataStore->reportgetcount(dataStore, "config");
        struct datastoreunit uint[uintcount];
        dataStore->reportscan(dataStore, "config", uint);
        for(i=0;i<uintcount;i++)
        {
                sprintf(tmp, "<result type=\"config\" code=\"%ld\" value=\"%d\"/>", \
                        uint[i].sensorID, (int)uint[i].data);
                strcat(buf, tmp);
        }
        strcat(buf, "</message>\n");

        return 0;
}
