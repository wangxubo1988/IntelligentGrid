/*
 * ====================================================================
 *
 *       Filename:  uart.c
 *
 *    Description:  Uart Interface Function
 *
 *        Version:  1.0
 *        Created:  2013å¹´12æœˆ24æ—¥ 16æ—¶57åˆ†16ç§’
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), 583050603@qq.com
 *        Company:  Zhejiang Hangzhou.
 *
 * ====================================================================
 */

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<termios.h>
#include<errno.h>
#include<string.h>
#include<FuncPKG.h>
#include"uart.h"
#include <misc.h>

static int uart_set(int fd, struct uart_config config);

static int uart_open(myuart * const me)
{
        int err = 0;

        me->fd = open(me->config.port, O_RDWR | O_NOCTTY | O_NDELAY);
        if(me->fd < 0)
        {
                perror("Can`t Open Serial Port");
                return -1;
        }

        if((err = fcntl(me->fd, F_SETFL, 0)) < 0)
        {
                perror("fcntl failed!");
                return -1;
        }
        else
        {
                //printf("fcntl = %d\n", err);
        }
        if(0 == isatty(STDIN_FILENO))
        {
                perror("standard input is not a terminal device");
                return -1;
        }
        else
        {
                //printf("isatty success!\n");
        }
        printf("uart->fd = %d\n", me->fd);
        
        uart_set(me->fd, me->config);
        
        return 0;
} /*End uart_open*/

static int uart_close(myuart * const me)
{

        return close(me->fd);

} /*End uart_close*/

static int uart_set(int fd, struct uart_config config)
{
        int i;
        struct termios options;
        int  const speed_arr[] = {
                                B115200, B19200, B9600, B4800, B2400, B1200, B300 };
        long const name_arr[] = {
                                115200,  19200,  9600,  4800,  2400,  1200,  300 };
		//ÉèÖÃ´®¿Ú²¨ÌØÂÊ
        if(tcgetattr(fd,&options) != 0)
        {
                perror("setup serial error!");
                return -1;
        }

        for(i = 0;i < sizeof(speed_arr) / sizeof(int); i++)
        {
                if(config.speed == name_arr[i])
                {
                        cfsetispeed(&options, speed_arr[i]);
                        cfsetospeed(&options, speed_arr[i]);
                        break;
                }
        }

        options.c_cflag |= CLOCAL;

        options.c_cflag |= CREAD;

        switch(config.flow_ctrl)
        {
                case 0 :
                        options.c_cflag &= ~CRTSCTS;
                        break;

                case 1 :
                        options.c_cflag |= ~CRTSCTS;
                        break;

                case 2 :
                        options.c_cflag |= IXON | IXOFF | IXANY;
                        break;

                default:
                        perror("Unsupported flow_ctrl!");
                        return -1;
        }

        options.c_cflag &= ~CSIZE;
        switch(config.databits)
        {
                case 5 :
                        options.c_cflag |= CS5;
                        break;
                case 6 :
                        options.c_cflag |= CS6;
                        break;
                case 7 :
                        options.c_cflag |= CS7;
                        break;
                case 8 :
                        options.c_cflag |= CS8;
                        break;
                default :
                        perror("Unsupported data size!");
                        return -1;
        }

        switch(config.parity)
        {
                case 'n' :
                case 'N' :
                        options.c_cflag &= ~PARENB;
                        options.c_iflag &= ~INPCK;
                        break;
                case 'o' :
                case 'O' :
                        options.c_cflag |= (PARODD | PARENB);
                        options.c_iflag |= INPCK;
                        break;
                case 'e' :
                case 'E' :
                        options.c_cflag |= PARENB;
                        options.c_cflag &= ~PARODD;
                        options.c_iflag |= INPCK;
                        break;
                case 's' :
                case 'S' :
                        options.c_cflag &= ~PARENB;
                        options.c_cflag &= ~CSTOPB;
                        break;
                default :
                        perror("Unsupported parity!");
                        return -1;

        }

        switch(config.stopbits)
        {
                case 1 :
                        options.c_cflag &= ~CSTOPB;
                        break;
                case 2 :
                        options.c_cflag |= CSTOPB;
                        break;
                default:
                        perror("Unsupported stop bits!");
                        return -1;
        }

        options.c_oflag &= ~OPOST;
        options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

        options.c_cc[VTIME] = 0;
        options.c_cc[VMIN] =  0;
        options.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);

        tcflush(fd, TCIFLUSH);

        if(tcsetattr(fd, TCSANOW, &options) != 0)
        {
                perror("uart set error!");
                return -1;
        }

        return 0;
} /*End uart_set*/

