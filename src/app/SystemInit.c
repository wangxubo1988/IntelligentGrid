#include <misc.h>
#include <mysqlite.h>
#include <mysqlite.h>
#include <DataCollection.h>
#include <sqlite3.h>
#include <DeviceMgmt.h>
#include<fcntl.h>
#include<sys/stat.h>
#include <unistd.h>
#include<FuncPKG.h>
#include <log.h>
int LoadConfig()
{

        //GetSystemConfig(&systemconfig.system);

        //GetServerConfig(&systemconfig.server);

        //GetNetworkConfig(&systemconfig.network);


        return 0;
}


static int AutomaticStartDetection()
{
        char buffer[1000];
        char envnum[2];
        int fd = open("/dev/mtd0", O_RDONLY);

        lseek(fd,0xc0000+4,SEEK_SET );
        ReadOneByte(fd, envnum);
        lseek(fd,0x160000+4,SEEK_SET );
        ReadOneByte(fd, envnum+1);
        if(envnum[0] > envnum[1])
        {
                lseek(fd,0xc0000,SEEK_SET );
                Readn(fd, buffer, 1000);
        }
        else
        {
                lseek(fd,0x160000,SEEK_SET );
                Readn(fd, buffer, 1000);
        }
        int offset = StrMatch(buffer,"appauto=",1000);
		
        if(offset == 0)
        {
               LOG_ERROR("not find appauto!");
               PrintfRed("not find appauto!");
               //return -2;
        }
        if(*(offset+buffer) != '1')
        {
                PrintfRed("appauto=%c",*(offset+buffer));
                //return -1;
        }
        else
        {
                PrintfGreen("AutomaticStart");
        }
        close(fd);
        return 0;
}


int SystemInit()
{
#if WDT_ENABLE
        if(AutomaticStartDetection() < 0)
        {
                return -1;
        }
#endif        
		PrintfGreen("sqlpath:%s", sqliteFilePath);
        deviceMgmt = DeviceMgmtCreate(sqliteFilePath);
        deviceMgmt->getsystemconfig(deviceMgmt);
        dataStore = DataStoreCreate();
        //LoadConfig();

        //UartInit();

        return 0;
}


int Systemclose()
{
        
        
        return 0;
}