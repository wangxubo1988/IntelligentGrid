#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysqlite.h>
#include <misc.h>
#include <log.h>
#include <SystemInit.h>
#include <unistd.h>

static int sqlite_open( mysqlite * me, char * file)
{
        int rc;
        char errcode[100];
        rc = sqlite3_open(file, &me->db);
        if( rc ){
                sprintf(errcode, "Can't open database: %s/n", sqlite3_errmsg(me->db));
                PrintfRed(errcode);
                LOG_ERROR(errcode);
                sqlite3_close(me->db);
                return -1;
        }
        if(sqlite3_busy_timeout(me->db,100) != SQLITE_OK)
        {
                return -2;
        }
        return 0;
}

static int sqlite_close( mysqlite * me)
{
        sqlite3_close(me->db);
        return 0;
}

static int SqliteRcIsOk(int rc, char *szErrMsg)
{
        char errcode[100];

        if(rc != SQLITE_OK)
        {
                sprintf(errcode,"error:%s", szErrMsg);
                PrintfRed(errcode);
                LOG_ERROR(errcode);
                sqlite3_free(szErrMsg);

                return -1;
         }
        usleep(10000);
        return 0;
}

static int CreateOperating(mysqlite * me, char *sqlstr)
{
        int rc;
        char *szErrMsg = NULL;
        
        rc=sqlite3_exec(me->db, sqlstr, 0, 0, &szErrMsg);

        return SqliteRcIsOk(rc, szErrMsg);
}

static int InsertOperating(mysqlite * me, char *sqlstr)
{
        int rc;
        char *szErrMsg = NULL;
        
        rc=sqlite3_exec(me->db, sqlstr, 0, 0, &szErrMsg);

        return SqliteRcIsOk(rc, szErrMsg);
}

static sqlite3_stmt * SelectOperating(mysqlite * me, char *sqlstr)
{
        int rc;
        sqlite3_stmt *stmt = NULL;
        char errcode[100];

        rc= sqlite3_prepare_v2(me->db, sqlstr, strlen(sqlstr), &stmt,0);

        if(rc != SQLITE_OK)
        {
                if(stmt)
                {
                        sqlite3_finalize(stmt);
                }
                sprintf(errcode, "Can't open statement: %s/n", sqlite3_errmsg(me->db));
                PrintfRed(errcode);
                LOG_ERROR(errcode);
        }
        usleep(10000);
        return stmt;
}

static int UpdateOperating(mysqlite * me, char *sqlstr)
{
        int rc;
        char *szErrMsg = NULL;

        rc=sqlite3_exec(me->db, sqlstr, 0, 0, &szErrMsg);
        
        return SqliteRcIsOk(rc, szErrMsg);
}

static int DeleteOperating(mysqlite * me, char *sqlstr)
{
        int rc;
        char *szErrMsg = NULL;

        rc=sqlite3_exec(me->db, sqlstr, 0, 0, &szErrMsg);
        
        return SqliteRcIsOk(rc, szErrMsg);
}

static void mysqliteInit(mysqlite * const me, int (*open)(mysqlite * me, char * file), \
        int (*close)(mysqlite * me), int (*create)(mysqlite * me, char *sqlstr), \
        int (*insert)(mysqlite * me, char *sqlstr), \
        sqlite3_stmt * (*select)(mysqlite * me, char *sqlstr), \
        int (*update)(mysqlite * me, char *sqlstr), int (*delete)(mysqlite * me, char *sqlstr))
{
        me->open  = open;
        me->close = close;
        me->create = create;
        me->insert = insert;
        me->select = select;
        me->update = update;
        me->delete = delete;
}

static void mysqliteCleanup(mysqlite * const me)
{
        
}

mysqlite *mysqliteCreate(void)
{
        mysqlite * me = (mysqlite *)Malloc(sizeof(mysqlite));
        if(me != NULL)
        {
                mysqliteInit(me, sqlite_open, sqlite_close, CreateOperating, InsertOperating,\
                        SelectOperating, UpdateOperating, DeleteOperating);
        }
        return me;
}


void mysqliteDestroy(mysqlite * const me)
{
        if(me != NULL)
        {
                mysqliteCleanup(me);
        }
        Free(me);
}