#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <misc.h>
#include <xmlparse.h>
#include <FuncPKG.h>
#include <mysqlite.h>

#define  XmlFree(x)     if(x != NULL){xmlFree(x);}


static int  getConfig(Resolver * const me, xmlNodePtr cur, int ZigbeeNUM)
{
        xmlChar *key;
		int Interface;

        memset(&me->config, 0, sizeof(me->config));
        
        key = xmlGetProp(cur, (const xmlChar *)"code");
        
        if(key != NULL)
        {
                me->config.code = atol((char *)key);    
        }
        
        printf("code:%ld\n", me->config.code);
        XmlFree(key);

        key = xmlGetProp(cur, (const xmlChar *)"type");
        
        if(key != NULL)
        {
              strcpy(me->config.type, (char *)key);
		Interface = atol((char *)key); 
        }
        
        printf("type:%s\n", me->config.type);
        XmlFree(key);

        key = xmlGetProp(cur, (const xmlChar *)"sleeptime");
        
        if(key != NULL)
        {
                me->config.sleeptime = atol((char *)key);
        }
        
        printf("sleeptime:%ld\n", me->config.sleeptime);
        XmlFree(key);

        key = xmlGetProp(cur, (const xmlChar *)"ratio");
        
        if(key != NULL)
        {
                me->config.ratio = atof((char *)key);
        }
        
        printf("ratio:%lf\n", me->config.ratio);
        XmlFree(key);

        deviceMgmt->sensorconfig.code = me->config.code;
	/*	
	Interface = deviceMgmt->type2interface(deviceMgmt, me->config.type);
	if(Interface < 0)
	{
		PrintfRed("unknow sensor name!");
		return 0;
	}
//ÐÞ¸ÄÔ­Òò£¬È¡Ïû·¢ËÍ´«¸ÐÆ÷Ãû³Æ£¬¸ÄÎªÖ±½Ó·¢ËÍinterface

	*/
	
	deviceMgmt->sensorconfig.interface = Interface;
	if(me->config.sleeptime < 0)
	{
		PrintfRed("sleeptime illegal!");
		return 0;
	}
	
        deviceMgmt->sensorconfig.sleeptime = me->config.sleeptime;
		
        deviceMgmt->sensorconfig.ratio = me->config.ratio;
        deviceMgmt->sensorconfig.zigbeenum = ZigbeeNUM;
        deviceMgmt->savesensorconfig(deviceMgmt);
        
        return 0;

}

static int  parseSensor(Resolver * const me, xmlNodePtr cur, int ZigbeeNUM)
{        
        cur = cur->xmlChildrenNode;
        while(cur != NULL)
        {
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"sensor")))
                {
                        printf("%s:\n", cur->name);
						//deviceMgmt->deletesensorconfig(deviceMgmt, ALL_STATUS);
                        getConfig(me, cur, ZigbeeNUM);
                }
                
                cur = cur->next;
                
        }

        return 0;
}

static int  getZigbeeMac(Resolver * const me, xmlNodePtr cur)
{
        xmlChar *key;
        int ZigbeeNUM = 0;
        key = xmlGetProp(cur, (const xmlChar *)"mac");
        if(key != NULL)
        {
                strcpy(deviceMgmt->zigbeeconfig.mac,  (char *)key);
                deviceMgmt->savezigbeeconfig(deviceMgmt);
                ZigbeeNUM = deviceMgmt->mac2zigbeenum(deviceMgmt, (char *)key);
        }
        printf("mac:%s\n", key);
        XmlFree(key);

        return ZigbeeNUM;
}

static int  parseZigbee(Resolver * const me, xmlNodePtr cur)
{
        int ZigbeeNUM = getZigbeeMac(me, cur);
        parseSensor(me, cur, ZigbeeNUM);

        return 0;
}

static int  parseDevice(Resolver* const me, xmlNodePtr cur)
{
        cur = cur->xmlChildrenNode;
        while (cur != NULL)
        {
                /*ï¿½ï¿½È¡zigbeeï¿½ï¿½ï¿½ï¿½*/
                if ((!xmlStrcmp(cur->name, (const xmlChar *)"zigbee")))
                {
                        printf("%s:\n", cur->name);
                        parseZigbee(me, cur);
                                
                }
                /*ï¿½ï¿½È¡3Gï¿½ÅºÅ²É¼ï¿½ï¿½ï¿½ï¿½ï¿½*/
                else if ((!xmlStrcmp(cur->name, (const xmlChar *)"gateway")))
                {
                        printf("%s:\n", cur->name);
                        getConfig(me, cur, 0);
                }
                
                cur = cur->next;
                
        }

        return 0;
}

