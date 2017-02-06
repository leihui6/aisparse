#include "reg_set.h"

int analyse_msg_user_id(char * _str){
	char * p = NULL;
	p = find_major_beg(_str);
	if (p == NULL){
		return 1;
	}
	size_t user_id = 0,ctd_flag = 0; 
	ctd_flag = convert_to_decimal(p,8,30,&user_id);
	if (ctd_flag != 0){
		return 1;
	}
	fprintf(stdout,"%ld\n",user_id);
	
	// do something.
	//...
	return 0;
}

int analyse_by_reg_7_special(vector<revd_msg_s> & _revd_msg_vec){
	vector<revd_msg_s>::iterator 
	rmit = _revd_msg_vec.begin(),
	rmend = _revd_msg_vec.end();
	char * p = NULL;
	
	while (rmit != rmend) {
		p = rmit->msg_p[0];
		
		analyse_msg_user_id(p);
		
		rmit++;
	}
	return 0;
}

int analyse_by_reg_7(map<size_t,vector<revd_msg_s> > &_userid_map_msg){
	map<size_t,vector<revd_msg_s> >::iterator 
	uit = _userid_map_msg.begin(),
	uend = _userid_map_msg.end();
	
	while(uit != uend) {
		analyse_by_reg_7_special(uit->second);
		uit ++;
	}
	return 0;
}
