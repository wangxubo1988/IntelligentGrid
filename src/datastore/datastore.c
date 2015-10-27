#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysqlite.h>
#include <misc.h>
#include <log.h>
#include <SystemInit.h>
#include <datastore.h>

/*
type:report
type:device
type:result

*/

static int DataStoreReportAdd(DataStore* const me, char *type)
{
        char str[200];
        sprintf(str, "insert into tb_datastore values (%ld, %f, %ld, '%s')", \
                me->unit.sensorID, me->unit.data, me->unit.time, type);
	//PrintfRed(str);
        me->sqlite->insert(me->sqlite, str);

        return 0;
}

/*?*/static int DataStoreReportGetCount(DataStore* const me, char *type)
{
        int count = 0;
        char str[200];
        
        sprintf(str, "select count(*) from tb_datastore where d_type = '%s' ", type);
        sqlite3_stmt* stmt = me->sqlite->select(me->sqlite, str);
        while(sqlite3_step(stmt) == SQLITE_ROW )
        {
                count = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
        
        return count;
}

static int DataStoreReportDelExceed(DataStore* const me, char *type)
{
        char str[500];
        sprintf(str, "delete from tb_datastore where "\
                "d_type = '%s' and "\
                "(select count(d_data) from tb_datastore where d_type = '%s') > %d and "\
                "d_data in (select d_data from tb_datastore order by d_time desc limit "\
                "(select count(d_data) from tb_datastore where d_type = '%s' ) offset %d)", \
                type, type, DATA_MAX_COUNT, type, DATA_MAX_COUNT);
        me->sqlite->delete(me->sqlite, str);
        return 0;
}

static int DataStoreReportDel(DataStore* const me, char *type)
{
        char str[200];
        sprintf(str, "delete from tb_datastore where d_type = '%s' ", type);
        me->sqlite->delete(me->sqlite, str);
        return 0;
}

static int DataStoreReportScan\
        (DataStore* const me, char *type, struct datastoreunit unit[])
{
        char str[500];
        int i = 0;
        sprintf(str, \
                "select d_sensorID,d_data,d_time,d_type from tb_datastore where d_type = '%s' ", \
                type);
        sqlite3_stmt* stmt = me->sqlite->select(me->sqlite, str);
		PrintfGreen(str);
        while(sqlite3_step(stmt) == SQLITE_ROW )
        {
                unit[i].sensorID = sqlite3_column_int(stmt, 0);
                unit[i].data = sqlite3_column_double(stmt, 1);
                unit[i].time = sqlite3_column_int(stmt, 2);
                strcpy(unit[i].type, (char *)sqlite3_column_text(stmt, 3));
		 PrintfGreen("sensorID:%02hhx data:%f, %s" ,unit[i].sensorID, unit[i].data ,unit[i].type);	
                i++;
        }
        sqlite3_finalize(stmt);
        return i;
}


static void DataStoreCleanup(DataStore * const me)
{


}




static void DataStoreInit(DataStore * const  me, \
        int (*reportadd)(struct DataStore* const me, char *type), 
        int (*reportgetcount)(struct DataStore* const me, char *type),
        int (*reportdelexceed)(struct DataStore* const me, char *type),
        int (*reportdel)(struct DataStore* const me, char *type),
        int (*reportscan)(DataStore* const me, char *type, struct datastoreunit unit[]))
{
        me->sqlite = mysqliteCreate();
        me->sqlite->open(me->sqlite, ":memory:");
        me->sqlite->create(me->sqlite, "CREATE TABLE [tb_datastore] ("\
                                                                        "[d_sensorID] INTEGER(1), "\
                                                                        "[d_data] double(1), "\
                                                                        "[d_time] INTEGER(1), "\
                                                                        "[d_type] CHAR(20));");
        me->sqlite->create(me->sqlite, "CREATE TABLE [tb_command] ("\
                                                                        "[c_cid] INTEGER(1), "\
                                                                        "[c_object] CHAR(20), "\
                                                                        "[c_mac] CHAR(20), "\
                                                                        "[c_action] CHAR(20), "\
                                                                        "[c_status] INTEGER(1));");
        me->reportadd = reportadd;
        me->reportgetcount = reportgetcount;
        me->reportdelexceed = reportdelexceed;
        me->reportdel = reportdel;
        me->reportscan = reportscan;
}


DataStore * DataStoreCreate(void)
{
        DataStore * me = (DataStore *)Malloc(sizeof(DataStore));
        
        if(me != NULL)
        {
                DataStoreInit(me, DataStoreReportAdd, DataStoreReportGetCount, \
                        DataStoreReportDelExceed, DataStoreReportDel, DataStoreReportScan);
        }

        return me;
}

void DataStoreDestroy(DataStore * const me)
{
        if(me != NULL)
        {
                me->sqlite->close(me->sqlite);
                DataStoreCleanup(me);  
        }
        Free(me);
}
