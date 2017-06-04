# ais_parse

对获取功能进行了封装，这意味这接口的添加与调用将会更方便。

| Compiler     |  Status   |
|--------|--------|
| g++ (tdm-1) 4.9.2 | OK |
| MSVC 12.0 | OK |

*但是当前版本十分不稳定，不稳定是指函数的健壮性以及api设计。*
*欢迎与我取得联系:ptsph#foxmail.com(#->@)*

例如：
你需要获取VDM报文编号为1的Longitude信息，根据标准，Longitude占用28个比特位，在这之前有61个比特位。

你可以在VDM_1中找到相关函数 `int get_longitude(const revd_msg_s *_revd_msg);`

之后你会发现实现十分简单：

	int VDM_1::get_longitude(const revd_msg_s *_revd_msg){
		size_t longitude = 0;
		convert_to_decimal(_revd_msg->major_msg_p, 61, 28, &longitude);
		return convert_to_signed_number(longitude, 28);
	}

当然同样的规则也同样适用于获取其它信息。

----------

### 以下是目前版本所提供的api

----------
* [VDM(公共信息)](#VDM(公共信息)) &nbsp; 
* [VDM_1](#VDM_1) &nbsp; [VDM_2](#VDM_2) &nbsp; 
* [VDM_3](#VDM_3) &nbsp; [VDM_6](#VDM_6) &nbsp; 
* [VDM_8](#VDM_8) &nbsp; [VDM_12](#VDM_12) &nbsp; 
* [VDM_14](#VDM_14) &nbsp; [VDM_18](#VDM_18) &nbsp;


## VDM(公共信息)

- `size_t get_message_id(const revd_msg_s * _revd_msg)`

- `size_t get_repeat_indicator(const revd_msg_s * _revd_msg)`

- `size_t get_user_id(const revd_msg_s * _revd_msg)`

- `std_time_s get_revd_time(const revd_msg_s *_revd_msg)`

- `char get_channel(const revd_msg_s *_revd_msg)`

## VDM_1

- `size_t get_navigational_status(const revd_msg_s *_revd_msg)`

- `size_t get_sog(const revd_msg_s *_revd_msg)`

- `size_t get_cog(const revd_msg_s *_revd_msg)`

- `size_t get_true_heading(const revd_msg_s *_revd_msg)`

- `int get_longitude(const revd_msg_s *_revd_msg)`

- `int get_latitude(const revd_msg_s *_revd_msg)`


## VDM_2

- 同VDM1

## VDM_3

- 同VDM1

## VDM_5

- `size_t get_imo_number(const revd_msg_s *_revd_msg)`

- `string get_call_sign(const revd_msg_s *_revd_msg)`

- `string get_name(const revd_msg_s *_revd_msg)`

- `od_s get_overall_dimension(const revd_msg_s *_revd_msg)`

- `size_t get_maximum_draught(const revd_msg_s *_revd_msg)_maximum_draught)`


## VDM_6

- `string get_application_data(const revd_msg_s *_revd_msg)`

## VDM_8

- `string get_application_data(const revd_msg_s *_revd_msg)`

## VDM_12

- `string get_safety_text(const revd_msg_s *_revd_msg)`

## VDM_14

- `string get_safety_text(const revd_msg_s *_revd_msg)`

## VDM_18

- `size_t get_sog(const revd_msg_s *_revd_msg)`

- `size_t get_cog(const revd_msg_s *_revd_msg)`

- `size_t get_true_heading(const revd_msg_s *_revd_msg)`

- `int get_longitude(const revd_msg_s *_revd_msg)`

- `int get_latitude(const revd_msg_s *_revd_msg)`
