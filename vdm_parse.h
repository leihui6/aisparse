/*
	此模块用于vdm报文的解析
	提供了以下三个功能:
	1) 指定区间报文到十进制数字的转换.
	2) 指定区间报文到内容字符串的转换.
	3) 指定区间报文到十六进制数的转换.
	
	
------------------------
	2017-01-24
	ptsph@foxmail.com
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>

#ifdef __GNUC__
#define _snprintf snprintf
#endif

unsigned char convert_to_sixascii(char _p);

unsigned char convert_to_sixchar(char _p);

int convert_to_decimal_special(char * _str,size_t _beg,size_t _end,size_t _r_need,size_t _l_need,size_t * _result);

int convert_to_decimal(char * _str,size_t _before_count,size_t _count,size_t *_result);

int convert_to_hexdecimal(char *_str,size_t _before_count,size_t _count,char * _dst,size_t _len);

int convert_to_strascii(char * _str,size_t _before_count,size_t _count,char * _dst,size_t _len);
