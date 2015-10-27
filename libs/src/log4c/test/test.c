/*
 * =====================================================================================
 *
 *       Filename:  test.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年03月07日 20时00分27秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jiang JiaJi (@.@), 583050603@qq.com
 *        Company:  Zhejiang Hangzhou.
 *
 * =====================================================================================
 */
#include <stdio.h>
#include "log.h"
int main(void)
{
	log_open("Tarminal_log");
	LOG_TRACE("trace");
	LOG_ERROR("error");
	LOG_WARN("warn");
	LOG_NOTICE("notice");
	LOG_DEBUG("hello log4c!");
	log_close();
	return 0;
}
