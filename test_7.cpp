#include "srcdata_opt.h"
#include "vdm_parse.h"
#include "reg_set.h"

int main (int argc,char * argv[]) {
	if(argc != 2){
		fprintf(stdout,"usage:%s datafile\n",argv[0]);
		return 1;
	}
	map<size_t,vector<revd_msg_s> >userid_map_msg;
	
	classify_by_user_id(argv[1],userid_map_msg);
	
	analyse_by_reg_7(userid_map_msg);
	
	return 0;
}