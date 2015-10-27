#ifndef _XML_PARSE_H_
#define _XML_PARSE_H_

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>

struct SensorConfigUint{
        long code;                    
        char type[20];                      
        long sleeptime;
        double ratio;
        int zigbeenum;
}SensorConfigUint;

typedef struct Resolver Resolver;

struct Resolver{
        int CMTID;    /*-9  初始状态    0 解析成功   */
        struct SensorConfigUint config;
        int (*parse)(Resolver * const me, char *docstr);
        void (*clean)(Resolver * const me);
       
};
Resolver * ResolverCreate(void);
void ResolverDestroy(Resolver * const me);
#endif
