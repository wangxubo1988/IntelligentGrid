#include "watchdog.h"
#include "misc.h"


/*
 * This function simply sends an IOCTL to the driver, which in turn ticks
 * the PC Watchdog card to reset its internal timer so it doesn't trigger
 * a computer reset.
 */
 void watchdog_keep_alive(int watchdog_fd)
{
        int dummy;
        PrintfGreen("feed dog");
        ioctl(watchdog_fd, WDIOC_KEEPALIVE, &dummy);
}

int  watchdog_initialization()
{
        int flags;
        int watchdog_fd;
        watchdog_fd = open("/dev/watchdog", O_WRONLY);
        if(watchdog_fd< 0){
                printf("Can not open /dev/watchdog\n" );
                return -1;
        }
        flags = 3;
        ioctl(watchdog_fd, WDIOC_GETTIMEOUT, &flags);
        return watchdog_fd;
}


void watchdog_release(int watchdog_fd)
{
        close(watchdog_fd);
}


