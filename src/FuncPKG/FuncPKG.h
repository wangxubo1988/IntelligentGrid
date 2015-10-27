#ifndef _FUNCTION_PACKAGE_
#define _FUNCTION_PACKAGE_

#define CRC16LEN 2

char* StrNCpy(char dest[],char src[], size_t num);

void * MyMalloc(int size, const char * name, const char * func, unsigned int line);

void  MyFree(char *ptr, const char * name, const char * func, unsigned int line);

long ReadOneByte(int fd, void *buf);

long Readn(int fd, void *buf, long count);

long ReadLine(int fd, void *buf, int size);

long Writen(int fd, const void *buf, long count);

long Sendn(int fd, const void *buf, long count);

int SyncTime();

int MacHexToString(char mac[], char *macstr);

int MacStringToHex(char *macstr, char mac[]);

int TestCrc(char trame[],int len);

int CalculCrc(char trame[],int len);

int StrMatch(char *src, char *des,int len);

#endif

