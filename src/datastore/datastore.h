#ifndef _DATA_STORE_
#define _DATA_STORE_

#include <time.h>

#define DATA_MAX_COUNT 200000

typedef struct DataStore DataStore;

struct datastoreunit{
        long sensorID;
        float data;
        time_t time;
        char type[20];
};

struct DataStore{
        mysqlite *sqlite;
        struct datastoreunit unit;
        int (*reportadd)(struct DataStore* const me, char *type); 
        int (*reportgetcount)(struct DataStore* const me, char *type);
        int (*reportdelexceed)(struct DataStore* const me, char *type); 
        //Ĭ������20000����ʷ����
        int (*reportdel)(struct DataStore* const me, char *type);
        int (*reportscan)(DataStore* const me, char *type, struct datastoreunit unit[]);
};

DataStore * DataStoreCreate(void);

void DataStoreDestroy(DataStore * const me);

#endif