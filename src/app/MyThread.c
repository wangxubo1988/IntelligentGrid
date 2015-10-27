#include <misc.h>
#include <time.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <limits.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <IEC103.h>
#include <uart.h>
#include <reportdata.h>
#include <log.h>
#include <mysocket.h>
#include <DataCollection.h>
#include <FuncPKG.h>
#include <xmlparse.h>


#include <Data_handle.h>//usr add
#include <tag_manage.h>
void * UartThread(void);
void * tags_test(void);

void * CommandsIssued(void);
void * Communications(void);
void * CheckConfigThread(void);
void * Get3GSignalThread(void);

int SystemStart(void)
{
        pthread_t Uart_ThreadId;
        pthread_t tags_test_ThreadId;
        pthread_t CommandsIssuedId;
        //pthread_t CommunicationsId;
        pthread_t CheckConfigThreadId;
        //pthread_t Get3GSignalThreadId;
        
        if(pthread_create(&Uart_ThreadId, NULL,  (void *) UartThread, NULL) != 0)  return -1; 
       // if(pthread_create(&tags_test_ThreadId, NULL,  (void *) tags_test, NULL) != 0)  return -1; 
		
       // if(pthread_create(&CommandsIssuedId, NULL, \
    //            (void *) CommandsIssued, NULL) != 0)
     //   {
  //              return -1;
  //      }
		/*
        if(pthread_create(&CommunicationsId, NULL, \
                (void *) Communications, NULL) != 0)
        {
                return -1;
        }*/

   //     if(pthread_create(&CheckConfigThreadId, NULL, \
   //             (void *) CheckConfigThread, NULL) != 0)
   //     {
  //              return -1;
 //       }
		/*
        if(pthread_create(&Get3GSignalThreadId, NULL, \
                (void *) Get3GSignalThread, NULL) != 0)
        {
                return -1;
        }*/
        
        return 0;

 }

void test_printf(char* message, char buf[], int len)
{
   int i;
    PrintfGreen("%s", message);
    for(i=0;i<len;i++)
            printf("%02X ",buf[i]);
    printf("\n");


}


int tv_read1;
void test_time(int enter)
{
struct timeval tv_busy;
int tm;
  gettimeofday(&tv_busy, NULL);
  tm = tv_busy.tv_sec*1000*1000 + tv_busy.tv_usec;
   if(enter == 0) {
		tv_read1 = tm;
   }else if (enter == 1)
   {
		PrintfGreen("time diff %d\n", tm - tv_read1);
   }

}


uint8_t  test_sdata[64]={0x3f,0,0,1,2,3,4,5,6,7,8,9,10,
															 1,2,3,4,5,6,7,8,9,10,
															 1,2,3,4,5,6,7,8,9,10,
															 1,2,3,4,5,6,7,8,9,10,
														 	  1,2,3,4,5,6,7,8,9,10,
															 1,2,3,4,5,6,7,8,9,10,0xaa};

void * UartThread(void)
{      
      int time_cnt = 0;
        myuart *uart_join = myuartCreate();
        uart_join->config.port = "/dev/ttyS1";
        uart_join->config.speed = 115200;
        uart_join->config.flow_ctrl = 0;
        uart_join->config.databits = 8;
        uart_join->config.stopbits = 1;
        uart_join->config.parity = 'N';
        uart_join->open(uart_join);

	 myuart *uart_buss = myuartCreate();
        uart_buss->config.port = "/dev/ttyS2";
        uart_buss->config.speed = 115200;
        uart_buss->config.flow_ctrl = 0;
        uart_buss->config.databits = 8;
        uart_buss->config.stopbits = 1;
        uart_buss->config.parity = 'N';
        uart_buss->open(uart_buss);

	 myuart *uart_bugle = myuartCreate();
        uart_bugle->config.port = "/dev/ttyS3";
        uart_bugle->config.speed = 115200;
        uart_bugle->config.flow_ctrl = 0;
        uart_bugle->config.databits = 8;
        uart_bugle->config.stopbits = 1;
        uart_bugle->config.parity = 'N';
        uart_bugle->open(uart_bugle);

	uart_data_Pkg *uart_Pkg;
	UartCollectionInit();
       uart_Pkg =  getUartCollection();

	//serial_bugle_init();
        while(1)
        {     
		  /*join ¡ý*/
                if(uart_join->readn(uart_join) > 0)		
                {  
			test_printf("nwk_chn_recv:", uart_join->buffer, uart_join->len) ;
			uart_join->len = 64;
			uart_join->writen(uart_join);
                }

		 if(uart_buss->readn(uart_buss) > 0)		
                {  
			test_printf("buss_chn_recv:", uart_buss->buffer, uart_buss->len) ;
			uart_buss->len = 64;
			uart_buss->writen(uart_buss);
                }
		 

		/*bugle ¡ý*/
		  uart_bugle->len = 1000;	
		  if(uart_bugle->readn(uart_bugle) > 0)
                {    
                    test_printf("uart_bugle_recv:", uart_bugle->buffer, uart_bugle->len) ;
                   uart_bugle->buffer[0] -=2;
                  	 uart_bugle->len  = 64;
			uart_bugle->writen(uart_bugle);
                }

                usleep(10000);
        }
        UartCollectionUnInitialize();
        myuartDestroy(uart_join);
	 myuartDestroy(uart_buss);
	 myuartDestroy(uart_bugle);
        return NULL;
}




