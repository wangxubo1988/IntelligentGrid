#ifndef _MISC_H_
#define _MISC_H_

#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <uart.h>
#include <mysqlite.h>
#include <SystemInit.h>
#include <DeviceMgmt.h>
#include <datastore.h>
#include <DataPKG.h>

#define USE3G   1

#define DEBUG  0

#define MEM_DEBUG  0

#define WDT_ENABLE 0		
  
#if DEBUG//release
#define sqliteFilePath "/usr/local/IntelligentGrid.db"
#else   //debug
#define sqliteFilePath "../DB/IntelligentGrid.db"
#endif

DeviceMgmt * deviceMgmt;
DataStore * dataStore;
dataPKG * DataPKG;

#define NONE                     "\033[m"
#define RED                        "\033[0;32;31m"
#define LIGHT_RED            "\033[1;31m"
#define GREEN                   "\033[0;32;32m"
#define LIGHT_GREEN       "\033[1;32m"
#define BLUE                     "\033[0;32;34m"
#define LIGHT_BLUE          "\033[1;34m"
#define DARY_GRAY           "\033[1;30m"
#define CYAN                    "\033[0;36m"
#define LIGHT_CYAN        "\033[1;36m"
#define PURPLE                  "\033[0;35m"
#define LIGHT_PURPLE     "\033[1;35m"
#define BROWN                   "\033[0;33m"
#define YELLOW                  "\033[1;33m"
#define LIGHT_GRAY         "\033[0;37m"
#define WHITE                   "\033[1;37m"

#define PrintfBLUE(fmt , args...)        printf(BLUE);\
                                                        printf(fmt, ##args);\
                                                        printf(NONE);\
                                                        printf("\n");


#define PrintfRed(fmt , args...)        printf(RED);\
                                                        printf(fmt, ##args);\
                                                        printf(NONE);\
                                                        printf("\n");

#define PrintfGreen(fmt , args...)      printf(GREEN);\
                                                        printf(fmt, ##args);\
                                                        printf(NONE);\
                                                        printf("\n");


#if DEBUG == 1
#define DEBUG_PRINTF printf("file:%s__function:%s__linefile:%d\n", \
        __FILE__, __FUNCTION__, __LINE__);
#else
#define DEBUG_PRINTF
#endif


#if MEM_DEBUG == 1
#define Malloc(size)    MyMalloc(size ,__FILE__, __FUNCTION__, __LINE__)
#define Free(ptr)       MyFree(ptr , __FILE__, __FUNCTION__, __LINE__)
#else
#define Malloc(size)    malloc(size)
#define Free(ptr)       free(ptr)
#endif

#endif
