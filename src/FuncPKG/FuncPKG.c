#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <misc.h>
#include <stdio.h>
#include <time.h>
#include<netinet/in.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <sys/time.h>

char* StrNCpy(char dest[],char src[], size_t num)
{
        size_t i;
        for(i=0;i<num;i++)
        {
                dest[i] = src[i];
        }
        return dest;
}



void * MyMalloc(int size, const char * name, const char * func, unsigned int line)
{
        static int i = 0;
        char *ret;
        FILE * fp = NULL;
        // long enough
        char str[11];

        // to change int to str

        sprintf(str,"%d c=%d",line,++i);
        ret = malloc(size);
        // log your msgs

        fp = fopen("Logm.txt", "a");
        fputs("\n", fp);

        fputs(" func: ", fp);
        fputs(func, fp);
        fputs(" line: ", fp);
        fputs(str, fp);
        fclose(fp);

        return ret;
};


void  MyFree(char *ptr, const char * name, const char * func, unsigned int line)
{
        static int j = 0;
        FILE * fp = NULL;
        // long enough
        char str[11];

        // to change int to str

        if(ptr == NULL)
        {
                return;
        }
        sprintf(str,"%d c=%d",line,++j);
        free(ptr);
        // log your msgs

        fp = fopen("Logf.txt", "a");
        fputs("\n", fp);

        fputs(" func: ", fp);
        fputs(func, fp);
        fputs(" line: ", fp);
        fputs(str, fp);
        fclose(fp);

        return;
};

long ReadOneByte(int fd, void *buf)
{
        char *strtmp;
        ssize_t reval;

        if(fd < 0)
        {
                return -1;
        }
        strtmp = (char *)buf;
        reval = read(fd, strtmp, 1);

        return reval;
}


long Readn(int fd, void *buf, long count)
{
        char *strtmp;
        long reval, realcount = 0;

        if(fd < 0)
        {
                return -1;
        }
        strtmp = (char *)buf;
        while (count > 0)
        {
                reval = read(fd, strtmp, count);
                if (reval < 0)
                {
                        if (errno == EINTR)
                        {
                                continue;
                        }
                        else
                        {
                                return -1;
                        }
                }
                else if (reval > 0)
                {
                        count -= reval;
                        strtmp += reval;
                        realcount += reval;
                        continue;
                }
                else
                {
                        break;
                }
        }

        return realcount;
}

long ReadLine(int fd, void *buf, int size)
{
        char *strtmp;
        ssize_t reval, realcount = 0;

        if(fd < 0)
        {
                return -1;
        }
        strtmp = (char *)buf;

        while (size > 1)
        {
                reval = read(fd, strtmp, 1);
                if (reval < 0)
                {
                        if (errno == EINTR)
                        {
                                continue;
                        }
                        else
                        {
                                return -1;
                        }
                }
                else if (reval == 0)
                {
                        break;
                }
                else
                {
                        realcount++;
                        size--;
                        if (*strtmp++ == '\n')
                        {
                                break;
                        }
                }
        }

        *(strtmp - 1) = '\0';
        return realcount;
}

long Writen(int fd, const void *buf, long count)
{
        char *strtmp;
        ssize_t reval, realcount = count;

        if(fd < 0)
        {
                return -1;
        }
        strtmp = (char *)buf;
        while (count > 0)
        {
                reval = write(fd, strtmp, count);
                if (reval < 0)
                {
                        if (errno == EINTR)
                        {
                                continue;
                        }
                        else
                        {
                                return -1;
                        }
                }
                count -= reval;
                strtmp += reval;
        }

        return realcount;
}

long Sendn(int fd, const void *buf, long count)
{
        char *strtmp;
        ssize_t reval, realcount = count;

        if(fd < 0)
        {
                return -1;
        }
        if(buf == NULL)
        {
                return 0;
        }

        strtmp = (char *)buf;
        while (count > 0)
        {


                reval = send(fd,strtmp,count>=65532?65531:count, MSG_NOSIGNAL);
                if (reval < 0)
                {
                        if (errno == EINTR)
                        {


                                return -2;
                        }
                        else
                        {

                                return -1;
                        }
                }
                count -= reval;
                strtmp += reval;
        }

        return realcount;
}

int rtc_xopen(const char *default_rtc, int flags)
{
 int rtc;
 if (!default_rtc) {
  default_rtc = "/dev/rtc";
  rtc = open(default_rtc, flags);
  if (rtc >= 0)
   return rtc;
  default_rtc = "/dev/rtc0";
  rtc = open(default_rtc, flags);
  if (rtc >= 0)
   return rtc;
  default_rtc = "/dev/misc/rtc";
 }
 return open(default_rtc, flags);
}


