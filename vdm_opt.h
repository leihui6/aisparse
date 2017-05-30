#include "vdm_parse_core.h"
#include "srcdata_opt.h"
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

struct revd_msg_s{
	size_t count;
	char msg_p[5][1024];
	char * major_msg_p;
};

struct std_time_s{
	std_time_s() :year(0), month(0), day(0), hour(0), minute(0), second(0){}
	std_time_s(const std_time_s&_std_time)
	{
		year = _std_time.year;
		month = _std_time.month;
		day = _std_time.day;
		hour = _std_time.hour;
		minute = _std_time.minute;
		second = _std_time.second;
	}
	std_time_s & operator=(const std_time_s &_std_time){
		if (this == &_std_time){
			return *this;
		}
		else{
			year = _std_time.year;
			month = _std_time.month;
			day = _std_time.day;
			hour = _std_time.hour;
			minute = _std_time.minute;
			second = _std_time.second;
			return *this;
		}
	}
	size_t year;
	size_t month;
	size_t day;
	size_t hour;
	size_t minute;
	size_t second;
};

struct overall_dimension_s{
	overall_dimension_s() :A(0), B(0), C(0), D(0){}
	overall_dimension_s(const overall_dimension_s&_od)
	{
		A = _od.A;
		B = _od.B;
		C = _od.C;
		D = _od.D;
	}
	overall_dimension_s & operator=(const overall_dimension_s &_od){
		if (this == &_od){
			return *this;
		}
		else{
			A = _od.A;
			B = _od.B;
			C = _od.C;
			D = _od.D;
			return *this;
		}
	}
	size_t A;
	size_t B;
	size_t C;
	size_t D;
};

typedef overall_dimension_s od_s;

// 使用VDM2或VDM3都是在使用VDM_1
#define VDM_2 VDM_1
#define VDM_3 VDM_1

// 获取公共数据
namespace VDM{
	size_t get_message_id(const revd_msg_s * _revd_msg);

	size_t get_repeat_indicator(const revd_msg_s * _revd_msg);

	size_t get_user_id(const revd_msg_s * _revd_msg);

	std_time_s get_revd_time(const revd_msg_s *_revd_msg);

	char get_channel(const revd_msg_s *_revd_msg);
}

namespace VDM_1{
	size_t get_navigational_status(const revd_msg_s *_revd_msg);

	size_t get_sog(const revd_msg_s *_revd_msg);

	size_t get_cog(const revd_msg_s *_revd_msg);

	size_t get_true_heading(const revd_msg_s *_revd_msg);

	size_t get_longitude(const revd_msg_s *_revd_msg);

	size_t get_latitude(const revd_msg_s *_revd_msg);
}

namespace VDM_2{

}

namespace VDM_3{

}

namespace VDM_5{

	size_t get_imo_number(const revd_msg_s *_revd_msg);

	string get_call_sign(const revd_msg_s *_revd_msg);

	string get_name(const revd_msg_s *_revd_msg);

	od_s get_overall_dimension(const revd_msg_s *_revd_msg);

	size_t get_maximum_draught(const revd_msg_s *_revd_msg);
}

namespace VDM_6{
	string get_application_data(const revd_msg_s *_revd_msg);
}

namespace VDM_7{

}

namespace VDM_8{
	string get_application_data(const revd_msg_s *_revd_msg);
}

namespace VDM_12{
	string get_safety_text(const revd_msg_s *_revd_msg);
}

namespace VDM_13{

}

namespace VDM_14{
	string get_safety_text(const revd_msg_s *_revd_msg);
}

namespace VDM_18{
	size_t get_sog(const revd_msg_s *_revd_msg);

	size_t get_cog(const revd_msg_s *_revd_msg);

	size_t get_true_heading(const revd_msg_s *_revd_msg);

	size_t get_longitude(const revd_msg_s *_revd_msg);

	size_t get_latitude(const revd_msg_s *_revd_msg);

}

namespace VDM_19{

}

namespace VDM_24{

}

#endif // VDM_OPT_H_INCLUDED
