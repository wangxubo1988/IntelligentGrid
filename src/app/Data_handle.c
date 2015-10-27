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

#include <app_typedef.h>
#include <Data_handle.h>//usr add
#include <tag_manage.h>



uint8_t cmd1[30]={0x13 ,0x41  ,0x88 ,0x0  ,0xff ,0xff  ,0x0  ,0x0  ,0x1b  ,0x0  ,0xe4  ,0xe5  ,0xf2  ,0x4  ,0x67  ,0x0  ,0x0  ,0xaa};
uint8_t cmd1t[30]={0x17  ,0x61  ,0x88  ,0x0  ,0xff  ,0xff  ,0x1b  ,0x0  ,0x1  ,0x2a  ,0xd4  ,0xd5  ,0xf2  ,0x8  ,0xa1  ,0x0  ,0x5  ,0xb  ,0x0  ,0x0 ,0x0  ,0xaa};

uint8_t cmd2[30] = {0x16  ,0x41  ,0x88  ,0x0  ,0xff  ,0xff  ,0x0  ,0x0  ,0x1b  ,0x0  ,0xb4  ,0xb5  ,0xf4  ,0x7  ,0x67  ,0x0  ,0xa1  ,0xa1  ,0x5  ,0x0  ,0xaa};
uint8_t cmd2t[30] ={0x11   ,0x61   ,0x88   ,0x0   ,0xff   ,0xff   ,0x1b   ,0x0   ,0x1   ,0x2a   ,0xd4   ,0xd5   ,0xf4   ,0x2   ,0xa1   ,0xaa};
uint8_t key1 = 0;
uint8_t key2  = 0;



uart_data_Pkg *uart_dataPkg;




uint16_t u8_u16(uint8_t *data, EU_ENDIAN endian) {
	uint16_t u16_data = 0;

	if (endian == LITTLE ) {
		u16_data = *(data+1);
		u16_data <<= 8;
		u16_data |= *(data+0);	
	} else if (endian == BIG ) {
		u16_data = *(data+0);
		u16_data <<= 8;
		u16_data |= *(data+1);	
	}	

	return (uint16_t)(u16_data);	
}