/*
static int uart_read(myuart * const me)
{
        struct timeval timeout;
        fd_set fs_read;
        int err = 0;
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        me->len = 0;
        FD_ZERO(&fs_read);

        FD_SET(me->fd, &fs_read);

        err = select(me->fd + 1, &fs_read, NULL, NULL, &timeout);
        
        if(err > 0)
        {
                me->len = Readn(me->fd, me->buffer, me->len);
        }
        
        return me->len;

} 
*/
static int uart_read(myuart * const me)
{
        struct timeval timeout;
        fd_set fs_read;
        int len = 0;
        int err = 0;
        int len_data = 0;
        timeout.tv_sec = 0;
        timeout.tv_usec = 1000;

        FD_ZERO(&fs_read);

        FD_SET(me->fd, &fs_read);

        err = select(me->fd + 1, &fs_read, NULL, NULL, &timeout);
        do{
                len_data += len;
                len = 0;
                if(err > 0)
                {

                        len = read(me->fd, me->buffer + len_data, me->len-len_data);

                }
                usleep(1000);
        }while(len > 0);
        me->len = len_data;
        return me->len;

} 

static int uart_readLine(myuart * const me)
{
        struct timeval timeout;
        fd_set fs_read;
        int err = 0;

        timeout.tv_sec = 10;
        timeout.tv_usec = 0;

        FD_ZERO(&fs_read);

        FD_SET(me->fd, &fs_read);

        err = select(me->fd + 1, &fs_read, NULL, NULL, &timeout);
        if(err > 0)
        {

                me->len = ReadLine(me->fd, me->buffer, UART_BUFFER_SIZE);

        }


        return me->len;

} /*End uart_read*/

static int uart_write(myuart * const me)
{
        int i;
        int len;
        //PrintfGreen("uart send:");
        //for(i=0;i<me->len;i++)
      //  {
       //      printf("%02x ",*(me->buffer+i));
      //  }
       // printf("\n");
        len = write(me->fd, me->buffer, me->len);

        if(len != me->len)
        {

                perror("send data error!");

                tcflush(me->fd, TCOFLUSH);

                return -1;

        }
        return 0;
} /*End uart_write*/

static void myuartCleanup(myuart * const me)
{
        me->fd = 0;
        me->len = 0;

        memset(&me->config, 0, sizeof(me->config));
        
        memset(&me->buffer, 0, sizeof(me->buffer));
}

static void myuartInit(myuart * const  me, int (*open)(myuart* const me), \
         int (*close)(myuart* const me),  int (*readline)(myuart* const me), \
         int (*readn)(myuart* const me), int (*writen)(myuart* const me),\
         void (*clean)(myuart* const me))
{
        me->fd = 0;
        me->len = 0;
        memset(&me->buffer, 0, sizeof(me->buffer));
        me->open = open;
        me->close = close;
        me->readline = readline;
        me->readn = readn;
        me->writen = writen;
        me->clean = clean;
}

myuart * myuartCreate(void)
{

        myuart * me = (myuart *)Malloc(sizeof(myuart));
        
        if(me != NULL)
        {
                myuartInit(me, uart_open, uart_close, uart_readLine, uart_read, uart_write,\
                        myuartCleanup);
        }

        return me;
}

void myuartDestroy(myuart * const me)
{
        if(me != NULL)
        {
                myuartCleanup(me);  
        }
        Free(me);
}