#ifndef _SOCKET_H_
#define _SOCKET_H_

#define MYSOCKET_BUFFER_SIZE 10000

typedef struct mysocket mysocket;

struct mysocket{
        int fd;
        int len;
        char ip[50];
        int port;
        char buffer[MYSOCKET_BUFFER_SIZE];

        
        int (*open)(mysocket* const me);
        int (*close)(mysocket* const me);
        int (*readline)(mysocket* const me);
        int (*readn)(mysocket* const me);
        int (*readonebyte)(mysocket* const me);
        int (*writen)(mysocket* const me);
        void (*clean)(mysocket* const me);
};

void mysocketDestroy(mysocket * const me);

mysocket * mysocketCreate(void);

#endif