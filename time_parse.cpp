#include "time_parse.h"

int atoi_s_(char * _str,size_t _len,size_t *_dst){
	if(strlen(_str) != _len){
		return 1;
	}
	for(size_t i = 0;i<_len;i++){
		*_dst = *_dst + (_str[i]-48) * (size_t)pow(10,_len-i-1);
	}
	return 0;
}

int convert_to_stdtime(char * _str,std_time_s * _std_time){
	if(strlen(_str) < 19){
		fprintf(stderr,"error:length should >= 19(have not the standard format of time)\n");
		return 1;
	}
	size_t num = 0;
	for (size_t i = 0;i < 6;i++) {
		switch(i) {
			case 0: // year
				atoi_s_(_str,4,&num);
				_std_time->year = num;
			break;
			case 1: // month
				atoi_s_(_str+4,2,&num);
				_std_time->month = num;
			break;
			case 2: // day
				atoi_s_(_str+6,2,&num);
				_std_time->day = num;
			break;
			case 3: // hour
				atoi_s_(_str+11,2,&num);
				_std_time->hour = num;
			break;
			case 4: // minute
				atoi_s_(_str+14,2,&num);
				_std_time->minute = num;
			break;
			case 5: // second
				atoi_s_(_str+17,2,&num);
				_std_time->second = num;
			break;
		}
		num = 0;
	}
	return 0;
}

int days_from_ad1(size_t _y,size_t _m,size_t _d){
	const int MONTHDAY[] =
        {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    const int MONTHDAY_LEAP[] =
        {0, 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335};
    int days = 0;
    days += ((_y % 4 ? 0 : (_y % 100 ? 1 : (_y % 400 ? 0 : 1)))

        ? MONTHDAY_LEAP[_m] : MONTHDAY[_m]) + _d;

    days += (--_y) * 365 + _y / 4 - _y / 100 + _y / 400;
	
    return days;
}
size_t seconds_between_stdtime(std_time_s * _std_time1,std_time_s * _std_time2){
	int days1 = days_from_ad1(_std_time1->year,_std_time1->month,_std_time1->day);
	
	int days2 = days_from_ad1(_std_time2->year,_std_time2->month,_std_time2->day);
	
	int secds = 
		(days2 - days1) * 86400 + 
		(_std_time2->hour - _std_time1->hour) * 3600 +  
		(_std_time2->minute - _std_time1->minute) * 60 + 
		(_std_time2->second - _std_time1->second);
	
	return (size_t)abs(secds);
}

void clear_revd_freq(revd_freq_s * _revd_freq){
	_revd_freq->set_init_time = false;
}