static void send_buffer_fill(rf_tx_info_t *tx_info)
{
  
	uint8_t length_of_tx_data_without_head, tx_frame_array_index;
	uint8_t *rx_frame;

	uint8_t src_addr_mode = (tx_info->fcf&SRC_ADDR_TYPE)>>SRC_ADDR_FCF_OFFSET;
	uint8_t dst_addr_mode = (tx_info->fcf&DST_ADDR_TYPE)>>DST_ADDR_FCF_OFFSET;
													   
	uart_dataPkg->pkg_send_buf[1] = (uint8_t)tx_info->fcf;// & 0xfb;	  // 11111011
	uart_dataPkg->pkg_send_buf[2] = (uint8_t)(tx_info->fcf>>8);			// FCF.
	uart_dataPkg->pkg_send_buf[3] = uart_dataPkg->send_pkg_seq;					// Sequence Number.               
	uart_dataPkg->pkg_send_buf[4] = (uint8_t)(tx_info->dest_panid);		// Dest. PANID.
	uart_dataPkg->pkg_send_buf[5] = (uint8_t)(tx_info->dest_panid >> 8);	// Dest. PANID.

	if(dst_addr_mode == LONG_ADDR)
	{
		uart_dataPkg->pkg_send_buf[6] = (uint8_t)tx_info->dest_longaddr;		// Dest. Addr.
		uart_dataPkg->pkg_send_buf[7] = (uint8_t)(tx_info->dest_longaddr>>8);	// Dest. Addr.
		uart_dataPkg->pkg_send_buf[8] = (uint8_t)(tx_info->dest_longaddr>>16);	// Dest. Addr.
		uart_dataPkg->pkg_send_buf[9] = (uint8_t)(tx_info->dest_longaddr>>24);	// Dest. Addr.
		uart_dataPkg->pkg_send_buf[10] = (uint8_t)(tx_info->dest_longaddr>>32);		// Dest. Addr.
		uart_dataPkg->pkg_send_buf[11] = (uint8_t)(tx_info->dest_longaddr>>40);	// Dest. Addr.
		uart_dataPkg->pkg_send_buf[12] = (uint8_t)(tx_info->dest_longaddr>>48);		// Dest. Addr.
		uart_dataPkg->pkg_send_buf[13] = (uint8_t)(tx_info->dest_longaddr>>56);	// Dest. Addr.
		uart_dataPkg->pkg_send_buf[14] = (uint8_t)(RF_MAC_ADDR);				// Source Addr.
		uart_dataPkg->pkg_send_buf[15] = (uint8_t)(RF_MAC_ADDR >> 8);			// Source Addr.
		tx_frame_array_index = RF_PACKET_LONG_MHR_SIZE + 1 ;//along with length
	}
	else
	{
		if(src_addr_mode == LONG_ADDR )
		{
			uart_dataPkg->pkg_send_buf[6] = (uint8_t)(tx_info->dest_addr);		// Dest. Addr.
			uart_dataPkg->pkg_send_buf[7] = (uint8_t)(tx_info->dest_addr >> 8) ;	// Dest. Addr.
			uart_dataPkg->pkg_send_buf[8]  = (uint8_t)(RF_MAC_IEEE_ADDR);			// Source Addr.
			uart_dataPkg->pkg_send_buf[9]  = (uint8_t)(RF_MAC_IEEE_ADDR >> 8);		// Source Addr.
			uart_dataPkg->pkg_send_buf[10] = (uint8_t)(RF_MAC_IEEE_ADDR >> 16);		// Source Addr.
			uart_dataPkg->pkg_send_buf[11] = (uint8_t)(RF_MAC_IEEE_ADDR >> 24);		// Source Addr.
			uart_dataPkg->pkg_send_buf[12] = (uint8_t)(RF_MAC_IEEE_ADDR >> 32);		// Source Addr.
			uart_dataPkg->pkg_send_buf[13] = (uint8_t)(RF_MAC_IEEE_ADDR >> 40);		// Source Addr.
			uart_dataPkg->pkg_send_buf[14] = (uint8_t)(RF_MAC_IEEE_ADDR >> 48);		// Source Addr.
			uart_dataPkg->pkg_send_buf[15] = (uint8_t)(RF_MAC_IEEE_ADDR >> 56);		// Source Addr.

			tx_frame_array_index = RF_PACKET_LONG_SRC_ADDR_SIZE + 1;
		}else
		{
			uart_dataPkg->pkg_send_buf[6] = (uint8_t)(tx_info->dest_addr);		// Dest. Addr.
			uart_dataPkg->pkg_send_buf[7] = (uint8_t)(tx_info->dest_addr >> 8) ;	// Dest. Addr.
			uart_dataPkg->pkg_send_buf[8] = (uint8_t)(RF_MAC_ADDR);				// Source Addr.
			uart_dataPkg->pkg_send_buf[9] = (uint8_t)(RF_MAC_ADDR >> 8);			// Source Addr.
			tx_frame_array_index = RF_PACKET_SHORT_MHR_SIZE + 1 ;  
		}
	}

	rx_frame = tx_info->payload;	
	length_of_tx_data_without_head = tx_info->length + 2;


	/* Copy data into the TX frame buffer */
	do {
		uart_dataPkg->pkg_send_buf[tx_frame_array_index++] = *rx_frame++;
	} while (--length_of_tx_data_without_head > 0);

	/* send frame length,join_pkg_send_buf[0] does not including.*/
	uart_dataPkg->pkg_send_buf[0] =  (tx_frame_array_index -1); 

} 

uint8_t* Uartbuss_DataCollection(char buf[], int len)
{
     buf[3] = 0;
      if(0==memcmp(buf,cmd1,len -2) && key1 == 0) 
      	{
     		PrintfRed("recv1");
			key1 = 1;
		return cmd1t;
      	}
	if(0==memcmp(buf,cmd2,len -2) && key2 == 0) 
      	{
     		PrintfRed("recv2");
			key2= 2;
		return cmd2t;
      	}
	return NULL;
}

/*************app¡ý¡ý¡ý**************/



