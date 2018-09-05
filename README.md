# ais_parse

&emsp;&emsp;对解析报文进行了封装，并进行了必要的设计，这意味着接口的添加与调用将会更方便。

>关于基于此的应用：
>[aisparser](https://github.com/macrovve/aisparser) by [macrovve](https://github.com/macrovve "macrovve")

| Compiler     |  Status   |
|--------|--------|
| g++ | OK |
| MSVC  | OK |

*但是当前版本十分不稳定，不稳定是指鲁棒性以及api设计。*
*欢迎及时与我取得联系:ptsph#foxmail.com(#->@)*

## 如何使用
### 1. 先run一遍

&emsp;&emsp;你可以直接编译并运行```./test.cpp```来查看如何调用解析的api，以及查看解析的结果。

### 2. 了解一下

&emsp;&emsp;当你需要获取VDM报文编号为1的`Navigational status`信息，根据标准(`R-REC-M.1371-5-201402-I`)，`Navigational status占`用4个比特位，在这之前有38个比特位。你可以在VDM_1中找到相关函数：`size_t get_navigational_status(const revd_msg_s *_revd_msg)`，之后你会发现实现十分简单：

		size_t VDM_1::get_navigational_status(const revd_msg_s *_revd_msg){
			size_t navigational_status = 0;
		
			convert_to_decimal(_revd_msg->major_msg.c_str(), 38, 4, &navigational_status);
			
			return navigational_status;
		}

&emsp;&emsp;当然同样的规则也同样适用于获取其它信息，由于并没有提供解析所有信息的api，你可以根据需要来添加相应的解析函数，可以参照解析同类数据的函数书写与调用规则。

## 目录

* [VDM(公共信息)](#VDM(公共信息))
* [VDM_1](#VDM_1) 
* [VDM_2](#VDM_2) 
* [VDM_3](#VDM_3)
* [VDM_5](#VDM_5)
* [VDM_6](#VDM_6)
* [VDM_8](#VDM_8)
* [VDM_12](#VDM_12)
* [VDM_14](#VDM_14)
* [VDM_18](#VDM_18)


## VDM(公共信息)

* `size_t get_message_id(const revd_msg_s * _revd_msg)`

* `size_t get_repeat_indicator(const revd_msg_s * _revd_msg)`

* `size_t get_user_id(const revd_msg_s * _revd_msg)`

* `std_time_s get_revd_time(const revd_msg_s *_revd_msg)`

* `char get_channel(const revd_msg_s *_revd_msg)`

## VDM_1

* `size_t get_navigational_status(const revd_msg_s *_revd_msg)`

* `size_t get_sog(const revd_msg_s *_revd_msg)`

* `size_t get_cog(const revd_msg_s *_revd_msg)`

* `size_t get_true_heading(const revd_msg_s *_revd_msg)`

* `int get_longitude(const revd_msg_s *_revd_msg)`

* `int get_latitude(const revd_msg_s *_revd_msg)`


## VDM_2

* 同VDM1

## VDM_3

* 同VDM1

## VDM_5

* `size_t get_imo_number(const revd_msg_s *_revd_msg)`

* `string get_call_sign(const revd_msg_s *_revd_msg)`

* `string get_name(const revd_msg_s *_revd_msg)`

* `od_s get_overall_dimension(const revd_msg_s *_revd_msg)`

* `size_t get_maximum_draught(const revd_msg_s *_revd_msg)_maximum_draught)`


## VDM_6

* `string get_application_data(const revd_msg_s *_revd_msg)`

## VDM_8

* `string get_application_data(const revd_msg_s *_revd_msg)`

## VDM_12

* `string get_safety_text(const revd_msg_s *_revd_msg)`

## VDM_14

* `string get_safety_text(const revd_msg_s *_revd_msg)`

## VDM_18

* `size_t get_sog(const revd_msg_s *_revd_msg)`

* `size_t get_cog(const revd_msg_s *_revd_msg)`

* `size_t get_true_heading(const revd_msg_s *_revd_msg)`

* `int get_longitude(const revd_msg_s *_revd_msg)`

* `int get_latitude(const revd_msg_s *_revd_msg)`



