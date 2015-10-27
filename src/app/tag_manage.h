
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

	STORE_EARE_IDLE_FLAG 					= 0,  // ¡ä?¡ä¡é??¨®¨°¨º?¡¤??¨¦¨®?
	SHORT_PAN_ADDR_REALLOC_FLAG		= 1,	// PAN ¦Ì??¡¤?¡ä¨®?¡À¨º??
	TAG_ONLINE_STATE_NON_CHECK		= 2,  // ¨¤????¨¬2a?¨¢¡À?¡À¨º??
	TAG_SCREEN_DATA_TYPE_CMD			= 3,	// ?¡é?¨¢¨ºy?Y?a¡ä¨²???¡é?¨¢¡À¨º??
	TAG_AWAKEN_TRAIL_FAILED_FLAG  = 4,  // ¡À¨º????D??¨¹¨¢?¨º¡ì¡ã¨¹¡À¨º¨º?

	//MAX_INFO_FLAG_UPSHOLD			= 7,

	/*Store Tag Event flag Area..*/
	MIN_EVENT_TAG_FALG_LOWSHOLD		= 8,

	REFRESH_DATA_TYPE_CMD_FLAG 		= 8, // ?¨¹¨¢??¡é?¨¢¡À¨º????
	REFRESH_SCREEN_CMD_FLAG				= 9, // ??¡¤¡é¡Á??¡ê?¡é?¨¢?¨¹¨¢?¡À¨º??
	SET_TAG_SLEEPTIME_CMD_FLAG 		= 10,// ¨¦¨¨??¡À¨º??DY??¨º¡À???¨¹¨¢?¡À¨º??	
	RELIEVE_BINDING_CMD_FLAG   		= 11,// ?a3y¡ã¨®?¡§?¨¹¨¢?¡À¨º??	   
	REBINDING_TAG_CMD_FLAG 	   		= 12,// ??¡ã¨®¡À¨º???¨¹¨¢?
	DISPLAY_TAG_LOW_POWER_GUI_FLAG= 13,// ¨¦¨¨??¡À¨º??¦Ì¡Â3?¦Ì¨ª¦Ì?¨¢?????¡À¨º????
	SET_TAG_EVENING_MODE_FLAG  		= 14,// ¨¦¨¨??¨°1¨ª¨ª1¡è¡Á¡Â?¡ê¨º?¡À¨º????
	UPDATE_TAG_FIREWARE_FLAG			= 15,// ¨¦¨¨???¨¹D?3¨¬D¨°¡À¨º????
	QUERY_TAG_INFO_CMD_FLAG				= 16,// ¨¦¨¨??2¨¦?¡¥¡À¨º??D??¡é¡À¨º????

	MAX_EVENT_TAG_FALG_UPSHOLD		= 19,

	/*Store Tag Event Response flag Area..*/
	//MIN_EVENT_RESPONSE_FALG_LOWSHOLD	= 20,

	REPORT_TAG_AFFIRM_INFO_FLAG 			= 20,	//¨¦?¡À¡§¡À¨º????¦Ì?¨¨¡¤¨¨?D??¡é 
	REPORT_TAG_REGISTER_INFO_FLAG			= 21, //¨¦?¡À¡§¡À¨º??¡Á¡é2¨¢D??¡é 
	RELIEVE_BINDING_FINISH_FLAG 			= 22, //¨¦?¡À¡§?a¡ã¨®¡Á¡ä¨¬?D??¡é
	SET_TAG_SLEEPTIME_FINISH_FLAG 		= 23, //¨¦?¡À¡§¨¦¨¨???¡¥??¨º¡À??D??¡é
	REPORT_TAG_LOGOUT_INFO_FLAG				= 24, //¨¦?¡À¡§¡À¨º??¨¤???D??¡é
	REFRESH_SCREEN_FINISH_FLAG  			= 25, //¨¦?¡À¡§¡À¨º???¡é?¨¢¨ª¨º3¨¦D??¡é
	LOW_POWER_ALARM_FLAG		   				= 26,	//¨¦?¡À¡§¦Ì¨ª¦Ì?¨¢?D??¡é
	REBINDING_TAG_FINISH_FLAG					= 27, //¨¦?¡À¡§??¡ã¨®?¨¹¨¢?D??¡é
	SET_TAG_EVENING_MODE_FLAG_FINISH 	= 28, //¨¦?¡À¡§¨°1¨ª¨ª1¡è¡Á¡Â?¡ê¨º?¡Á¡ä¨¬?D??¡é
	DISPLAY_TAG_LOW_POWER_GUI_FINISH	= 29, //¨¦?¡À¡§¦Ì¨ª¦Ì?¨¢?GUI??¨º?D??¡é
	REPORT_TAG_FIREWARE_INFO_FLAG			= 30, //¨¦?¡À¡§¡À¨º???¨¹D?3¨¬D¨°¡Á¡ä¨¬?D??¡é
	REPORT_TAG_EVEING_MODE_OUT_FLAG		= 31, //¨¦?¡À¡§¡À¨º??¡ä¨®¨°1¨ª¨ª?¡ê¨º????¡ä?y3¡ê?¡ê¨º?¡Á¡ä¨¬?D??¡é

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