static int app_Rf_NwkSearchRsp(uint64_t TaglongAddr)
{
	uint8_t Sendbuf[15];
	rf_tx_info_t  tx_info;
	prf_header_t pnwkheader = (prf_header_t)Sendbuf;
	papp_nwksearch_t pnwksearch = (papp_nwksearch_t)(Sendbuf + sizeof(rf_header_t));

	/*look up addrrss pool & then check weather a (viladited) net-addr is availabe\
	  no has available,no need to response.*/
	//if(gw_has_avaliable_short_addr() == FALSE)
	//	return FAILED;

	/*in frame control area, fill long_src_addr and set no-need-ack*/
	tx_info.fcf = FCF_NOACK_DST_LONG_DATA;
	tx_info.dest_panid = BROADCAST_ADDR;
	tx_info.dest_longaddr = TaglongAddr;
	tx_info.length = sizeof(rf_header_t) + sizeof(app_nwksearch_t);
	tx_info.payload = Sendbuf;

	pnwkheader->head = NWK_RESPONSE_HEAD;
	pnwkheader->cmd = NWK_SEARCH;
	pnwkheader->length = sizeof(app_nwksearch_t);
	
	/*Tell gw pan attribute to tag.both panid & rf_mac are needed*/
	//pnwksearch->status = gateway.status;
	pnwksearch->devType = RFID_GATEWAY;
	pnwksearch->nwkPanid = RF_PANID; 
	pnwksearch->nkwAddr	 = RF_MAC_ADDR;
	pnwksearch->tail = TAIL;
	
	/*send response to tag in common-channel*/
	send_buffer_fill(&tx_info);
	uart_dataPkg->send_pkg_seq++;
	
	return SUCCESS;
}

void send_test()
{
app_Rf_NwkSearchRsp(0);

}
static int app_Rf_NwkJoinRsp(uint64_t TaglongAddr,uint8_t *pData)
{	
	int8_t stat;
	uint8_t Sendbuf[10];
	rf_tx_info_t  tx_info;
	
	prf_header_t pnwkheader = (prf_header_t)Sendbuf;
	papp_joinrequest_t pjoinreq = (papp_joinrequest_t)pData;
	papp_joinresponse_t pnwkjoin = (papp_joinresponse_t)(Sendbuf + sizeof(rf_header_t));
	uint16_t tagshortAddr = 0;

      tag_Manage *tag_manage = (tag_Manage *)getTag_Mange();
	if((stat = tag_manage->tag_get_shortaddr(TaglongAddr, &tagshortAddr))==FAILED)//failed   
	{
		return stat;
	}
  
	tx_info.fcf = FCF_NOACK_DST_LONG_DATA;
	tx_info.dest_panid = RF_PANID;
	tx_info.dest_longaddr = TaglongAddr;
	tx_info.length = sizeof(rf_header_t) + sizeof(app_joinresponse_t);
	tx_info.payload = Sendbuf;

	pnwkheader->head = NWK_RESPONSE_HEAD;
	pnwkheader->cmd = NWK_JOIN;
	pnwkheader->length = sizeof(app_joinresponse_t);


	pnwkjoin->devType = RFID_GATEWAY;
	pnwkjoin->tagAddr = tagshortAddr;
	pnwkjoin->bugle_channel = BG_CHANNEL;
	pnwkjoin->bussiness_channel = RF_CHANNEL;
	pnwkjoin->tail = TAIL;

       send_buffer_fill(&tx_info);
	uart_dataPkg->send_pkg_seq++;
	
      test_printf("add tag", (uint8_t*)&TaglongAddr, 8);
	return stat;
}

static int app_Rf_NwkQueryRsp(uint16_t tagaddr, uint8_t *pData)
{
      int8_t stat = SUCCESS;
     tag_Manage *test_tag_manage = (tag_Manage *)getTag_Mange();
   
     test_tag_manage->tag_awake_remove(tagaddr);

      uint8_t Sendbuf[64];	 
      rf_tx_info_t  tx_info;
	prf_header_t pnwkheader = (prf_header_t)Sendbuf;
	papp_req_query_t queryreq = (papp_req_query_t)pData;
	uint8_t *pApayload = (uint8_t*)(Sendbuf + sizeof(rf_header_t));
	
	 tx_info.fcf = FCF_NOACK_DST_SHORT_DATA; 
	 tx_info.dest_panid = RF_PANID;
	tx_info.dest_addr = tagaddr;
	tx_info.payload = Sendbuf;

	pnwkheader->head = NWK_RESPONSE_HEAD;
	pnwkheader->cmd = NWK_QUERY;
	pnwkheader->length = 2;
		
	tx_info.length = sizeof(rf_header_t) + 2;

	*pApayload++ = DATATYPE_NULL_JOB ;	  // no action ..
	*pApayload = TAIL;

	   send_buffer_fill(&tx_info);
	uart_dataPkg->send_pkg_seq++;
     PrintfRed("set tag sleep");
     return stat;



}
int8_t app_Rf_Nwk_Recv_Request_Packet_Process(uint8_t cmd, uint8_t *pData, uint64_t tagaddr)
{
	int8_t stat = SUCCESS;

	switch(cmd)
	{
	case NWK_SEARCH:
		stat = app_Rf_NwkSearchRsp(tagaddr);
		break;
	case NWK_JOIN:
	       stat = app_Rf_NwkJoinRsp(tagaddr,pData);
		break;
	case NWK_QUERY:
		stat = app_Rf_NwkQueryRsp((uint16_t)tagaddr, pData);
	      // rf_bugle_remove(tagaddr);
		break;
	case NWK_RETRANS:
		//stat = app_Rf_NwkRetransRsp((uint16_t)tagaddr, pData);
	 // rf_bugle_remove(tagaddr);
		break;
	default:
		break;
	}

	return stat;
}

