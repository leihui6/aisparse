#include "vdm_opt.h"

size_t VDM::get_message_id(const revd_msg_s * _revd_msg)
{
	size_t message_id = 0;

	convert_to_decimal(_revd_msg->major_msg_p, 0, 6, &message_id);
	
	return message_id;
}

size_t VDM::get_repeat_indicator(const revd_msg_s * _revd_msg)
{
	size_t repeat_indicator = 0;

	convert_to_decimal(_revd_msg->major_msg_p, 6, 2, &repeat_indicator);

	return repeat_indicator;
}

size_t VDM::get_user_id(const revd_msg_s * _revd_msg)
{
	size_t user_id = 0;

	convert_to_decimal(_revd_msg->major_msg_p, 8, 30, &user_id);

	return user_id;
}

std_time_s VDM::get_revd_time(const revd_msg_s *_revd_msg){
	const char * first_msg_p = _revd_msg->msg_p[0];
	if (strlen(first_msg_p) < 19){
		fprintf(stderr, "error:length should >= 19(have not the standard format of time)\n");
		return std_time_s();
	}
	size_t num = 0;
	std_time_s std_time;

	atoi_s_(first_msg_p, 4, &num);
	std_time.year = num;

	atoi_s_(first_msg_p + 4, 2, &num);
	std_time.month = num;

	atoi_s_(first_msg_p + 6, 2, &num);
	std_time.day = num;

	atoi_s_(first_msg_p + 11, 2, &num);
	std_time.hour = num;

	atoi_s_(first_msg_p + 14, 2, &num);
	std_time.minute = num;

	atoi_s_(first_msg_p + 17, 2, &num);
	std_time.second = num;
	return std_time;
}

string VDM::get_channel(const revd_msg_s *_revd_msg){
	const char * first_msg_p = _revd_msg->msg_p[0];
	const char * p = find_msg_header(first_msg_p);
	if (p == NULL){
		return string();
	}
	p = find_char_by_count(p, ',', 4);
	if (p == NULL){
		return string();
	}
	if (*(p + 1) != 'A' && *(p + 1) != 'B'){
		return string();
	}
	return string((p + 1),1);
}

size_t VDM_1::get_navigational_status(const revd_msg_s *_revd_msg){
	size_t navigational_status = 0;

	convert_to_decimal(_revd_msg->major_msg_p, 38, 4, &navigational_status);
	
	return navigational_status;
}

size_t VDM_1::get_sog(const revd_msg_s *_revd_msg){
	size_t sog = 0;

	convert_to_decimal(_revd_msg->major_msg_p, 50, 10, &sog);
	
	return sog;
}

size_t VDM_1::get_cog(const revd_msg_s *_revd_msg){
	size_t cog = 0;

	convert_to_decimal(_revd_msg->major_msg_p, 116, 12, &cog);

	return cog;
}

size_t VDM_1::get_true_heading(const revd_msg_s *_revd_msg){
	size_t true_heading = 0;

	convert_to_decimal(_revd_msg->major_msg_p, 128, 9, &true_heading);

	return true_heading;
}

size_t VDM_1::get_longitude(const revd_msg_s *_revd_msg){
	size_t longitude = 0;

	convert_to_decimal(_revd_msg->major_msg_p, 61, 28, &longitude);

	return longitude;
}

size_t VDM_1::get_latitude(const revd_msg_s *_revd_msg){
	size_t latitude = 0;

	convert_to_decimal(_revd_msg->major_msg_p, 89, 27, &latitude);
	
	return latitude;
}

size_t VDM_5::get_imo_number(const revd_msg_s *_revd_msg){
	size_t imo_number = 0;

	convert_to_decimal(_revd_msg->major_msg_p, 40, 30, &imo_number);

	return imo_number;
}

string VDM_5::get_call_sign(const revd_msg_s *_revd_msg){
	char call_sign[8] = {};
	
	convert_to_strascii(_revd_msg->major_msg_p, 70, 42, call_sign, 7);
	
	return (call_sign);
}

string VDM_5::get_name(const revd_msg_s *_revd_msg){
	char name[21] = {};
	
	convert_to_strascii(_revd_msg->major_msg_p, 112, 120, name, 20);

	return (name);
}

od_s VDM_5::get_overall_dimension(const revd_msg_s *_revd_msg){
	od_s od;
	convert_to_decimal(_revd_msg->major_msg_p, 240, 9, &od.A);
	convert_to_decimal(_revd_msg->major_msg_p, 249, 9, &od.B);
	convert_to_decimal(_revd_msg->major_msg_p, 258, 6, &od.C);
	convert_to_decimal(_revd_msg->major_msg_p, 264, 6, &od.D);
	return od;
}

size_t VDM_5::get_maximum_draught(const revd_msg_s *_revd_msg){
	size_t maximum_draught = 0;
	
	convert_to_decimal(_revd_msg->major_msg_p, 294, 8, &maximum_draught);
	
	return maximum_draught;
}

string VDM_6::get_application_data(const revd_msg_s *_revd_msg){
	char application_data[231] = {};
	
	convert_to_hexdecimal(_revd_msg->major_msg_p, 88, 920, application_data, 230);

	return (application_data);
}

string VDM_8::get_application_data(const revd_msg_s *_revd_msg){
	char application_data[239] = {};

	convert_to_hexdecimal(_revd_msg->major_msg_p, 56, 952, application_data, 238);

	return (application_data);
}

string VDM_12::get_safety_text(const revd_msg_s *_revd_msg){
	char safety_text[157] = {};

	convert_to_strascii(_revd_msg->major_msg_p, 72, 936, safety_text, 156);

	return (safety_text);
}

string VDM_14::get_safety_text(const revd_msg_s *_revd_msg){
	/* NOTE：
	* 标准是968，以六比特区分
	* 但是除不尽，于是就取 698/6 = 161
	* 161 * 6 = 966 个比特
	*/
	char safety_text[162] = {};

	convert_to_strascii(_revd_msg->major_msg_p, 40, 966, safety_text, 161);
	
	return (safety_text);
}

size_t VDM_18::get_sog(const revd_msg_s *_revd_msg){
	size_t sog = 0;

	convert_to_decimal(_revd_msg->major_msg_p, 46, 10, &sog);
	
	return sog;
}

size_t VDM_18::get_cog(const revd_msg_s *_revd_msg){
	size_t cog = 0;

	convert_to_decimal(_revd_msg->major_msg_p, 112, 12, &cog);

	return cog;
}

size_t VDM_18::get_true_heading(const revd_msg_s *_revd_msg){
	size_t true_heading = 0;
	
	convert_to_decimal(_revd_msg->major_msg_p, 124, 9, &true_heading);

	return true_heading;
}

size_t VDM_18::get_longitude(const revd_msg_s *_revd_msg){
	size_t longitude = 0;

	convert_to_decimal(_revd_msg->major_msg_p, 57, 28, &longitude);
	
	return longitude;
}

size_t VDM_18::get_latitude(const revd_msg_s *_revd_msg){
	size_t latitude = 0;

	convert_to_decimal(_revd_msg->major_msg_p, 85, 27, &latitude);

	return latitude;
}