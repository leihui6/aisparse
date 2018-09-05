/*
*	此模块负责获取vdm报文中的内容
*	NOTE:
*		输入：revd_msg_s
*
*	@time:2017-05-30
*	@author:ptsph@foxmail.com
*
*/
#ifndef VDM_OPT_H_INCLUDED
#define VDM_OPT_H_INCLUDED

#include "vdm_parse_core.h"


void atoi_s_(const char * _str, size_t _len, size_t *_dst);

const char * find_msg_header(const char * _str);

const char * find_char_by_count(const char * _str, char _check, size_t _count);

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

struct std_time_s{
	std_time_s() :year(0), month(0), day(0), hour(0), minute(0), second(0){}
	size_t year;
	size_t month;
	size_t day;
	size_t hour;
	size_t minute;
	size_t second;
};

struct overall_dimension_s{
	overall_dimension_s() :A(0), B(0), C(0), D(0){}
	size_t A;
	size_t B;
	size_t C;
	size_t D;
};

typedef overall_dimension_s od_s;

#define VDM_2 VDM_1
#define VDM_3 VDM_1

// VDM
struct VDM{
	size_t get_message_id(const revd_msg_s * _revd_msg);

	size_t get_repeat_indicator(const revd_msg_s * _revd_msg);

	size_t get_user_id(const revd_msg_s * _revd_msg);

	std_time_s get_revd_time(const revd_msg_s *_revd_msg);

	string get_channel(const revd_msg_s *_revd_msg);
};

struct VDM_1{
	size_t get_navigational_status(const revd_msg_s *_revd_msg);

	size_t get_sog(const revd_msg_s *_revd_msg);

	size_t get_cog(const revd_msg_s *_revd_msg);

	size_t get_true_heading(const revd_msg_s *_revd_msg);

	int get_longitude(const revd_msg_s *_revd_msg);

	int get_latitude(const revd_msg_s *_revd_msg);
};

struct VDM_5{
	size_t get_imo_number(const revd_msg_s *_revd_msg);

	string get_call_sign(const revd_msg_s *_revd_msg);

	string get_name(const revd_msg_s *_revd_msg);

	od_s get_overall_dimension(const revd_msg_s *_revd_msg);

	size_t get_maximum_draught(const revd_msg_s *_revd_msg);
};

struct VDM_6{
	string get_application_data(const revd_msg_s *_revd_msg);
};

struct VDM_8{
	string get_application_data(const revd_msg_s *_revd_msg);
};

struct VDM_12{
	string get_safety_text(const revd_msg_s *_revd_msg);
};

struct VDM_14{
	string get_safety_text(const revd_msg_s *_revd_msg);
};

struct VDM_18{
	size_t get_sog(const revd_msg_s *_revd_msg);

	size_t get_cog(const revd_msg_s *_revd_msg);

	size_t get_true_heading(const revd_msg_s *_revd_msg);

	int get_longitude(const revd_msg_s *_revd_msg);

	int get_latitude(const revd_msg_s *_revd_msg);
};

#endif // VDM_OPT_H_INCLUDED
