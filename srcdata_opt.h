/*
	此模块用于对数据源进行必要的整理.
	所以所分析的对象都是源数据类型的.
	
	提供了以下几个功能:
	1) 将原始数据报文按照user_id(MMSI)分类(只有vdm的才会进行分类).
	2) 将报文(vdm报文)以user_id为文件名进行保存.
	
------------------------
	2017-01-24
	ptsph@foxmail.com
*/
#include <map>
#include <vector>
using namespace std;

#include "vdm_parse.h"

#ifndef SRCDATA_H
#define SRCDATA_H

struct revd_msg_s{
	size_t count;
	char msg_p[5][1024];
};

#endif /*SRCDATA_H*/

char * find_char_by_count(char * _str,char _check,size_t _count);

char * find_major_beg(char * _str);

char * find_major_end(char * _str);

char * find_msg_header(char * _str);

char * find_msg_channel(char * _str);

int find_major_beg_end(char * _str,char ** _beg,char ** _end);

int cat_major_msg_special(revd_msg_s * _revd_msg,char * _major_msg,size_t _len);

char * cat_major_msg(revd_msg_s * _revd_msg,size_t _len);

int recv_all_msg(revd_msg_s * _revd_msg,FILE **_fp);

int clear_revd_msg(revd_msg_s *_revd_msg);

int classify_by_user_id(char * _filename,map<size_t,vector<revd_msg_s> > &_userid_map_msg);

int save_by_user_id(map<size_t,vector<revd_msg_s> > &_userid_map_msg);

