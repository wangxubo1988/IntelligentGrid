#ifndef _DEVICE_QUERY_H_
#define _DEVICE_QUERY_H_

#include <mysqlite.h>

#define ALL_STATUS 0

#define UF_STATUS 1  //Unfinished

#define UR_STATUS 2 //Unreport

struct System{
        int ProtocolType;
        int Reboot;
        int Register;
        char Code[20];
}System;

struct Server{
        char IP[20];
        int XmlPort;
        int Interval;
        int DataPort;
}Server;

struct Network{
        char IP[20];
        char Mask[20];
        char Gateway[20];
        char DNS1[20];
        char DNS2[20];
}Network;

struct SystemConfig{
        struct System system;
        struct Server server;
        struct Network network;
}SystemConfig;

typedef struct DeviceMgmt DeviceMgmt;

struct SensorConfig{
        long code;
        int interface;
        long sleeptime;
        double ratio;
        int zigbeenum;
        int status;
};

struct ZigbeeConfig{
        int num;
        char mac[50];
        int status;
};

struct DeviceMgmt{
        mysqlite *sqlite;   //base class
        struct SensorConfig sensorconfig;
        struct ZigbeeConfig zigbeeconfig;
        struct SystemConfig systemconfig;
        char SqliteName[100];
        int (*savesensorconfig)(DeviceMgmt* const me);
        int (*deletesensorconfig)(DeviceMgmt* const me,int status);
        int (*type2interface)(DeviceMgmt* const me, char *Type);
        int (*mac2zigbeenum)(DeviceMgmt* const me, char *mac);
        int (*deletezigbeeconfig)(DeviceMgmt* const me);
        int (*savezigbeeconfig)(DeviceMgmt* const me);
        int (*getsensornum)(DeviceMgmt* const me, int code, int status);
        int (*getsensorconfig)\
                (DeviceMgmt* const me, int code, struct SensorConfig config[], int status);
        int (*getzigbeestatus)(DeviceMgmt* const me, int code);
        int (*setzigbeestatus)(DeviceMgmt* const me, int code, int Status);
        int (*getsystemconfig)(DeviceMgmt * me);
        int (*setsensorstatus)(DeviceMgmt* const me, int code, int Status);
        int (*getsensorcode)(DeviceMgmt* const me, int zigbeenum, int interface);
        double (*getsensorratio)(DeviceMgmt* const me, int code);
        int (*sensorstatusconfirm)(DeviceMgmt* const me);
        int(*disablecom)(DeviceMgmt* const me);
        int (*deldisablecom)(DeviceMgmt* const me, int code);
        int (*checkconfig)(DeviceMgmt* const me);
        int (*cleanconfigchange)(DeviceMgmt* const me);
};

DeviceMgmt * DeviceMgmtCreate(char *SqliteName);

void DeviceMgmtDestroy(DeviceMgmt * const me);

#endif