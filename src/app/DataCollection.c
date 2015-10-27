#include <uart.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <misc.h>
#include <stdio.h>
#include<netinet/in.h>
#include <misc.h>
#include <DataCollection.h>
#include <mysqlite.h>
#include <FuncPKG.h>
#include <time.h>
#include <DataPKG.h>

int DataCollectionInit()
{
        DataPKG = dataPKGCreate();
        return 0;
}

int DataCollectionUnInitialize()
{
        dataPKGDestroy(DataPKG);
        return 0;
}

int DataCollection(char buf[], int len)
{
    int i;
    PrintfGreen("uart rec:");
    for(i=0;i<len;i++)
            printf("%02X ",buf[i]);
    printf("\n");
	if(buf[0] != 0x34 || buf[1] != 0x12)
	{
		PrintfRed("header error!");
		return -1;
	}



    struct ZigbeeHeader *pzigbeeheader;
    pzigbeeheader = (struct ZigbeeHeader *)buf;
    StrNCpy(DataPKG->buffer, buf, len);
    DataPKG->len = len;

    if(TestCrc(buf,pzigbeeheader->len + 16 - 2))
    {

        return -1;

    }

/*
	if(pzigbeeheader->len + 16 != len)
	{
		PrintfRed("len error!");
	       return -1;

	}
	*/
        switch(pzigbeeheader->type)
        {
                case JOINING:
                        DataPKG->joining(DataPKG);
                        break;
                case REPORT:
//						PrintfGreen("REPORT!\n");
                        DataPKG->report(DataPKG);
                        break;
                case CONFIRM:
                        DataPKG->confirm(DataPKG);
                        break;
                default:
                        break;
        }
        
        return 0;

}