static int8_t PacketsRecv_RequestResponse(uint8_t *pMacData, uint64_t tagaddr)
{
	prf_header_t rfheader = (prf_header_t)pMacData;
	uint8_t *pData = (uint8_t*)(pMacData + sizeof(rf_header_t));
	int8_t stat = SUCCESS;

	switch(rfheader->head)
	{
	case NWK_REQUEST_HEAD:
		stat = app_Rf_Nwk_Recv_Request_Packet_Process(rfheader->cmd, pData, tagaddr);
		break;
	case CMD_RESPONSE_HEAD://response from rf
		//stat = app_Rf_Cmd_Recv_Response_Packet_Process(rfheader->cmd, pData, tagaddr);
		break;
	default:
		break;
	}
	return stat;
}

int8_t app_Rf_Recv_Packet_Process(RF_RX_INFO_T *rf_rx_info)
{
	uint8_t *pMacData = NULL;
	uint64_t TagAddr = 0;
	if(((rf_rx_info->fcf&SRC_ADDR_TYPE)>>SRC_ADDR_FCF_OFFSET)==LONG_ADDR) 
	{
		pMacData = &rf_rx_info->payload[MAC_HEAD_LONG_SRC_OFFSET];	//length is contained.
		memcpy((uint8_t*)&TagAddr, &rf_rx_info->payload[SRC_ADDR_OFFSET], 8);
	
	}
	else
	{
		uint8_t seq = 0;
		uint16_t recvToken;
		
		pMacData= &rf_rx_info->payload[MAC_HEAD_SHORT_SRC_OFFSET];
		memcpy((uint8_t*)&TagAddr, &rf_rx_info->payload[SRC_ADDR_OFFSET], 2);
		
		recvToken = u8_u16(&rf_rx_info->payload[MAC_SHORT_SRC_TOKEN_OFFSET], BIG);
	}		
	return PacketsRecv_RequestResponse(pMacData, TagAddr);
}

/*************app¡ü¡ü¡ü*************/
static int Uart_DataCollection(char buf[], int len)
{
  /*PKG length check*/
  if(len<PKG_MIN_LENGTH ||
 	( len > PKG_MAX_LENGTH  + PGK_TAIL_OPPEND_LENGTH)) return;
 /*PKG corrent check*/
  if(buf[0] +1 != len || buf[len - 3]  !=TAIL) return;


  rf_rx_frame_t rxframe;
 RF_RX_INFO_T rf_rx_info;
 
 rxframe.length = buf[0];
 memcpy(&rxframe.data[0], &buf[0 + PKG_LENGTH_HEAD], len -  PKG_LENGTH_HEAD - PGK_TAIL_OPPEND_LENGTH);
 rxframe.lqi =buf[ len - PGK_TAIL_OPPEND_LENGTH];

if (((rxframe.data[0] & FRAME_TYPE_MASK) != FRAME_TYPE_DATA)
			&&((rxframe.data[0] & FRAME_TYPE_MASK) != FRAME_TYPE_MAC_COMMAND))  return;

		
rf_rx_info.fcf = u8_u16(&rxframe.data[0], LITTLE );


if(((rf_rx_info.fcf&SRC_ADDR_TYPE)>>SRC_ADDR_FCF_OFFSET) != LONG_ADDR && 
	((rf_rx_info.fcf&SRC_ADDR_TYPE)>>SRC_ADDR_FCF_OFFSET) != SHORT_ADDR) return;

 rf_rx_info.seq_number = rxframe.data[2]; 
 rf_rx_info.length = rxframe.length -2;
 rf_rx_info.lqi = rxframe.lqi;
memcpy(&rf_rx_info.payload[0], &rxframe.data, rf_rx_info.length);

//uart_dataPkg->rx_pkt_buf[uart_dataPkg->rx_pkt_tail] = rf_rx_info;
//uart_dataPkg->rx_pkt_tail = (uart_dataPkg->rx_pkt_tail + 1) % RX_DATA_MAX_BUF_SIZE;

return app_Rf_Recv_Packet_Process(&rf_rx_info);
}