void * tags_test(void)
{
  Tag_Mange_init();
   tag_Manage *test_tag_manage = (tag_Manage *)getTag_Mange();
   int t = 0;
      while(1)
      	{
      	  uint16_t search_index;
	
	 for (search_index=0; search_index < SUPPORT_MAX_ACCESS_TAG_NUMBER; search_index++) 
       {
		if(test_tag_manage->tag_info[search_index].tag_long_addr != 0)
		{
		     // PrintfGreen("current tag addr:%-2x", search_index+1);
		    //  test_printf("now curent tag mac", (uint8_t*)&(test_tag_manage->tag_info[search_index].tag_long_addr), 8) ;
		      if(t<4) t++;
		      if(t == 4) {
			  	test_tag_manage->tag_awake_add( search_index+1);
				t=0;
		      	}
		}
	 }
		 usleep(5000000);

      }
 Tag_Mange_UnInitialize();
 return NULL;
}




void * CommandsIssued(void)
{

        mysocket *cmdsocket = mysocketCreate();
        Resolver *cmdresolver = ResolverCreate();//define in Xmlparse.h
        strcpy(cmdsocket->ip, deviceMgmt->systemconfig.server.IP);
        cmdsocket->port = deviceMgmt->systemconfig.server.XmlPort;
        
        while(1)
        {
                PrintfGreen("XML Connection--%s:%d", cmdsocket->ip, cmdsocket->port);
                if(cmdsocket->open(cmdsocket) > 0)
                {
                        memset(cmdsocket->buffer, 0, strlen(cmdsocket->buffer));
                        deviceMgmtReport(cmdsocket->buffer);//define in Reportdata.h
                        cmdsocket->len = strlen(cmdsocket->buffer);
                        PrintfRed("send");
                        PrintfGreen(cmdsocket->buffer);
                        cmdsocket->writen(cmdsocket);

                        cmdsocket->readline(cmdsocket);
                        PrintfRed("rec:%d", cmdsocket->len);
                        if(cmdsocket->len > 0)
                        {
                                deviceMgmt->sensorstatusconfirm(deviceMgmt);
                                dataStore->reportdel(dataStore, "config");
                                
                                PrintfGreen(cmdsocket->buffer);
                                //½âÎöxml
                                cmdresolver->parse(cmdresolver, cmdsocket->buffer);
                        }
                        cmdsocket->close(cmdsocket);
                }
                sleep(10);

        }
        
        mysocketDestroy(cmdsocket);
        ResolverDestroy(cmdresolver);
        return NULL;

}

void * Communications(void)
{

       reportdata();

        return NULL;
}

void *CheckConfigThread(void)
{
        while(1)
        {
                if(deviceMgmt->checkconfig(deviceMgmt) == 1)
                {
                        deviceMgmt->getsystemconfig(deviceMgmt);
                        deviceMgmt->cleanconfigchange(deviceMgmt);
                }
                sleep(1);
        }
        return NULL;
}

void *Get3GSignalThread()
{
#if USE3G
	char port[] = "/dev/ttyUSB0";
        myuart *uart = myuartCreate();
        uart->config.port = port;
        uart->config.speed = 115200;
        uart->config.flow_ctrl = 0;
        uart->config.databits = 8;
        uart->config.stopbits = 1;
        uart->config.parity = 'N';
        uart->open(uart);
        while(1)
        {
        	strcpy(uart->buffer, "AT+CSQ\r\n");
        	uart->len = 9;
            	uart->writen(uart);
		uart->readline(uart);
		uart->readline(uart);
		int rssi;
		int ber;
		sscanf(uart->buffer, "+CSQ: %d, %d\r\nOK", &rssi, &ber);
		int Signal;
		if(rssi<99)
                Signal = rssi * 2 -113;
        	else
                Signal = rssi  -216;
                dataStore->unit.sensorID = 256;
                dataStore->unit.data = Signal;
                dataStore->unit.time = time(NULL);
                dataStore->reportadd(dataStore, "report");
                sleep(60);
        }
	myuartDestroy(uart);
#endif
}
