/*
	此模块用于对报文开头时间的解析.
	提供了以下几个功能:
	1) 计算相隔时间的秒数一计算消息发送频率.
	2) 为违规判断提供了底层数据结构支持.
	
------------------------
	2017-01-24
	ptsph@foxmail.com
*/
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>

#ifndef TIME_PARSE_H
#define TIME_PARSE_H

struct std_time_s{
	size_t year;
	size_t month;
	size_t day;
	size_t hour;
	size_t minute;
	size_t second;
};

struct revd_freq_s{
	bool set_init_time;
	std_time_s init_time;
	std::vector<size_t>freq_count;
};

#endif /*TIME_PARSE_H*/

int atoi_s_(char * _str,size_t _len,size_t *_dst);

int convert_to_stdtime(char * _str,std_time_s * _std_time);

int days_from_ad1(size_t _y,size_t _m,size_t _d);

size_t seconds_between_stdtime(std_time_s * _std_time1,std_time_s * _std_time2);

void clear_revd_freq(revd_freq_s * _revd_freq);
