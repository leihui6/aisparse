/*
*	此模块用于vdm报文的解析
*	提供了以下三个功能:
*	1) 指定区间报文到十进制数字的转换.
*	2) 指定区间报文到内容字符串的转换.
*	3) 指定区间报文到十六进制数的转换.
*
*	@time:2017-05-30
*	@author:ptsph@foxmail.com
*
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

#ifndef VDM_PARSE_CORE_H_INCLUDED
#define VDM_PARSE_CORE_H_INCLUDED

unsigned char convert_to_sixascii(char _p);

unsigned char convert_to_sixchar(char _p);

int convert_to_signed_number(size_t _num, size_t _total_bits);

int convert_to_decimal_special(const char * _str,size_t _beg,size_t _end,size_t _r_need,size_t _l_need,size_t * _result);

int convert_to_decimal(const char * _str,size_t _before_count,size_t _count,size_t *_result);

int convert_to_hexdecimal(const char *_str,size_t _before_count,size_t _count,char * _dst,size_t _len);

int convert_to_strascii(const char * _str, size_t _before_count, size_t _count, char * _dst, size_t _len);

#endif