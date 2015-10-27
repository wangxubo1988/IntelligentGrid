
#include <Data_handle.h>//usr add
#include <tag_manage.h>
#include <app_typedef.h>

#include <uart.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <misc.h>
#include <stdio.h>
#include<netinet/in.h>
#include <misc.h>
#include <mysqlite.h>
#include <FuncPKG.h>
#include <time.h>
#include <DataPKG.h>

uint8_t BG_CHANNEL = 0x10;					/*bugler broadcast channel*/
uint8_t RF_CHANNEL = 0x5;					/*bussiness conm. channel*/

uint16_t RF_MAC_ADDR = 0x2a02;			/*RF PAN short mac address.*/
uint16_t RF_PANID = 0xFFFF;					/*RF short pan id*/
uint64_t RF_MAC_IEEE_ADDR = 0xFFFFFFFFFFFFFFFELL;

volatile uint16_t alloct_tag_short_addr = 0x0000;



tag_Manage *tag_management;


int tag_access_get_short_address(uint64_t tag_long_addr, uint16_t *tag_short_addr)
{
	int ret = 0;
	
	uint16_t search_index;
	uint16_t tag_info_store_index;
	
	if ( tag_short_addr == NULL)  return -1;
	
	for (search_index=0; search_index < SUPPORT_MAX_ACCESS_TAG_NUMBER; search_index++) 
      	{
		if(tag_management->tag_info[search_index].tag_long_addr == tag_long_addr)
		{
			*tag_short_addr = search_index + 1;
			return SUCCESS;
		}
	}

	for (search_index=0; search_index < SUPPORT_MAX_ACCESS_TAG_NUMBER; search_index++) 
      	{
		if(tag_management->tag_info[search_index].tag_long_addr == 0 && (RF_MAC_ADDR != search_index + 1))
		{
			*tag_short_addr = search_index + 1;
			tag_management->tag_info[search_index].tag_long_addr = tag_long_addr;
			return SUCCESS;
		}
	}
	return FAILED;
}




int tag_sent_event_add(rf_tx_info_t*  txinfo)
{
       int list_head = tag_management->tag_event_queue.event_head;
	int list_tail = tag_management->tag_event_queue.event_tail; 


}

int tag_awake_add_addr(uint16_t tag_short_addr)
{
	int ret = 0;
	
	uint16_t search_index;
	
	if(tag_management->tag_info[tag_short_addr - 1].tag_long_addr == 0) return FAILED;

	uart_data_Pkg *uart_Pkg = (uart_data_Pkg *)getUartCollection();
	prf_bugle_send_pkt_t add_pkg = (prf_bugle_send_pkt_t)uart_Pkg->bugle_send_buf;
       if(add_pkg->head != 0) return FAILED;
	add_pkg->head = C_SYNC_HEAD;
	add_pkg->cmd = C_SEND_CMD;
	add_pkg->tagaddr = tag_short_addr;
	add_pkg->U16_info = 6000;
	add_pkg->U8_info = 0;
	add_pkg->tail = C_SYNC_TAIL;

	return SUCCESS;
}

int tag_awake_remove_addr(uint16_t tag_short_addr)
{
	int ret = 0;
	
	uint16_t search_index;

	if(tag_management->tag_info[tag_short_addr - 1].tag_long_addr == 0) return FAILED;

	uart_data_Pkg *uart_Pkg = (uart_data_Pkg *)getUartCollection();
	prf_bugle_send_pkt_t add_pkg = (prf_bugle_send_pkt_t)uart_Pkg->bugle_send_buf;
       if(add_pkg->head != 0) return FAILED;
	add_pkg->head = C_SYNC_HEAD;
	add_pkg->cmd = C_REMOVE_CMD;
	add_pkg->tagaddr = tag_short_addr;
	add_pkg->U16_info = 0;
	add_pkg->U8_info = 0;
	add_pkg->tail = C_SYNC_TAIL;

	return SUCCESS;
}



static void Tag_MangeCleanup(tag_Manage * const me)
{
   memset((uint8_t*)me, 0, sizeof(tag_Manage));
   
}

void tagFuncInit(tag_Manage * const  me, int (*tag_getshortaddr)(uint64_t tag_long_addr, uint16_t *tag_short_addr),  
										  int (*tag_awakeadd)(uint16_t tag_short_addr),
										   int (*tag_awakeremove)(uint16_t tag_short_addr))
{
  Tag_MangeCleanup(me);
  me->tag_get_shortaddr = tag_getshortaddr;
  me->tag_awake_add = tag_awakeadd;
  me->tag_awake_remove = tag_awakeremove;
}


tag_Manage* getTag_Mange()
{
	 return tag_management;
}

void  Tag_Mange_init()
{
 tag_management= (tag_Manage *)Malloc(sizeof(tag_Manage));
        
  tagFuncInit(tag_management,
  							tag_access_get_short_address,
  							tag_awake_add_addr,
  							tag_awake_remove_addr);
}



void Tag_Mange_UnInitialize()
{

  if(tag_management != NULL) Tag_MangeCleanup(tag_management);  
  Free(tag_management);
}






