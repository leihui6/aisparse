# ais_parse

对获取进行了封装，这意味这接口的添加与调用将会更方便。

*但是当前版本十分不稳定，不稳定是指函数的健壮性以及api设计。*
*欢迎与我取得联系:ptsph#foxmail.com(#->@)*

例如：
你需要获取VDM报文编号为1的Longitude信息，根据标准，Longitude占用28个比特位，在这之前有61个比特位。

你可以在VDM_1中找到相关函数 `size_t get_longitude(const revd_msg_s *_revd_msg);`

之后你会发现实现十分简单：

	size_t VDM_1::get_longitude(const revd_msg_s *_revd_msg){
		size_t longitude = 0;
		convert_to_decimal(_revd_msg->major_msg_p, 61, 28, &longitude);
		return longitude;
	}

当然同样的规则也同样适用于获取其它信息。

----------

### 以下是当前当前版本中提供的api

----------

* [VDM](#0) 
* [VDM_1](#1) &nbsp; [VDM_2](#2) &nbsp; [VDM_3](#3)
* [VDM_5](#5) &nbsp; [VDM_6](#6) &nbsp; [VDM_7](#7)
* [VDM_8](#8) &nbsp; [VDM_12](#12) &nbsp;[VDM_13](#13)
* [VDM_14](#14) &nbsp; [VDM_18](#18) &nbsp;[VDM_19](#19)
* [VDM_24](#24)


## VDM(公共信息)<span id="0">&nbsp;</span>

- `size_t get_message_id(const revd_msg_s * _revd_msg)`

- `size_t get_repeat_indicator(const revd_msg_s * _revd_msg)`

- `size_t get_user_id(const revd_msg_s * _revd_msg)`

- `std_time_s get_revd_time(const revd_msg_s *_revd_msg)`

- `char get_channel(const revd_msg_s *_revd_msg)`

## VDM_1<span id="1">&nbsp;</span>

- `size_t get_navigational_status(const revd_msg_s *_revd_msg)`

- `size_t get_sog(const revd_msg_s *_revd_msg)`

- `size_t get_cog(const revd_msg_s *_revd_msg)`

- `size_t get_true_heading(const revd_msg_s *_revd_msg)`

- `size_t get_longitude(const revd_msg_s *_revd_msg)`

- `size_t get_latitude(const revd_msg_s *_revd_msg)`


## VDM_2<span id="2">&nbsp;</span>

- 见VDM1

## VDM_3<span id="3">&nbsp;</span>

- 见VDM1

## VDM_5<span id="5">&nbsp;</span>

- `size_t get_imo_number(const revd_msg_s *_revd_msg)`

- `string get_call_sign(const revd_msg_s *_revd_msg)`

- `string get_name(const revd_msg_s *_revd_msg)`

- `od_s get_overall_dimension(const revd_msg_s *_revd_msg)`

- `size_t get_maximum_draught(const revd_msg_s *_revd_msg)_maximum_draught)`


## VDM_6<span id="6">&nbsp;</span>

- `string get_application_data(const revd_msg_s *_revd_msg)`

## VDM_7<span id="7">&nbsp;</span>

- not yet

## VDM_8<span id="8">&nbsp;</span>

- `string get_application_data(const revd_msg_s *_revd_msg)`

## VDM_12<span id="12">&nbsp;</span>

- `string get_safety_text(const revd_msg_s *_revd_msg)`

## VDM_13<span id="13">&nbsp;</span>

- not yet

## VDM_14<span id="14">&nbsp;</span>

- `string get_safety_text(const revd_msg_s *_revd_msg)`

## VDM_18<span id="18">&nbsp;</span> 

- `size_t get_sog(const revd_msg_s *_revd_msg)`

- `size_t get_cog(const revd_msg_s *_revd_msg)`

- `size_t get_true_heading(const revd_msg_s *_revd_msg)`

- `size_t get_longitude(const revd_msg_s *_revd_msg)`

- `size_t get_latitude(const revd_msg_s *_revd_msg)`

## VDM_19<span id="19">&nbsp;</span>

- not yet

## VDM_24<span id="24">&nbsp;</span>

- not yet