
#ifndef DATA_HANDLE_H
#define DATA_HANDLE_H

#include "app_typedef.h"



#define RX_DATA_MAX_BUF_SIZE 100

typedef enum {LITTLE = 1 ,BIG = 2} EU_ENDIAN;

typedef struct uart_data_Pkg uart_data_Pkg;

struct uart_data_Pkg{

	RF_RX_INFO_T rx_pkt_buf[RX_DATA_MAX_BUF_SIZE];
	uint8_t pkg_send_buf[PKG_MAX_LENGTH];
	int send_pkg_seq;
	int rx_pkt_head;
	int rx_pkt_tail;

	FlagStatus bugle_is_set;
	uint8_t bugle_send_buf[8];
	int bugle_send_timeout;
	
	 int (*data_collection)(char buf[], int len); 
	 int (*bugle_collection)(char buf[], int len);
	  int (*bugle_send)();
       //int (*data_collecton)(uart_data_Pkg* const me);
};


int UartListon_DataCollection(char buf[], int len);


#endif



