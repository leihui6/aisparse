/*
* 提供使用案例
*
* @time:2018-09-05
* @author:ptsph@foxmail.com
*/

#include "vdm_opt.h"
#include "vdm_parse_core.h"

//#define DEBUG_VDM_1
#define DEBUG_VDM_5

void print_common(std_time_s,string,size_t,size_t,size_t);

int main() {
	VDM vdm;
	std_time_s std_time;
	string channel;
	size_t user_id;
	size_t message_id;
	size_t repeat_indicator;
	revd_msg_s * revd_msg = new revd_msg_s;
#ifdef DEBUG_VDM_1
	VDM_1 vdm_1;
	revd_msg->msg[0] = "20160812 - 01:40:20	\g:3-4-01863,n:08017,c:0000000162*50\!ARVDM,1,1,,A,169UMe00008LH=h=v0:P>A8T0D2L,0*1F";
	revd_msg->count = 1;
	revd_msg->major_msg = "169UMe00008LH=h=v0:P>A8T0D2L";
	
	std_time = vdm.get_revd_time(revd_msg);
	message_id = vdm.get_message_id(revd_msg);
	channel = vdm.get_channel(revd_msg);
	user_id = vdm.get_user_id(revd_msg);
	repeat_indicator = vdm.get_repeat_indicator(revd_msg);

	print_common(std_time, channel, user_id, message_id, repeat_indicator);

	size_t navigational_status;
	size_t sog;
	size_t cog;
	size_t true_heading;
	int longitude;
	int latitude;

	navigational_status = vdm_1.get_navigational_status(revd_msg);
	sog = vdm_1.get_sog(revd_msg);
	cog = vdm_1.get_cog(revd_msg);
	true_heading = vdm_1.get_true_heading(revd_msg);
	longitude = vdm_1.get_longitude(revd_msg);
	latitude = vdm_1.get_latitude(revd_msg);

	printf("\nnavigational_status:%ld\
			\nsog:%ld\
			\ncog:%ld\
			\ntrue_heading:%ld\
			\nlongitude:%d\
			\nlatitude:%d", navigational_status, sog,cog, true_heading, longitude, latitude);

#endif // DEBUG_VDM_1

#ifdef DEBUG_VDM_5
	VDM_5 vdm_5;
	
	revd_msg->msg[0] = "20160812 - 02:16:51	\g:3-5-08052,n:01342,c:0000002341*59\!ARVDM,2,1,2,A,56:R<4P1h`bT9HTsR204r0L4pN0aDr3V2222220Q80D,0*29";
	revd_msg->msg[1] = "20160812 - 02:16:51	\g:4-5-08052,n:01343,c:0000002341*5F\!ARVDM,2,2,2,A,496:dN9V2@H3AC`8888888888880,2*12";
	revd_msg->count = 2;
	revd_msg->major_msg = "56:R<4P1h`bT9HTsR204r0L4pN0aDr3V2222220Q80D496:dN9V2@H3AC`8888888888880";

	std_time = vdm.get_revd_time(revd_msg);
	message_id = vdm.get_message_id(revd_msg);
	channel = vdm.get_channel(revd_msg);
	user_id = vdm.get_user_id(revd_msg);
	repeat_indicator = vdm.get_repeat_indicator(revd_msg);
	print_common(std_time, channel, user_id, message_id, repeat_indicator);

	string sign;
	size_t imo;
	size_t maximum_draught;
	string name;
	od_s overall_dimension;
	sign = vdm_5.get_call_sign(revd_msg);
	imo = vdm_5.get_imo_number(revd_msg);
	maximum_draught = vdm_5.get_maximum_draught(revd_msg);
	name = vdm_5.get_name(revd_msg);
	overall_dimension = vdm_5.get_overall_dimension(revd_msg);
	printf("\nsign:%s\
			\nimo:%ld\
			\nmaximum_draught:%ld\
			\nname:%s\
			\nA:%ld,B:%ld,C:%ld,D:%ld",
		sign.c_str(),imo,maximum_draught,name.c_str(),
		overall_dimension.A,overall_dimension.B,overall_dimension.C,overall_dimension.D);

#endif // DEBUG_VDM_5

#ifdef _MSC_VER
	while (1) { getchar(); }
#endif
	putchar(10);
	return 0;
}

void print_common(std_time_s std_time, string channel,
	size_t user_id, size_t message_id, size_t repeat_indicator) {

	printf("user_id:%ld \
			\nmessage_id:%ld \
			\nrepeat_indicator:%ld", user_id, message_id, repeat_indicator);

	printf("\nchannel:%s", channel.c_str());

	printf("\nrecived time:%ld-%ld-%ld %ld:%ld:%ld", \
		std_time.year, std_time.month, std_time.day,
		std_time.hour, std_time.minute, std_time.second);
}
