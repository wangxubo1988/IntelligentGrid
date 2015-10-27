#include <misc.h>
#include <unistd.h>
#include <DataCollection.h>
#include <MyThread.h>
#include <SystemInit.h>
#include <log.h>
#include <mysqlite.h>
#include <uart.h>
#include <xmlparse.h>
#include <time.h>
#include <watchdog.h>



int  main(int argc, char * argv [])
{


        log_open("Tarminal_log");
        LOG_NOTICE("System Start!");

        if(SystemInit() < 0)
        {
                 return -1;
        }

        SystemStart();
#if WDT_ENABLE
        int wdt_fd = watchdog_initialization();
#endif
        while(1)
        {
               sleep(10);
#if WDT_ENABLE
               watchdog_keep_alive(wdt_fd);
#endif
        }
#if WDT_ENABLE
        watchdog_release(wdt_fd);
#endif
        return 0;
}


