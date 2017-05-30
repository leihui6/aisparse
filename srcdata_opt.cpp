#include "srcdata_opt.h"

void atoi_s_(const char * _str, size_t _len, size_t *_dst){
	*_dst = 0;
	if (strlen(_str) < _len){
		return;
	}
	for (size_t i = 0; i < _len; i++){
		if (_str[i] >= '0' && _str[i] <= '9'){
			*_dst *= 10;
			*_dst += _str[i] - '0';
		}
		else
		{
			*_dst = 0;
			return;
		}
	}
}

const char * find_msg_header(const char * _str){
	const char * p = _str;
	while (*p != '\0') {
		if (*p == '!' || *p == '$'){
			return p;
		}
		p++;
	}
	return NULL;
}

const char * find_char_by_count(const char * _str, char _check, size_t _count){
	const char * p = _str;
	while (*p != '\0'){
		if (*p == _check){
			--_count;
		}
		if (_count == 0){
			return p;
		}
		p++;
	}
	return NULL;
}