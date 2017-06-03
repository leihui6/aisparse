/**
*	此模块用于对数据源进行必要的整理
*	以及将每条报文存为revd_msg_s格式
*	总之，是在源文件上的操作，若脱离源文件就没有意义
*
*	提供了以下几个功能:
*		- 将数据在读取时进行必要的分类
*		- 仅将数据读取
*
*------------------------
*	2017-01-24
*	ptsph@foxmail.com
*/
#include <map>
#include <vector>
#include <fstream>

using namespace std;

#include "vdm_parse_core.h"

#ifndef SRCDATA_H
#define SRCDATA_H

const size_t MAXCOUNT = 5;

struct revd_msg_s{
	revd_msg_s() :count(0), msg(),major_msg(){}

	void set_msg_by_count(size_t _count,const string &_str){
		msg[_count] = _str;
	}

	string get_msg_by_count(size_t _count){
		return msg[_count];
	}

	size_t count;
	string msg[MAXCOUNT];
	string major_msg;
};
#endif /*SRCDATA_H*/

void atoi_s_(const char * _str, size_t _len, size_t *_dst);



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

/*	
*	找到报文中的主要报文段开始位置，找不到则返回NULL
*
*	例如：
*	const char * str = "20160322 - 07:09:12	!AIVDM,1,1,,A,B6:V`n00=28I9I4W9pQ4swTWQP06,0*71";
*	find_major_beg(str);
*	函数将返回下面箭头所示的字符所在指针
*	20160322 - 07:09:12	!AIVDM,1,1,,A,B6:...
*									  ^
*	NOTE：
*	报文主要内容就从此开始，但是是否有效我们不保证
*
*/
const char * find_major_beg(const char * _str);

/*
*	找到报文中的主要报文段结束位置，找不到则返回NULL
*
*	例如：
*	const char * str = "20160322 - 07:09:12	!AIVDM,1,1,,A,B6:V`n00=28I9I4W9pQ4swTWQP06,0*71";
*	find_major_end(str);
*	函数将返回下面箭头所示的字符所在指针
*	20160322 - 07:09:12	!AIVDM,1,1,,A,B6:V`n00=28I9I4W9pQ4swTWQP06,0*71
*									                              ^
*	NOTE：
*	若你想遍历报文的主要内容，使用find_major_beg和find_major_end函数再适合不过了，
*	假设前者返回的值为beg，后者为end(且都不为NULL)，那么遍历的语句可以这么写：
*	for(const char * i = beg;i < end;i ++){...}
*	这么做的意义是确保遍历的习惯和平时写for循环的习惯一样，即[beg,end)
*
*/
const char * find_major_end(const char * _str);

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
*	同时返回找到报文的头位置和结束位置
*	
*	NOTE：
*	详细内容请看find_major_beg和find_major_end函数
*
*/
int find_major_beg_end(const char * _str, const char ** _beg, const char ** _end);

/*
*	拼接报文主要内容，返回拼接结果，失败返回NULL
*	
*	例如：
*	对于以下两条报文：
*	20160322 - 07:09:12	!AIVDM,2,1,3,A,C6:`Mo00AB8l@e4Vv@;NGwv0@b30jbM0@2N00000000,0*56
*	20160322 - 07:09:12	!AIVDM,2,2,3,A,0`3`63S0P,0*20
*	其拼接结果为：
*	C6:`Mo00AB8l@e4Vv@;NGwv0@b30jbM0@2N000000000`3`63S0P
*	
*	NOTE：
*	拼接结果主要用于当发送多条报文时的解析
*
*/
char * cat_major_msg(revd_msg_s * _revd_msg);

/*
*	按照报文条数接受报文
*	
*	例如：
*	对于以下两条报文：
*	20160322 - 07:09:12	!AIVDM,2,1,3,A,C6:`Mo00AB8l@e4Vv@;NGwv0@b30jbM0@2N00000000,0*56
*	20160322 - 07:09:12	!AIVDM,2,2,3,A,0`3`63S0P,0*20
*	使用recv_all_msg函数后会将结果存储在$_revd_msg中
*
*
*/
int recv_all_msg(revd_msg_s * _revd_msg,FILE **_fp);

/*
*	清除revd_msg_s结构
*	
*	NOTE：
*	清除意味着将里面的数据清空，即都设置为'\0'
*	而不是释放
*/
int clear_revd_msg(revd_msg_s *_revd_msg);

/*
*	将文本数据中的报文加载到$_revd_msg_vec结构中
*	revd_msg_s结构如下：
*	struct revd_msg_s{
*		size_t count;
*		char msg_p[5][1024];
*	};
*	
*	
*	
*/
int read_srcdata(const char * _filename, vector<revd_msg_s> &_revd_msg_vec);

int classify_by_user_id(char * _filename,map<size_t,vector<revd_msg_s> > &_userid_map_msg);

int save_by_user_id(map<size_t,vector<revd_msg_s> > &_userid_map_msg);



















