#ifndef __DOFAR_WATCHDOG_H
#define __DOFAR_WATCHDOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/watchdog.h>


int  watchdog_initialization();
void watchdog_keep_alive(int watchdog_fd);
void watchdog_release(int watchdog_fd);

#endif

