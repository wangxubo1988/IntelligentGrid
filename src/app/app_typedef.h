
#ifndef _APP_TYPEDEF_H
#define _APP_TYPEDEF_H

#include <stdint.h>
#include <stdio.h>
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;

typedef enum {SUCCESS = 0, FAILED = !SUCCESS} RESULT_STATUS;
typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

#define PKG_MIN_LENGTH   5
#define PKG_MAX_LENGTH 64

#define PKG_LENGTH_HEAD 	          1
#define PGK_TAIL_OPPEND_LENGTH    2

#define RX_BUFF_SIZE         100



#define RF_PACKET_SHORT_MHR_SIZE 			9	//(2 + 1 + 2 + 2 + 2)
#define RF_PACKET_LONG_MHR_SIZE 			15	//(2 + 1 + 2 + 2 + 2)
#define RF_PACKET_LONG_SRC_ADDR_SIZE		15
#define RF_PACKET_MHR_SIZE 					9	//(2 + 1 + 2 + 2 + 2)


#define LONG_ADDR		3
#define SHORT_ADDR		2

#define DST_ADDR_TYPE   0x0c00
#define SRC_ADDR_TYPE   0xc000

#define MAC_HEAD_LONG_SRC_OFFSET		  15
#define MAC_HEAD_SHORT_SRC_OFFSET	    9
#define MAC_SHORT_SRC_TOKEN_OFFSET		14

#define DST_ADDR_FCF_OFFSET	10
#define SRC_ADDR_FCF_OFFSET 14

#define SRC_ADDR_OFFSET  7
#define DST_ADDR_OFFSET	 0


#define RF_PACKET_LONG_HEAD_SIZE         17       //    ((2 + 1 + 2 + 8 + 2) + (2))
#define RF_PACKET_SHOR_THEAD_SIZE		11    //    ((2 + 1 + 2 + 2 + 2) + (2))


#define BROADCAST_ADDR				0xFFFF
#define BROADCAST_LONG_ADDR			0xFFFFFFFFFFFFFFFF

#define TAIL										((uint8_t)0xAA)


#pragma pack (1)

typedef enum
{
	RFID_GATEWAY =	1,
	RFID_NODE		= 2,
	RFID_OTHER,
}DEVICE_TYPE_T;


typedef enum {
	FRAME_TYPE_BEACON = 0,
	FRAME_TYPE_DATA = 1,
	FRAME_TYPE_ACKNOWLEDGE = 2,
	FRAME_TYPE_MAC_COMMAND = 3,	
	FRAME_TYPE_MASK = 0x07,
} FRAME_TYPE;


typedef enum
{
    CMD_REQUEST_HEAD	  = 0xc5c4,
    CMD_RESPONSE_HEAD	  = 0xb5b4,
    NWK_REQUEST_HEAD	  = 0xe5e4,
    NWK_RESPONSE_HEAD	  = 0xd5d4,
	//PEER_RESPONSE_HEAD	  = 0xf5f4,
}FRAME_HEAD_CODE;

typedef enum
{
	FCF_NOACK_DST_LONG_DATA  = 0x8c41,
	FCF_ACK_DST_SHORT_DATA   = 0x8861,
	FCF_NOACK_DST_SHORT_DATA = 0x8841,
}FCF_FRAME_FILL_CMD;


typedef enum
{
    NWK_SEARCH    = 0xf0,
    NWK_JOIN      = 0xf1,
    NWK_QUERY     = 0xf2,
   NWK_RETRANS		= 0xf3,
    NWK_ACK			  = 0xf4,
}SEND_PACKET_TYPE;//D-¨°¨¦?¨¹¨¢???

typedef struct {
	uint8_t length;
	uint8_t data[PKG_MAX_LENGTH -PKG_LENGTH_HEAD];
	uint8_t lqi;
	uint8_t crc;
}rf_rx_frame_t;

typedef struct {
	uint16_t fcf;		
	uint8_t seq_number;	
	uint8_t length;			
	uint8_t payload[PKG_MAX_LENGTH -PKG_LENGTH_HEAD];		
	uint8_t lqi;
} RF_RX_INFO_T;


typedef struct {
	uint16_t dest_panid;	
	uint16_t dest_addr;	
	uint16_t fcf;
	uint64_t dest_longaddr;
	uint8_t *payload;		
	uint8_t length;			
} rf_tx_info_t;

typedef struct
{
	uint16_t head;    //type of header
	uint8_t  cmd;     //command type
	uint8_t  length;  //length of body,not including header.
}rf_header_t, *prf_header_t;

typedef struct
{
       uint8_t   devType;
	uint8_t   status; 
	uint8_t   tail;
}app_search_req_t, *papp_search_req_t;

typedef struct
{
	uint8_t   devType;
	uint16_t  nwkPanid;
	uint16_t  nkwAddr;
	uint8_t   tail;
} app_nwksearch_t, *papp_nwksearch_t;


typedef struct
{
	uint8_t   devType;
        uint8_t   firmware_version;
        uint32_t  sleeptime;
	uint8_t   tail;
}app_join_req_t,*papp_join_req_t;


typedef struct
{
	uint8_t devType;
	uint8_t firmware_version;
	uint32_t sleeptime;
	uint8_t tail;
} app_joinrequest_t,*papp_joinrequest_t;


typedef struct	   
{
	uint8_t   devType;
	uint16_t  tagAddr;
	uint8_t   bugle_channel;      //??D??¨¤¨¬yD?¦Ì¨¤
	uint8_t	  bussiness_channel;  //¨º???D?¦Ì¨¤
	uint8_t   tail;
} app_joinresponse_t,*papp_joinresponse_t;


typedef struct
{
	uint16_t  token;
	uint8_t   power;
	uint8_t   tail;
} app_req_query_t,*papp_req_query_t;

typedef enum{
	C_SYNC_HEAD  = 0x5A,
	C_SYNC_TAIL  = 0x5B,
	
	C_INIT_CMD	 = 0x00,
	C_SEND_CMD	 = 0x11,
	C_REMOVE_CMD = 0x22,
	
	C_RECV_REPLY = 0x66,
	C_CFG_REPLY  = 0x77,
	C_NOTE_REPLY = 0x88,
	C_TMOUT_REPLY= 0x99,
	
}FRAME_CODE_T;

typedef enum
{   
    DATATYPE_NULL_JOB      	= 0x00,
    DATATYPE_SCREEN_DATE   	= 0x01,
	DATATYPE_FIREWARE_DATA 	= 0x02,
	TAG_KICKE_OUT_FROM_NET 	= 0x03,
	EXCEPTION_NOTICE_FLAG	 = 0x04,
}QUERY_DATA_RESPONSE_TYPE;  //return DataType of query


typedef struct{
  uint8_t head;
  uint8_t cmd;
  uint16_t tagaddr;
  uint16_t U16_info;
  uint8_t  U8_info;
  uint8_t tail;
} rf_bugle_recv_t,*prf_bugle_recv_t;

typedef struct {
	uint8_t head; 
	uint8_t cmd;
	uint16_t tagaddr;
	uint16_t U16_info;
	uint8_t  U8_info;
	uint8_t tail;
} rf_bugle_send_pkt_t,*prf_bugle_send_pkt_t;




#pragma pack ()


#define SERCH_PKT_LEN  (sizeof(rf_header_t) + sizeof(app_search_req_t) + RF_PACKET_LONG_HEAD_SIZE)
#define JOIN_PKT_LEN     (sizeof(rf_header_t) + sizeof(app_join_req_t) + RF_PACKET_LONG_HEAD_SIZE)

#endif

