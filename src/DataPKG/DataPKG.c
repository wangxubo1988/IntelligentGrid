#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <FuncPKG.h>
#include <DataPKG.h>
#include <time.h>
#include <misc.h>

static int ChangeZigbeeStatus(int code)
{
        if(deviceMgmt->getzigbeestatus(deviceMgmt, code) == 2)
        {
                deviceMgmt->setzigbeestatus(deviceMgmt, code, 0);
        }
        
        return 0;
}

static int dataPKGJoining(dataPKG* const me)
{
        int SensorCount = 0;
        char macstr[20];
        
        struct ZigbeeHeader *pzigbeeheader;
        pzigbeeheader = (struct ZigbeeHeader *)me->buffer;

        MacHexToString(pzigbeeheader->mac, macstr);
        int Zigbeecode = deviceMgmt->mac2zigbeenum(deviceMgmt, macstr);
        if(Zigbeecode != 0)
        {
                ChangeZigbeeStatus(Zigbeecode);
                SensorCount = deviceMgmt->getsensornum(deviceMgmt, Zigbeecode, \
                        ALL_STATUS);
        }
        
        pzigbeeheader->Sign = 0x5678;
        pzigbeeheader->type = 0x02;
        
        

        if(SensorCount > 0)
        {
                PrintfGreen("SensorCount:%d", SensorCount);
                struct SensorConfig Sensorconfig[SensorCount];
                deviceMgmt->getsensorconfig(deviceMgmt, Zigbeecode, Sensorconfig, \
                        ALL_STATUS);

                struct DataPKGDataUnit Uint[SensorCount * 2];
                int i = 0;
                for(i=0;i<SensorCount;i++)
                {
                        Uint[i*2].interface = Sensorconfig[i].interface;
                        Uint[i*2].type = 0x20;
                        Uint[i*2].value = 0x01;
                        Uint[i*2].cid = Sensorconfig[i].code;

                        Uint[i*2 + 1].interface = Sensorconfig[i].interface;
                        Uint[i*2 + 1].type = 0x23;
                        Uint[i*2 + 1].value = Sensorconfig[i].sleeptime;
                        Uint[i*2 + 1].cid = Sensorconfig[i].code;
                        
                }
                pzigbeeheader->len = SensorCount * sizeof(struct DataPKGDataUnit) * 2;
                PrintfGreen("pzigbeeheader->len:%d", pzigbeeheader->len);
                StrNCpy(me->buffer + 0x0e, (char *)Uint, pzigbeeheader->len);
        }
        else 
        {
                struct DataPKGDataUnit Uint;
                
                Uint.interface = 0x00;
                Uint.type = 0x23;
                Uint.value = 0x00;
                Uint.cid = 0x00;
                
                pzigbeeheader->len = sizeof(struct DataPKGDataUnit);
                StrNCpy(me->buffer + 0x0e, (char *)&Uint, pzigbeeheader->len);
        }
        CalculCrc(me->buffer, sizeof(struct ZigbeeHeader) + pzigbeeheader->len);

        me->len = sizeof(struct ZigbeeHeader) + pzigbeeheader->len + CRC16LEN;
        PrintfGreen("len:%d", me->len);
        return 0;
}

int GetSensorData(int zigbeenum, struct DataPKGDataUnit Uint[], int num)
{
        int i;
        for(i=0;i<num;i++)
        {
              int sensorID = deviceMgmt->getsensorcode(\
                        deviceMgmt, zigbeenum, Uint[i].interface);
		if(sensorID > 0)
		{
	                dataStore->unit.sensorID= sensorID;
			
	                double ratio = deviceMgmt->getsensorratio(deviceMgmt, \
	                        dataStore->unit.sensorID);
	                dataStore->unit.data = Uint[i].value * ratio;
	                        
	                PrintfGreen("dataStore->data:%f", dataStore->unit.data);
	                dataStore->unit.time = (long)time(NULL);
	                dataStore->reportadd(dataStore, "report");
		}
		else
		{
			PrintfRed("sensor not exist!");
		}
        }
        return 0;
}

