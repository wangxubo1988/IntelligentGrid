#ifndef _DATA_PACKAGE_
#define _DATA_PACKAGE_

#include <time.h>

struct DataPKGDataUnit{
        char interface;
        char type;
        short value;
        long cid;
};

struct ZigbeeHeader{
        short Sign;
        char  mac[8];
        short type;
        short len;
};

typedef struct dataPKG dataPKG;

struct dataPKG{
        char buffer[2000];
        int len;
        int (*joining)(dataPKG* const me);
        int (*report)(dataPKG* const me);
        int (*confirm)(dataPKG* const me);
};

dataPKG * dataPKGCreate(void);
void dataPKGDestroy(dataPKG * const me);


#endif
