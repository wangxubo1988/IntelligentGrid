/*
 * ====================================================================
 *
 *       Filename:  log.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2014年03月07日 20时24分58秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), 583050603@qq.com
 *        Company:  Zhejiang Hangzhou.
 *
 * ====================================================================
 */

#include "log4c.h"
#include <assert.h>
#include "log.h"
static log4c_category_t *log_category = NULL;

int log_open(const char *category)
{
        if (log4c_init() == 1)
        {
                return -1;
        }
        log_category = log4c_category_get(category);

        return 0;
}

void log_message(int priority , const char *fmt , ...)
{

        va_list ap;

        assert(log_category != NULL);

        va_start(ap, fmt);
        log4c_category_vlog(log_category , priority , fmt , ap);
        va_end(ap);

        return;
}

int log_close()
{
        return (log4c_fini());
}