static int8_t bugle_Packet_Process(prf_bugle_recv_t resp)
{
	int8_t stat = SUCCESS;

	memset(uart_dataPkg->bugle_send_buf, 0, 8);
       uart_dataPkg->bugle_send_timeout = 0;
	   
	switch(resp->cmd)
	{
	case C_RECV_REPLY:
		PrintfGreen("added bugle addr\n");
		stat = 0;
	break;
	case C_CFG_REPLY:
		PrintfGreen("C_CFG_REPLY\n");
		uart_dataPkg->bugle_is_set= SET;
       break;

       case C_NOTE_REPLY:
		PrintfGreen("removed bugle addr\n");
       break;
		
       case C_TMOUT_REPLY:
	   		{
	   	 tag_Manage *test_tag_manage = (tag_Manage *)getTag_Mange();
   	       test_tag_manage->tag_awake_remove(resp->tagaddr);
		PrintfGreen("bugle_timeout\n");
       	}
       break;
	default:
		break;
	}
	return stat;
}

static int Bugle_DataCollection(char buf[], int len)
{
    if(buf[0] == C_SYNC_HEAD && buf[len - 1] == C_SYNC_TAIL)
    {
          prf_bugle_recv_t resp = (prf_bugle_recv_t)buf;
	   return bugle_Packet_Process(resp);
   }
   return FAILED;
}


static int Bugle_Datasend(void)
{
   int send_state = 1;
   if(uart_dataPkg->bugle_send_buf[0] != C_SYNC_HEAD) return send_state;
   
  if((uart_dataPkg->bugle_send_timeout)%100 == 0)
  {
	send_state  = 0;
  }
   uart_dataPkg->bugle_send_timeout++;
   return send_state;
   
}


int serial_bugle_init()
{	
	prf_bugle_send_pkt_t init_pkg = (prf_bugle_send_pkt_t)uart_dataPkg->bugle_send_buf;
	init_pkg->head = C_SYNC_HEAD;
	init_pkg->cmd = C_INIT_CMD;
	init_pkg->tagaddr = RF_MAC_ADDR;
	init_pkg->U16_info = RF_PANID;
	init_pkg->U8_info = BG_CHANNEL;
	init_pkg->tail = C_SYNC_TAIL;
	return 0;
}

static void uartPKGCleanup(uart_data_Pkg * const me)
{
  memset((uint8_t*)&((me->rx_pkt_buf[0]).fcf), 0, sizeof(RF_RX_INFO_T)*RX_BUFF_SIZE);
  memset( me->pkg_send_buf, 0, PKG_MAX_LENGTH);
  memset( me->bugle_send_buf, 0, 8);
  me->send_pkg_seq = 0;
  me->rx_pkt_head = 0;
  me->rx_pkt_tail = 0;
 
  me->bugle_is_set = RESET;
  me->bugle_send_timeout = 0;
  
  me->bugle_collection = NULL;
  me->data_collection =NULL;
}

void UartPKGInit(uart_data_Pkg * const  me, int (*datacollection)(char buf[], int len), int (*buglecollection)(char buf[], int len), int (*buglesend)())
{
  uartPKGCleanup(me);
     
  me->data_collection = datacollection;
  me->bugle_collection= buglecollection;
  me->bugle_send = buglesend;
}


uart_data_Pkg *getUartCollection()
{
	 return uart_dataPkg;
}

void  UartCollectionInit()
{
 uart_dataPkg= (uart_data_Pkg *)Malloc(sizeof(uart_data_Pkg));
        
  UartPKGInit(uart_dataPkg, 
  	                                      Uart_DataCollection, 
  	                                      Bugle_DataCollection, Bugle_Datasend);
}



void UartCollectionUnInitialize()
{

  if(uart_dataPkg != NULL) uartPKGCleanup(uart_dataPkg);  
  Free(uart_dataPkg);
}









	

