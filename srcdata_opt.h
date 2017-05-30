#include <cstdio>
#include <cstring>
/*
*	此模块负责对源文件内容进行操作
*
*	@time:2017-05-30
*	@author:ptsph@foxmail.com
*
*/
#ifndef SRCDATA_H_INCLUDED
#define SRCDATA_H_INCLUDED

/*
*	将数字字符串转为数字返回，若发现非数字字符则返回0
*
*	例如：
*	const char * str = "123456";
*	char dst[6];
*	atoi_s_(str,6,dst);
*	调用函数后dst为数字123456
*	
*
*/

void atoi_s_(const char * _str, size_t _len, size_t *_dst);

/*
*	找到报文的头位置，找不到则返回NULL
*
*	例如：
*	const char * str = "20160322 - 07:09:12	!AIVDM,1,1,,A,B6:V`n00=28I9I4W9pQ4swTWQP06,0*71";
*	find_msg_header(str);
*
*	函数将返回下面箭头所示的字符所在指针
*	20160322 - 07:09:12	!AIVDM,1,1,,A,B6:V`n00=28I9I4W9pQ4swTWQP06,0*71
*						^
*
*
*/
const char * find_msg_header(const char * _str);

/*
*	获取字符$_check出现第$_count次数的位置，不满足条件则返回NULL
*
*	例如：
*	const char * str = "abc,d,efr,sdf";
*	find_char_by_count(str,',',3);
*	将返回第三个','所在位置的指针
*
*	NOTE：
*	注意不是返回下一个位置的指针，
*	因为我们无法保证下一个指针(next pointer)是有效的
*
*/
const char * find_char_by_count(const char * _str, char _check, size_t _count);

#endif