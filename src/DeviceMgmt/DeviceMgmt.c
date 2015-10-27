#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysqlite.h>
#include <misc.h>
#include <log.h>
#include <DeviceMgmt.h>

#include <SystemInit.h>

/*
zigbee status   
        0        working
        1       sleeping
        2       lost

sensor status
        0       已成功
        1       成功
        2       下发
        3       未下发
*/


static int DeviceMgmtSaveSensorConfig(DeviceMgmt * const me)
{
        char str[300];
        
       
        sprintf(str,"delete from tb_Sensor where s_Code = %ld", me->sensorconfig.code);
        me->sqlite->delete(me->sqlite, str);
        sprintf(str, "insert into tb_Sensor values (%ld, %d, %ld, %lf, %d, 3)", \
                me->sensorconfig.code, me->sensorconfig.interface, \
                me->sensorconfig.sleeptime, me->sensorconfig.ratio, \
                me->sensorconfig.zigbeenum);

	PrintfGreen("%s\n", str);
        me->sqlite->insert(me->sqlite, str);

        return 0;
}

static int DeviceMgmtDeleteSensorConfig(DeviceMgmt * const me, int status)
{
        char str[200];
        if(status == UF_STATUS)
        {
                sprintf(str,"delete from tb_Sensor where s_Status > 1");
        }
        else if(status == ALL_STATUS)
        {
                sprintf(str,"delete from tb_Sensor");
        }
        me->sqlite->delete(me->sqlite, str);

        return 0;
}

static int DeviceMgmtType2Interface(DeviceMgmt * const me, char *Type)
{
        char str[200];
        int Interface = -1;
        sprintf(str,"select t_Interface  from tb_Type2Interface where t_Type = '%s' ", Type);
        sqlite3_stmt* stmt = me->sqlite->select(me->sqlite, str);
        while(sqlite3_step(stmt) == SQLITE_ROW )
        {
                Interface = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);

        return Interface;
}

static int DeviceMgmtMac2Zigbeenum(DeviceMgmt* const me, char* mac)
{
        char str[200];
        int zigbeenum = 0;
        sprintf(str,"select z_Num  from tb_Zigbee where z_Mac = '%s' ", mac);
 
        sqlite3_stmt* stmt = me->sqlite->select(me->sqlite, str);
        while(sqlite3_step(stmt) == SQLITE_ROW )
        {
                zigbeenum = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);

        return zigbeenum;
}

static int CleanSqliteSequenceZigbee(DeviceMgmt* const me)
{
        char str[]= "update sqlite_sequence SET seq = 0 where name = 'tb_Zigbee' ";
        me->sqlite->update(me->sqlite, str);

        return 0;
}

static int DeviceMgmtGetSensorNum\
        (DeviceMgmt* const me, int code ,int status)
{
        int num = 0;
        char str[200];
        if(status == ALL_STATUS)
        {
                sprintf(str, "select count(*) from tb_Sensor where s_ZigbeeNum = %d", code);
        }
        else if(status == UF_STATUS)
        {
                sprintf(str,\
                        "select count(*) from tb_Sensor where s_ZigbeeNum = %d and s_Status > 1", \
                        code);
        }
        sqlite3_stmt* stmt = me->sqlite->select(me->sqlite, str);
        
        while(sqlite3_step(stmt) == SQLITE_ROW )
        {
                num = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);

        return num;
}

static int DeviceMgmtSensorStatusConfirm(DeviceMgmt* const me)
{
        
        char str[]= "update tb_Sensor SET s_Status = 0 where s_Status = 1 ";
        me->sqlite->update(me->sqlite, str);
        return 0;
}


static int DeviceMgmtGetSensorConfig\
        (DeviceMgmt* const me, int code, struct SensorConfig config[], int status)
{
        char str[200];
        int i = 0;
        if(status == ALL_STATUS)
        {
                sprintf(str, \
                        "select s_Code,s_Interface,s_Sleeptime from tb_Sensor where"\
                        " s_ZigbeeNum = %d",  code);
        }
        else if(status == UR_STATUS)
        {
                sprintf(str, \
                        "select s_Code,s_Interface,s_Sleeptime from tb_Sensor where "\
                        "s_ZigbeeNum = %d and s_Status > 0", code);
        }
        else if(status == UF_STATUS)
        {
                sprintf(str, \
                        "select s_Code,s_Interface,s_Sleeptime from tb_Sensor where "\
                        "s_ZigbeeNum = %d and s_Status > 1", code);
        }        
		PrintfRed(str);
        sqlite3_stmt* stmt = me->sqlite->select(me->sqlite, str);
        while(sqlite3_step(stmt) == SQLITE_ROW )
        {
                config[i].code = sqlite3_column_int(stmt, 0);
                config[i].interface = sqlite3_column_int(stmt, 1);
                config[i].sleeptime = sqlite3_column_int(stmt, 2);
                i++;
        }
        sqlite3_finalize(stmt);
        
        return i;
}

