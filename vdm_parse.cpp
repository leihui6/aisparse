#include "vdm_parse.h"

unsigned char convert_to_sixascii(char _p){
	if(_p <= 87 && _p >= 48){
		return _p-48;
	}
	else {
		return _p-56;
	}
}

unsigned char convert_to_sixchar(char _p){
	if(_p >= 0 && _p <= 31){
		return _p+64;
	}
	else{
		return _p;
	}
	return 0;
}

int convert_to_decimal_special(char * _str,size_t _beg,size_t _end,size_t _r_need,size_t _l_need,size_t * _result) {
	size_t rst = 0;
	unsigned char p;
	
	for (size_t i = _beg;i < _end;i++) {
		p = convert_to_sixascii(_str[i]);
		if (i == _end-1 ){
			if(i == _beg){
				p = p&((2<<(_r_need-1))-1);
			}
			p = p>>(6-_l_need);
			rst = rst << _l_need;
			rst = p | rst;
		}
		else if(i == _beg){
			p = p&((2<<(_r_need-1))-1);
			rst = p | rst;
		}
		else{
			rst = rst << 6;
			rst = p | rst;
		}
	}
	*_result = rst;
	
	return 0;
}

int convert_to_decimal(char * _str,size_t _before_count,size_t _count,size_t *_result){
	size_t beg = _before_count/6;
	size_t end = (_before_count+_count)/6+1;
	size_t r_need = 6-_before_count%6;
	size_t l_need = (_before_count+_count)%6;
	
	size_t len = strlen(_str);
	if(beg > len-1){
		return 1;
	}
	if(end == len+1){
		l_need = 0;
	}
	else if(end > len+1){
		l_need = 0;
		end = len+1;
	}
	convert_to_decimal_special(_str,beg,end,r_need,l_need,_result);
	return 0;
}

int convert_to_strascii(char * _str,size_t _before_count,size_t _count,char * _dst,size_t _len){
	unsigned char p = 0;
	size_t result = 0;
	size_t ctd_flag = 0;
	
	for(size_t i = 0;(i != _len)&&(i < _count/6);i++) {
		ctd_flag = convert_to_decimal(_str,_before_count + i*6,6,&result);
		if(ctd_flag != 0){
			_dst[i-1] = '\0';
			return 1;
		}
		p = convert_to_sixchar((char)result);
		_dst[i] = p;
	}
	return 0;
}

int convert_to_hexdecimal(char *_str,size_t _before_count,size_t _count,char * _dst,size_t _len){
	char p = 0;
	size_t result = 0;
	size_t w_count = _count/4;
	size_t ctd_flag = 0;
	
	for(size_t i = 0;(i != _len) && (i < w_count);i++) {
		ctd_flag = convert_to_decimal(_str,_before_count + i*4,4,&result);
		if(ctd_flag != 0){
			_dst[i-1] = '\0';
			return 1;
		}
		_snprintf(&p,1,"%x",result);
		_dst[i] = p;
	}
	return 0;
}