#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <limits.h>
#include <time.h>
#include <netdb.h>

#include <arpa/inet.h>
#include <ctype.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <misc.h>
#include<FuncPKG.h>
#include <mysocket.h>
#include <DataPKG.h>

static int set_sock_time(int fd, int read_sec, int write_sec)
{
        struct timeval send_timeval;
        struct timeval recv_timeval;

        if(fd <= 0) return -1;
        send_timeval.tv_sec = write_sec<0?0:write_sec;
        send_timeval.tv_usec = 0;
        recv_timeval.tv_sec = read_sec<0?0:read_sec;;
        recv_timeval.tv_usec = 0;
        if(setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &send_timeval,\
                sizeof(send_timeval)) == -1)
        {
                return -1;
        }
        if(setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &recv_timeval,\
                sizeof(recv_timeval)) == -1)
        {
                return -1;
        }

        return 0;
}

static int SockConnect(char *ipaddr, int portnumber)
{

         int sockfd = 0;


        struct sockaddr_in   server_addr;

        if((sockfd=socket(AF_INET,SOCK_STREAM,0)) == -1)/*建立SOCKET连接*/
        {
                PrintfRed("Socket   Error:%s\a\n", strerror(errno));

                return -1;
        }

        if(set_sock_time(sockfd, 30, 30) < 0)
        {
                close(sockfd);
                return -1;
        }




    /*   客户程序填充服务端的资料   */
        bzero(&server_addr, sizeof(server_addr));

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(portnumber);
        inet_pton(AF_INET, ipaddr, &server_addr.sin_addr);

    /*   客户程序发起连接请求   */

        if(connect(sockfd, (struct sockaddr*)(&server_addr), sizeof(struct sockaddr)) == -1)
        {
                PrintfRed("Connect   Error:%s\a\n", strerror(errno));
                close(sockfd);
                return -1;
        }

        return sockfd;
}

static int mysocket_open(mysocket* const me)
{
        me->fd = SockConnect(me->ip, me->port);
        return me->fd;
}

static int mysocket_close(mysocket* const me)
{
        return close(me->fd);
}

static int mysocket_readline(mysocket* const me)
{

        struct timeval timeout;
        fd_set fs_read;
        me->len = 0;
        memset(me->buffer, 0, strlen(me->buffer));
        do{
                timeout.tv_sec = 3;
                timeout.tv_usec = 0;
                FD_ZERO(&fs_read);

                FD_SET(me->fd, &fs_read);
                if(select(me->fd + 1, &fs_read, NULL, NULL, &timeout) < 0)
                {
                        return -1;
                }
        
                
                me->len += ReadLine(me->fd, me->buffer + me->len, MYSOCKET_BUFFER_SIZE);

               usleep(100);
        }while(me->len == 0);

        return me->len;
        
}

static int mysocket_readn(mysocket* const me)
{
        
        memset(me->buffer, 0, strlen(me->buffer));
        if(me->len > MYSOCKET_BUFFER_SIZE)
        {
                return -3;
        }
        me->len = Readn(me->fd, me->buffer, me->len);

        return me->len;
}

static int mysocket_readonebyte(mysocket* const me)
{
        return ReadOneByte(me->fd, me->buffer);
}

static int mysocket_writen(mysocket* const me)
{
        me->len = Sendn(me->fd, me->buffer, me->len);
        return 0;
}

static void mysocketCleanup(mysocket * const me)
{
        me->fd = 0;
        me->len = 0;
        memset(me->ip, 0, strlen(me->ip));
        me->port = 0;
        memset(&me->buffer, 0, sizeof(me->buffer));
}

static void mysocketInit(mysocket * const  me, int (*open)(mysocket * me), \
         int (*close)(mysocket * me),  int (*readline)(mysocket * me), \
         int (*readn)(mysocket * me),  int (*readonebyte)(mysocket * me), \
         int (*writen)(mysocket * me),  void (*clean)(mysocket * me))
{
        me->fd = 0;
        me->len = 0;
        memset(me->ip, 0, strlen(me->ip));
        me->port = 0;
        memset(&me->buffer, 0, sizeof(me->buffer));
        me->open = open;
        me->close = close;
        me->readline = readline;
        me->readn = readn;
        me->readonebyte = readonebyte;
        me->writen = writen;
        me->clean = clean;
}

mysocket * mysocketCreate(void)
{
        mysocket * me = (mysocket *)Malloc(sizeof(mysocket));
        
        if(me != NULL)
        {
                mysocketInit(me, mysocket_open, mysocket_close, mysocket_readline,\
                        mysocket_readn, mysocket_readonebyte, mysocket_writen,\
                        mysocketCleanup);
        }

        return me;
}

void mysocketDestroy(mysocket * const me)
{
        if(me != NULL)
        {
                mysocketCleanup(me);  
        }
        Free(me);
}