static int DeviceMgmtDeleteZigbeeConfig(DeviceMgmt* const me)
{
        char str[200];
        sprintf(str,"delete from tb_Zigbee");
        me->sqlite->delete(me->sqlite, str);
        CleanSqliteSequenceZigbee(me);//删除记录后将自增长重置
        
        return 0;
}

static int DeviceMgmtSaveZigbeeConfig(DeviceMgmt* const me)
{
        char str[200];
        sprintf(str, "insert into tb_Zigbee values(NULL, '%s', 3)", me->zigbeeconfig.mac);
        
        me->sqlite->delete(me->sqlite, str);
        
        return 0;
}

static int DeviceMgmtGetZigbeeStatus(DeviceMgmt* const me, int code)
{
        int status = -1;
        char str[200];
        sprintf(str, "select z_Status  from tb_Zigbee where z_Num = %d ", code);
        sqlite3_stmt* stmt = me->sqlite->select(me->sqlite, str);
        while(sqlite3_step(stmt) == SQLITE_ROW )
        {
                status = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
        return status;
}

static int DeviceMgmtSetZigbeeStatus\
        (DeviceMgmt* const me, int code, int Status)
{
        char str[200];
        
        sprintf(str, "update tb_Zigbee SET z_Status=%d where z_Num=%d ", Status, code);
        me->sqlite->update(me->sqlite, str);
        
        return 0;
}

static int DeviceMgmtSetSensorStatus\
        (DeviceMgmt* const me, int code, int Status)
{
        char str[200];
        
        sprintf(str, "update tb_Sensor SET s_Status=%d where s_Code=%d ", Status, code);
		//PrintfRed(str);
	me->sqlite->update(me->sqlite, str);
        
        return 0;
}
static int GetSystemServerConfig(DeviceMgmt* const me)
{
        char str[]="select Config,Value from tb_SystemConfig where Belong = 'Server' ";
        
        sqlite3_stmt* stmt = me->sqlite->select(me->sqlite, str);
        while(sqlite3_step(stmt) == SQLITE_ROW )
        {
                if(!strcmp((char *)sqlite3_column_text(stmt, 0), "IP"))
                {
                        
                        strcpy(me->systemconfig.server.IP, (char *)sqlite3_column_text(stmt, 1));
                }
                else if(!strcmp((char *)sqlite3_column_text(stmt, 0), "XmlPort"))
                {
                        me->systemconfig.server.XmlPort = sqlite3_column_int(stmt, 1);
                }
                else if(!strcmp((char *)sqlite3_column_text(stmt, 0), "Interval"))
                {
                        me->systemconfig.server.Interval = sqlite3_column_int(stmt, 1);
                }
                else if(!strcmp((char *)sqlite3_column_text(stmt, 0), "DataPort"))
                {
                        me->systemconfig.server.DataPort = sqlite3_column_int(stmt, 1);
                }
                        
        }
        sqlite3_finalize(stmt);
        return 0;
}

static int GetSystemDeviceConfig(DeviceMgmt* const me)
{
        char str[]="select Config,Value from tb_SystemConfig where Belong = 'System' ";
        
        sqlite3_stmt* stmt = me->sqlite->select(me->sqlite, str);
        while(sqlite3_step(stmt) == SQLITE_ROW )
        {

                if(!strcmp((char *)sqlite3_column_text(stmt, 0), "ProtocolType"))
                {
                        me->systemconfig.system.ProtocolType = sqlite3_column_int(stmt, 1);
                }
                else if(!strcmp((char *)sqlite3_column_text(stmt, 0), "reboot"))
                {
                        me->systemconfig.system.Reboot = sqlite3_column_int(stmt, 1);
                }
                else if(!strcmp((char *)sqlite3_column_text(stmt, 0), "Code"))
                {
                        strcpy(me->systemconfig.system.Code, \
                                (char *)sqlite3_column_text(stmt, 1));
                }
                else if(!strcmp((char *)sqlite3_column_text(stmt, 0), "Register"))
                {
                        me->systemconfig.system.Register = sqlite3_column_int(stmt, 1);
                }
                        
        }
        sqlite3_finalize(stmt);
        return 0;
}

static int GetSystemNetworkConfig(DeviceMgmt* const me)
{
        char str[]="select Config,Value from tb_SystemConfig where Belong = 'Network' ";
        
        sqlite3_stmt* stmt = me->sqlite->select(me->sqlite, str);
        while(sqlite3_step(stmt) == SQLITE_ROW )
        {
                if(!strcmp((char *)sqlite3_column_text(stmt, 0), "IP"))
                {
                        strcpy(me->systemconfig.network.IP, \
                                (char *)sqlite3_column_text(stmt, 1));
                }
                else if(!strcmp((char *)sqlite3_column_text(stmt, 0), "Mask"))
                {
                        strcpy(me->systemconfig.network.Mask, \
                                (char *)sqlite3_column_text(stmt, 1));
                }
                else if(!strcmp((char *)sqlite3_column_text(stmt, 0), "Gateway"))
                {
                        strcpy(me->systemconfig.network.Gateway, \
                                (char *)sqlite3_column_text(stmt, 1));
                }
                else if(!strcmp((char *)sqlite3_column_text(stmt, 0), "DNS1"))
                {
                        strcpy(me->systemconfig.network.DNS1, \
                                (char *)sqlite3_column_text(stmt, 1));
                }
                else if(!strcmp((char *)sqlite3_column_text(stmt, 0), "DNS2"))
                {
                        strcpy(me->systemconfig.network.DNS2, \
                                (char *)sqlite3_column_text(stmt, 1));
                }
                        
        }
        sqlite3_finalize(stmt);
        return 0;
}

static int DeviceMgmtGetSystemConfig(DeviceMgmt* const me)
{
        GetSystemServerConfig(me);
        GetSystemDeviceConfig(me);
        GetSystemNetworkConfig(me);
        
        return 0;
}

static int DeviceMgmtGetSensorCode\
        (DeviceMgmt* const me, int zigbeenum, int interface)
{
        int Code = -1;
        char str[200];
        sprintf(str, \
                "select s_Code  from tb_Sensor where s_Interface = %d and s_ZigbeeNum = %d ", \
                interface, zigbeenum);
        sqlite3_stmt* stmt = me->sqlite->select(me->sqlite, str);
        while(sqlite3_step(stmt) == SQLITE_ROW )
        {
                Code = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
        return Code;
}

static double DeviceMgmtGetSensorRatio\
        (DeviceMgmt* const me, int code)
{
        double ratio = 0;
        char str[200];
        sprintf(str, "select s_Ratio  from tb_Sensor where s_Code = %d ", code);
        sqlite3_stmt* stmt = me->sqlite->select(me->sqlite, str);
        while(sqlite3_step(stmt) == SQLITE_ROW )
        {
                ratio = sqlite3_column_double(stmt, 0);
        }
        sqlite3_finalize(stmt);
        return ratio;
}

static int DeviceMgmtDisableCom(DeviceMgmt* const me)
{
        char str[200];
        
        sprintf(str, "update tb_Sensor SET s_Interface=s_Interface+128,s_Status=3  "\
                "where s_Status<2 and s_Interface<128");
        me->sqlite->update(me->sqlite, str);
        
        return 0;
}

static int DeviceMgmtDelDisableCom(DeviceMgmt* const me, int code)
{
        char str[200];
        sprintf(str,"delete from tb_Sensor where s_Code = %d", code);
        me->sqlite->delete(me->sqlite, str);
        me->sqlite->delete(me->sqlite, str);
        
        return 0;
}

static int DeviceMgmtCleanConfigChange(DeviceMgmt* const me)
{
        char str[]="update tb_SystemConfig SET Value = 0 "\
                "where Belong = 'System' and Config = 'ConfigChange' ";
        me->sqlite->update(me->sqlite, str);
        
        return 0;
}

static int DeviceMgmtCheckConfig(DeviceMgmt* const me)
{
        int result = 0;
        char str[200];
        sprintf(str, "select Value  from tb_SystemConfig where "\
                "Belong = 'System' and  Config='ConfigChange' ");
        sqlite3_stmt* stmt = me->sqlite->select(me->sqlite, str);
        while(sqlite3_step(stmt) == SQLITE_ROW )
        {
                result = atoi((char *)sqlite3_column_text(stmt, 0));
        }
        sqlite3_finalize(stmt);
        return result;
}

static int DeviceMgmtInit(DeviceMgmt * const  me, \
        int (*savesensorconfig)(DeviceMgmt * me), \
        int (*deletesensorconfig)(DeviceMgmt * me,int status), \
        int (*type2interface)(DeviceMgmt * me, char *Type), \
        int (*mac2zigbeenum)(DeviceMgmt* const me, char *mac), \
        int (*deletezigbeeconfig)(DeviceMgmt* const me), \
        int (*savezigbeeconfig)(DeviceMgmt* const me), \
        int (*getsensornum)(DeviceMgmt* const me, int code, int status), \
        int (*getsensorconfig)\
        (DeviceMgmt* const me, int code, struct SensorConfig config[], int status),\
        int (*getzigbeestatus)(DeviceMgmt* const me, int code), \
        int (*setzigbeestatus)(DeviceMgmt* const me, int code, int Status), \
        int (*getsystemconfig)(DeviceMgmt * me),\
        int (*setsensorstatus)(DeviceMgmt* const me, int code, int Status),\
        int (*getsensorcode)(DeviceMgmt* const me, int zigbeenum, int interface),\
        double (*getsensorratio)(DeviceMgmt* const me, int code),
        int (*sensorstatusconfirm)(DeviceMgmt* const me),\
        int (*disablecom)(DeviceMgmt* const me),\
        int (*deldisablecom)(DeviceMgmt* const me, int code),\
        int (*checkconfig)(DeviceMgmt* const me),\
        int (*cleanconfigchange)(DeviceMgmt* const me))
{
        me->sqlite = mysqliteCreate();
        me->savesensorconfig = savesensorconfig;
        me->deletesensorconfig = deletesensorconfig;
        me->type2interface = type2interface;
        me->mac2zigbeenum = mac2zigbeenum;
        me->deletezigbeeconfig = deletezigbeeconfig;
        me->savezigbeeconfig = savezigbeeconfig;
        me->getsensornum = getsensornum;
        me->getsensorconfig = getsensorconfig;
        me->getzigbeestatus = getzigbeestatus;
        me->setzigbeestatus = setzigbeestatus;
        me->getsystemconfig = getsystemconfig;
        me->setsensorstatus = setsensorstatus;
        me->getsensorcode = getsensorcode;
        me->getsensorratio = getsensorratio;
        me->sensorstatusconfirm = sensorstatusconfirm;
        me->disablecom = disablecom;
        me->deldisablecom = deldisablecom;
        me->checkconfig=checkconfig;
        me->cleanconfigchange = cleanconfigchange;
        return 0;
}

static void DeviceMgmtCleanup(DeviceMgmt * const me)
{
        memset(&me->sensorconfig, 0, sizeof(me->sensorconfig));
        memset(&me->zigbeeconfig, 0, sizeof(me->zigbeeconfig));
}

DeviceMgmt * DeviceMgmtCreate(char *SqliteName)
{
        DeviceMgmt * me = (DeviceMgmt *)Malloc(sizeof(DeviceMgmt));
        strcpy(me->SqliteName, SqliteName);
        if(me != NULL)
        {
                DeviceMgmtInit(me, DeviceMgmtSaveSensorConfig, \
                        DeviceMgmtDeleteSensorConfig,DeviceMgmtType2Interface, \
                        DeviceMgmtMac2Zigbeenum, DeviceMgmtDeleteZigbeeConfig, \
                        DeviceMgmtSaveZigbeeConfig, DeviceMgmtGetSensorNum, \
                        DeviceMgmtGetSensorConfig, DeviceMgmtGetZigbeeStatus, \
                        DeviceMgmtSetZigbeeStatus, DeviceMgmtGetSystemConfig,\
                        DeviceMgmtSetSensorStatus, DeviceMgmtGetSensorCode,\
                        DeviceMgmtGetSensorRatio, DeviceMgmtSensorStatusConfirm,\
                        DeviceMgmtDisableCom, DeviceMgmtDelDisableCom,\
                        DeviceMgmtCheckConfig, DeviceMgmtCleanConfigChange);

                me->sqlite->open(me->sqlite, me->SqliteName);
        }

        return me;
}

void DeviceMgmtDestroy(DeviceMgmt * const me)
{
        if(me != NULL)
        {
                me->sqlite->close(me->sqlite);
                DeviceMgmtCleanup(me);
        }
        Free(me);
}
