#ifndef _MYSQLITE_
#define _MYSQLITE_
#include <sqlite3.h>
#include <SystemInit.h>

typedef struct mysqlite mysqlite;

struct mysqlite{
        sqlite3 *db;
        
        int (*open)(mysqlite * me, char * file);
        int (*close)(mysqlite * me);
        int (*create)(mysqlite * me, char *sqlstr);
        int (*insert)(mysqlite * me, char *sqlstr);
        sqlite3_stmt *  (*select)(mysqlite * me, char *sqlstr);
        int (*update)(mysqlite * me, char *sqlstr);
        int (*delete)(mysqlite * me, char *sqlstr);
};

mysqlite *mysqliteCreate(void);

void mysqliteDestroy(mysqlite * const me);

#endif
