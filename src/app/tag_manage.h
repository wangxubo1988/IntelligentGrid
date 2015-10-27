
#ifndef _TAG_MANAGE_H
#define _TAG_MANAGE_H

#include <app_typedef.h>

#define SUPPORT_MAX_ACCESS_TAG_NUMBER		200
#define SUPPORT_MAX_TAG_EVENT_NUMBER		200
#define SUPPORT_MAX_TAG_PENDING_NUMBER		5

#pragma pack (1)

typedef struct {
	uint64_t tag_long_addr;							
} tag_info_t; 

typedef struct {
	 rf_tx_info_t rf_tx_info[SUPPORT_MAX_TAG_EVENT_NUMBER];
	 int event_head;
	 int event_tail;
} tag_sent_event_queue_t; 



typedef struct
{
	int16_t report_num_sum_up;
	
	uint8_t logout_num;
	uint8_t register_num;
	uint8_t poweralert_num;
	uint8_t setsleep_num;
	uint8_t unbind_num;
	uint8_t rebinding_num;
	uint8_t wrscreen_num;  //seems to be write screen numbers..
	uint8_t affirm_num;
	uint8_t eveningCmd_num;
	uint8_t disp_lower_power_GUI_num;
	uint8_t firmware_updated_num;
	uint8_t evening_mode_out_num;
	uint8_t awken_failed_num;
}tag_event_t, *ptag_event_t;


typedef enum
{
	/*Store Tag Entry flag Area..*/
	//MIN_INFO_FLAG_UPSHOLD			= 0,

	STORE_EARE_IDLE_FLAG 					= 0,  // ��?���??������?��??����?
	SHORT_PAN_ADDR_REALLOC_FLAG		= 1,	// PAN ��??��?�䨮?����??
	TAG_ONLINE_STATE_NON_CHECK		= 2,  // ��????��2a?����?����??
	TAG_SCREEN_DATA_TYPE_CMD			= 3,	// ?��?����y?Y?a�䨲???��?������??
	TAG_AWAKEN_TRAIL_FAILED_FLAG  = 4,  // ����????D??����?����㨹������?

	//MAX_INFO_FLAG_UPSHOLD			= 7,

	/*Store Tag Event flag Area..*/
	MIN_EVENT_TAG_FALG_LOWSHOLD		= 8,

	REFRESH_DATA_TYPE_CMD_FLAG 		= 8, // ?����??��?������????
	REFRESH_SCREEN_CMD_FLAG				= 9, // ??�����??��?��?��?����?����??
	SET_TAG_SLEEPTIME_CMD_FLAG 		= 10,// ����??����??DY??����???����?����??	
	RELIEVE_BINDING_CMD_FLAG   		= 11,// ?a3y�㨮?��?����?����??	   
	REBINDING_TAG_CMD_FLAG 	   		= 12,// ??�㨮����???����?
	DISPLAY_TAG_LOW_POWER_GUI_FLAG= 13,// ����??����??�̡�3?�̨���?��?????����????
	SET_TAG_EVENING_MODE_FLAG  		= 14,// ����??��1����1�����?�꨺?����????
	UPDATE_TAG_FIREWARE_FLAG			= 15,// ����???��D?3��D������????
	QUERY_TAG_INFO_CMD_FLAG				= 16,// ����??2��?������??D??�����????

	MAX_EVENT_TAG_FALG_UPSHOLD		= 19,

	/*Store Tag Event Response flag Area..*/
	//MIN_EVENT_RESPONSE_FALG_LOWSHOLD	= 20,

	REPORT_TAG_AFFIRM_INFO_FLAG 			= 20,	//��?��������????��?������?D??�� 
	REPORT_TAG_REGISTER_INFO_FLAG			= 21, //��?��������??����2��D??�� 
	RELIEVE_BINDING_FINISH_FLAG 			= 22, //��?����?a�㨮���䨬?D??��
	SET_TAG_SLEEPTIME_FINISH_FLAG 		= 23, //��?��������???��??����??D??��
	REPORT_TAG_LOGOUT_INFO_FLAG				= 24, //��?��������??��???D??��
	REFRESH_SCREEN_FINISH_FLAG  			= 25, //��?��������???��?������3��D??��
	LOW_POWER_ALARM_FLAG		   				= 26,	//��?�����̨���?��?D??��
	REBINDING_TAG_FINISH_FLAG					= 27, //��?����??�㨮?����?D??��
	SET_TAG_EVENING_MODE_FLAG_FINISH 	= 28, //��?������1����1�����?�꨺?���䨬?D??��
	DISPLAY_TAG_LOW_POWER_GUI_FINISH	= 29, //��?�����̨���?��?GUI??��?D??��
	REPORT_TAG_FIREWARE_INFO_FLAG			= 30, //��?��������???��D?3��D�����䨬?D??��
	REPORT_TAG_EVEING_MODE_OUT_FLAG		= 31, //��?��������??�䨮��1����?�꨺????��?y3��?�꨺?���䨬?D??��

	MAX_INFO_FLAG_NUM				= 31,	
}TAG_INFO_FLAG_T;



typedef struct {
	FlagStatus is_pending;
	uint16_t short_addr;
} tag_wake_pending_queue_t; 




typedef struct tag_Manage tag_Manage;

struct tag_Manage{
   tag_info_t tag_info[SUPPORT_MAX_ACCESS_TAG_NUMBER];
   tag_sent_event_queue_t    tag_event_queue;
   tag_wake_pending_queue_t tag_pending_queue[SUPPORT_MAX_TAG_PENDING_NUMBER];
   
   tag_event_t TagEvent;

    int (*tag_get_shortaddr)(uint64_t tag_long_addr, uint16_t *tag_short_addr);
    int (*tag_awake_add)(uint16_t tag_short_addr);
   int (*tag_awake_remove)(uint16_t tag_short_addr);
	
};

#pragma pack ()

extern uint8_t BG_CHANNEL ;					/*bugler broadcast channel*/
extern uint8_t RF_CHANNEL ;					/*bussiness conm. channel*/

extern uint16_t RF_MAC_ADDR ;			/*RF PAN short mac address.*/
extern uint16_t RF_PANID ;					/*RF short pan id*/
extern uint64_t RF_MAC_IEEE_ADDR;


#endif