static void from_sys_clock(const char *pp_rtcname, int utc)
{

        struct timeval tv;
        struct tm tm_time;
        struct tm tm_time_now;
        int rtc;
        rtc = rtc_xopen(pp_rtcname, O_WRONLY);
        gettimeofday(&tv, NULL);

        if (sizeof(time_t) == sizeof(tv.tv_sec)) {
                if (utc)
                        gmtime_r((time_t*)&tv.tv_sec, &tm_time);
                else
                        localtime_r((time_t*)&tv.tv_sec, &tm_time);
        }
        else {

                time_t t = tv.tv_sec;
                if (utc)
                        gmtime_r(&t, &tm_time);
                else
                        localtime_r(&t, &tm_time);
        }
        
        tm_time.tm_isdst = 0;

        ioctl(rtc, RTC_RD_TIME, &tm_time_now);

        if(tm_time_now.tm_min != tm_time.tm_min   || \
                tm_time_now.tm_hour != tm_time.tm_hour   || \
                tm_time_now.tm_mday != tm_time.tm_mday   || \
                tm_time_now.tm_mon != tm_time.tm_mon || \
                tm_time_now.tm_year != tm_time.tm_year)
        {

                ioctl(rtc, RTC_SET_TIME, &tm_time);
                PrintfGreen("nowtime:%d", tm_time_now.tm_sec);
                PrintfGreen("time:%d", tm_time.tm_sec);
                PrintfGreen("sync time");
        }
        //if (ENABLE_FEATURE_CLEAN_UP)
        close(rtc);
}

int SyncTime(time_t time)
{
        stime(&time);
        from_sys_clock("/dev/rtc", 1);

        return 0;
}


int MacHexToString(char mac[], char *macstr)
{

        sprintf(macstr, "%02X%02X%02X%02X%02X%02X%02X%02X",
                mac[0], mac[1], mac[2], mac[3], mac[4], mac[5], mac[6], mac[7]);

       return 0;
}

int MacStringToHex(char *macstr,char mac[])
{
        unsigned int temmac[8];
        PrintfGreen("macstring:%s",macstr);
        sscanf(macstr, "%02X%02X%02X%02X%02X%02X%02X%02X",
                &temmac[0], &temmac[1], &temmac[2],
                &temmac[3], &temmac[4], &temmac[5],
                &temmac[6], &temmac[7]);
       int i;
       for(i=0;i<8;i++)
                mac[i] = (unsigned char)temmac[i];

       return 0;
}

/**********************************************************************
 *函数名称	:TestCrc
 *函数功能	:对modbus数据包进行crc校验
 *函数输入参数	:trame	数据包指针，len 数据包除了crc部分的长度
 *函数返回值	:0-成功	1-失败
 **********************************************************************/
int TestCrc(char trame[],int len)
{
        unsigned int crc;
        unsigned int i;
        unsigned int j;
        unsigned int carry_flag;
        unsigned int a;
        crc = 0xffff;
        for(i = 0; i < len; i ++)
        {
                crc = crc ^ trame[i];
                for(j = 0; j < 8; j ++)
                {
                        a = crc;
                        carry_flag = a & 0x0001;
                        crc=crc >> 1;
                        if(carry_flag == 1)
                        {
                                crc = crc ^ 0xa001;
                        }
                }
        }
        if((trame[len + 1] != (crc >> 8)) || (trame[len] != (crc & 255)))
        {

                PrintfRed("crc check failure!\n");

                return 1;
        }

        return 0;        
} /*End test_crc*/

/**********************************************************************
 *函数名称	:CalculCrc
 *函数功能	:在数据帧后面插入crc并返回crc
 *函数输入参数	:trame	原始数据帧指针，len原始数据帧长度
 *函数返回值	:数据帧的crc
 **********************************************************************/
int CalculCrc(char trame[],int len)
{
        unsigned int crc;
        unsigned int i;
        unsigned int j;
        unsigned int carry_flag;
        unsigned int a;
        crc=0xffff;
        for(i = 0; i < len; i ++)
        {
                crc = crc^trame[i];
                for(j = 0; j < 8; j ++)
                {
                        a = crc;
                        carry_flag = a & 0x0001;
                        crc = crc >> 1;
                        if(carry_flag == 1)
                        crc = crc ^ 0xa001;
                }
        }
        trame[len + 1] = crc >> 8;
        trame[len] = crc & 255;

        return crc;
} /*End calcul_crc*/


int StrMatch(char *src, char *des,int len)
{
        int i;
        int j;
        for(i = 0; i < len; i ++)
        {
               for(j = 0; j < strlen(des); j++)
               {
                        if(*(src+i+j) != *(des+j))
                        {
                                break;
                        }
               }
               if(strlen(des) == j)
               {
                        return i+j;
               }
        }
        return 0;
}