static int dataPKGReport(dataPKG* const me)
{
        int SensorCount = 0;
        char macstr[20];
        struct ZigbeeHeader *pzigbeeheader;
        pzigbeeheader = (struct ZigbeeHeader *)me->buffer;

        MacHexToString(pzigbeeheader->mac, macstr);
        int Zigbeecode = deviceMgmt->mac2zigbeenum(deviceMgmt, macstr);
        if(Zigbeecode != 0)
        {
                ChangeZigbeeStatus(Zigbeecode);
                SensorCount = deviceMgmt->getsensornum(deviceMgmt, Zigbeecode, \
                        UF_STATUS);
        }
        
        pzigbeeheader->Sign = 0x5678;
        pzigbeeheader->type = 0x04;
        GetSensorData(Zigbeecode, \
                (struct DataPKGDataUnit *)(me->buffer + sizeof(struct ZigbeeHeader)), \
                pzigbeeheader->len/(sizeof(struct DataPKGDataUnit)));
        if(SensorCount > 0)
        {
                struct SensorConfig Sensorconfig[SensorCount];
                deviceMgmt->getsensorconfig(deviceMgmt, Zigbeecode, Sensorconfig, \
                        UF_STATUS);

                
				//Uint[0].interface = 0x00;//Sensorconfig[i].interface;
                //Uint[0].type = 0x24;
                //Uint[0].value = 0;
                //Uint[0].cid = 0x00;//Sensorconfig[i].code;
				
                int i = 0;
                int count = SensorCount*2;
                struct DataPKGDataUnit Uint[count];
                for(i=0;i<count;)
                {
                        Uint[i].interface = Sensorconfig[i].interface;
						PrintfRed("Uint[i].interface:%d", Uint[i].interface)
                        Uint[i].type = 0x20;
                        Uint[i].value = 0x01;
                        Uint[i].cid = Sensorconfig[i].code;
                        i++;
                        if(Sensorconfig[i].interface < 0x80)
                        {
                                Uint[i].interface = Sensorconfig[i].interface;
                                Uint[i].type = 0x23;
                                Uint[i].value = Sensorconfig[i].sleeptime;
                                Uint[i].cid = Sensorconfig[i].code;
                        }
                        else
                        {
                                count--;
                        }
                        
                }
                PrintfGreen("Sensorconfig:%d", count);
                
                pzigbeeheader->len = sizeof(struct DataPKGDataUnit);
                StrNCpy(me->buffer + 0x0e, (char *)Uint, pzigbeeheader->len);
        }
        else if(Zigbeecode != 0)
        {
                pzigbeeheader->len = 0;
        }
        else
        {
                struct DataPKGDataUnit Uint;
                
                Uint.interface = 0x00;
                Uint.type = 0x23;
                Uint.value = 0x00;
                Uint.cid = 0x00;
                
                pzigbeeheader->len = sizeof(struct DataPKGDataUnit);
                StrNCpy(me->buffer + 0x0e, (char *)&Uint, pzigbeeheader->len);
        }
        CalculCrc(me->buffer, sizeof(struct ZigbeeHeader) + pzigbeeheader->len);

        me->len = sizeof(struct ZigbeeHeader) + pzigbeeheader->len + CRC16LEN;
        return 0;
}


static int dataPKGConfirm(dataPKG* const me)
{
        struct ZigbeeHeader *pZigbeeheader;
        int i;
        struct DataPKGDataUnit* pUint;
        pZigbeeheader = (struct ZigbeeHeader *)me->buffer;
        pZigbeeheader->Sign = 0x5678;
        pZigbeeheader->type = 0x06;
        PrintfGreen("rec len:%d", pZigbeeheader->len);
	char macstr[20];	
	MacHexToString(pZigbeeheader->mac, macstr);
        int zigbeenum = deviceMgmt->mac2zigbeenum(deviceMgmt, macstr);
	if(zigbeenum > 0)
	{
	        for(i=0;i<pZigbeeheader->len/(sizeof(struct DataPKGDataUnit));i++)
	        {
	                pUint = (struct DataPKGDataUnit*)(me->buffer + sizeof(struct ZigbeeHeader))+i;
	                switch(pUint->type)
	                {
	                        case 0xa0:
	                                        if(pUint->interface < 0x80)
	                                        {
	                                        		
	                                        	      long sensorID = deviceMgmt->getsensorcode(deviceMgmt, zigbeenum, pUint->interface);
								if(sensorID == pUint->cid)		
									{
			                                                deviceMgmt->setsensorstatus(deviceMgmt, pUint->cid, \
			                                                        (pUint->value||(pUint+1)->value)==0?1:2);
			                                                dataStore->unit.sensorID = pUint->cid;
															
			                                                dataStore->unit.data = (pUint->value||(pUint+1)->value);
			                                                dataStore->reportadd(dataStore, "config");
									}
	                                        }
	                                        else
	                                        {
	                                                deviceMgmt->deldisablecom(deviceMgmt, pUint->cid);
	                                        }
	                                i++;
	                                
	                                
	                }
	                        
	        }
	}
        pZigbeeheader->len = 0x00;
        
        CalculCrc(me->buffer, sizeof(struct ZigbeeHeader) + pZigbeeheader->len);

        me->len = sizeof(struct ZigbeeHeader) + pZigbeeheader->len + CRC16LEN;
        return 0;
}


static void dataPKGCleanup(dataPKG * const me)
{
        memset(me->buffer, 0, sizeof(me->buffer));
        me->len = 0;        
}

void dataPKGInit(dataPKG * const  me, int (*joining)(dataPKG* const me), \
        int (*report)(dataPKG* const me), int (*confirm)(dataPKG* const me))
{
        memset(me->buffer, 0, sizeof(me->buffer));
        me->len = 0;
        me->joining = joining;
        me->report = report;
        me->confirm = confirm;
        
}

dataPKG * dataPKGCreate(void)
{
        dataPKG * me = (dataPKG *)Malloc(sizeof(dataPKG));
        
        if(me != NULL)
        {
                dataPKGInit(me, dataPKGJoining, dataPKGReport, dataPKGConfirm);
        }

        return me;
}

void dataPKGDestroy(dataPKG * const me)
{
        if(me != NULL)
        {
                dataPKGCleanup(me);  
        }
        Free(me);
}