static int CheckGatewayCode(const xmlChar * code)
{
        if((!xmlStrcmp(code, (const xmlChar *)deviceMgmt->systemconfig.system.Code)))
        {
                
                return 0;
        }
        return -1;
}

static int  parseBody(Resolver * const me, xmlNodePtr cur)
{
        xmlChar *key;
        if ((!xmlStrcmp(cur->name, (const xmlChar *)"message")))
        {
                key = xmlGetProp(cur, (const xmlChar *)"code");
                printf("\tcode:%s\n", key);
                 /*ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½codeï¿½Ç·ï¿½Ò»ï¿½Â£ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½*/
                if (CheckGatewayCode(key) != 0)
                {
                        me->CMTID = -1; 
			PrintfRed("getway code error!");
                        XmlFree(key);
                        return -1;
                }
                me->CMTID = 0;
                XmlFree(key);
                cur = cur->xmlChildrenNode;
                while (cur != NULL)
                {   
                        if ((!xmlStrcmp(cur->name, (const xmlChar *)"config")))/*ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½*/                
                        {
                                printf("%s:\n", cur->name);
                                
                                deviceMgmt->deletesensorconfig(deviceMgmt, UF_STATUS);
                                deviceMgmt->deletezigbeeconfig(deviceMgmt);
                                parseDevice(me, cur);
                                deviceMgmt->disablecom(deviceMgmt);
   
                        }
                        else if ((!xmlStrcmp(cur->name, (const xmlChar *)"control")))
                        {
                                printf("%s:\n", cur->name);
                                key = xmlGetProp(cur, (const xmlChar *)"action");
                                printf("action:%s\n", key);
                                XmlFree(key);
                                key = xmlGetProp(cur, (const xmlChar *)"cid");
                                printf("cid:%s\n", key);
                                XmlFree(key);
                                key = xmlGetProp(cur, (const xmlChar *)"object");
                                printf("object:%s\n", key);
                                XmlFree(key);
                                
                        }
                        cur = cur->next;
                }
        }
        
        return -1;
}

static int  parseDoc(Resolver * const me, char *docstr)
{
        xmlDocPtr doc;
        xmlNodePtr cur;
        doc = xmlParseMemory(docstr, strlen(docstr));
        if (doc == NULL )
        {
                fprintf(stderr,"Document not parsed successfully. \n");
                return -1;
        }
        
        cur = xmlDocGetRootElement(doc);
        if (cur == NULL)
        {
                fprintf(stderr,"empty document\n");
                xmlFreeDoc(doc);
                
                return -1;
        }

        parseBody(me, cur);

        switch(me->CMTID)
        {

                case 0:
                        break;
                case -1:
                        fprintf(stderr,\
                                        "document of the wrong type, gateway code check error");
                        break;
                case -9:
                        fprintf(stderr,"document of the wrong type, root node != gateway");
                        break;
                default:
                        fprintf(stderr,"unknow error!");
                        break;
        }
        
        xmlFreeDoc(doc);
        
        return 0;
}

static void ResolverCleanup(Resolver * const me)
{
        memset(&me->config, 0, sizeof(me->config));
}

static void ResolverInit(Resolver * const  me, int (*parse)(Resolver * me, char *docstr), \
        void (*clean)(Resolver * me))
{
        me->CMTID = -9;
        memset(&me->config, 0, sizeof(me->config));
        me->parse = parse;
        me->clean = clean;
}

Resolver * ResolverCreate(void)
{
        Resolver * me = (Resolver *)Malloc(sizeof(Resolver));
        
        if(me != NULL)
        {
                ResolverInit(me, parseDoc, ResolverCleanup);
        }

        return me;
}

void ResolverDestroy(Resolver * const me)
{
        if(me != NULL)
        {
                ResolverCleanup(me);  
        }
        Free(me);
}
