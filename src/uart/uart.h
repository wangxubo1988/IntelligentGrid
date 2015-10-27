/*
 * ====================================================================
 *
 *       Filename:  uart.h
 *
 *    Description:  uart api
 *
 *        Version:  1.0
 *        Created:  2013年12月24日 21时14分30秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), 583050603@qq.com
 *        Company:  Zhejiang Hangzhou.
 *
 * ====================================================================
 */
#ifndef _UART_H_
#define _UART_H_

#define UART_BUFFER_SIZE 2000

struct uart_config
{
        char *port;
        long speed;
        int flow_ctrl;
        int databits;
        int stopbits;
        int parity;
};

typedef struct myuart myuart;

struct myuart{
        int fd;
        struct uart_config config;
        char buffer[UART_BUFFER_SIZE];
        int len;

        int (*open)(myuart* const me);
        int (*close)(myuart* const me);
        int (*readn)(myuart* const me);
        int (*readline)(myuart* const me);
        int (*writen)(myuart* const me);
        void (*clean)(myuart* const me);
};

myuart * myuartCreate(void);

void myuartDestroy(myuart * const me);

#endif
