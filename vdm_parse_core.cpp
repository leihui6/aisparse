#include "vdm_parse_core.h"

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

int convert_to_signed_number(size_t _num, size_t _total_bits){
	int copy_btis = _num & ~(1 << (_total_bits - 1));

	if ((_num & (1 << (_total_bits - 1))) == 0){
		return copy_btis;
	}
	else{
		return -copy_btis;
	}
}

int convert_to_decimal_special(const char * _str,size_t _beg,size_t _end,size_t _r_need,size_t _l_need,size_t * _result) {
	size_t rst = 0;
	unsigned char p;

	for (size_t i = _beg;i < _end;i++) {
		if (_str[i] == '\0'){
			*_result = rst;
			return 1;
		}
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

int convert_to_decimal(const char * _str,size_t _before_count,size_t _count,size_t *_result){
	size_t beg = _before_count/6;
	size_t end = (_before_count + _count) / 6 +1 ;
	size_t r_need = 6 - _before_count % 6;
	size_t l_need = (_before_count + _count) % 6;

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

int convert_to_strascii(const char * _str,size_t _before_count,size_t _count,char * _dst,size_t _len){
	unsigned char p = 0;
	size_t 
		result = 0,
		strlength = strlen(_str),
		ctd_flag = 0;

	for (size_t i = 0; i * 6 < _count && i * 6 < strlength * 6; i++) {
		
		ctd_flag = convert_to_decimal(_str, _before_count + i * 6, 6, &result);
		
		if (ctd_flag != 0){
			break;
		}
		
		p = convert_to_sixchar((char)result);
		_dst[i] = (char)p;
	}
	_dst[_len] = '\0';
	return 0;
}

int convert_to_hexdecimal(const char *_str,size_t _before_count,size_t _count,char * _dst,size_t _len){
	size_t 
		result = 0,
		strlength = strlen(_str),
		i = 0,
		ctd_flag = 0;

	for (i = 0; i * 4 < _count && i * 4 < strlength * 6; i++){

		ctd_flag = convert_to_decimal(_str, _before_count + i * 4, 4, &result);
		
		if (ctd_flag != 0){
			break;
		}
		sprintf(&_dst[i],"%X", result);
	}
	
	if (i % 2 != 0){
		sprintf(&_dst[i], "%X", 0);
	}
	_dst[_len] = '\0';
	return 0;
}















