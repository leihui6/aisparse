#include "srcdata_opt.h"

char * find_char_by_count(char * _str,char _check,size_t _count){
	char * p = _str;
	size_t up_count = 0;
	while (*p != '\0'){
		if(*p == _check){
			up_count ++;
		}
		if(up_count == _count){
			return p;
		}
		p++;
	}
	return NULL;
}

char * find_major_beg(char * _str){
	char * p = NULL;
	p = find_msg_header (_str);
	if(p == NULL){
		return NULL;
	}
	p = find_char_by_count(p,',',5);
	if(p == NULL && (p+1 != NULL)){
		return NULL;
	}
	return p+1;
}

char * find_major_end(char * _str){
	char * p = NULL;
	p = find_msg_header (_str);
	if(p == NULL){
		return NULL;
	}
	p = find_char_by_count(p,',',6);
	if(p == NULL){
		return NULL;
	}
	return p+1;
}

char * find_msg_channel(char * _str){
	char * p = NULL;
	p = find_msg_header (_str);
	if(p == NULL){
		return NULL;
	}
	p = find_char_by_count(p,',',4);
	if(p == NULL){
		return NULL;
	}
	return p+1;
}

int find_major_beg_end(char * _str,char ** _beg,char ** _end){
	char * p = NULL;
	char * beg_tmp = NULL;
	char * end_tmp = NULL;
	p = find_msg_header (_str);
	if(p == NULL){
		_beg = NULL;
		_end = NULL;
		return 1;
	}
	beg_tmp = find_char_by_count(p,',',5);
	if(beg_tmp != NULL){
		*_beg = beg_tmp+1;
	}
	end_tmp = find_char_by_count(p,',',6);
	if(end_tmp != NULL){
		*_end = end_tmp+1;
	}
	return 0;
}

char * find_msg_header(char * _str){
	char * p = _str;
	while (*p != '\0') {
		if (*p == '!' || *p == '$'){
			return p;
		}
		p++;
	}
	return NULL;
}

int cat_major_msg_special(revd_msg_s * _revd_msg,char * _major_msg,size_t _len){
	char * beg = NULL;
	char * end = NULL;
	size_t len = 0;
	char * w_major_msg = _major_msg;
	for(size_t i = 0;i < _revd_msg->count;i++){
		find_major_beg_end(_revd_msg->msg_p[i],&beg,&end);
		if (beg == NULL || end == NULL){
			return 1;
		}
		len = strlen(beg) - strlen(end) - 1;
		strncpy(w_major_msg,beg,len);
		w_major_msg += len;
		if(strlen(_major_msg) >= _len){
			(_major_msg)[_len] = '\0';
			return 0;
		}
	}
	return 0;
}

int recv_all_msg(revd_msg_s * _revd_msg,FILE **_fp){
	char * p = _revd_msg->msg_p[0];
	char * sp = NULL;
	char * count_p = NULL;
	sp = find_msg_header(p);
	if(sp == NULL){
		return 1;
	}
	count_p = find_char_by_count(sp,',',1);
	if(count_p == NULL){
		return 1;
	}
	count_p = count_p + 1;
	_revd_msg->count = (*count_p) - 48;

	for(size_t i = 1;i<_revd_msg->count;i++){
		fgets(_revd_msg->msg_p[i],1024,*_fp);
	}
	return 0;
}

int clear_revd_msg(revd_msg_s *_revd_msg){
	_revd_msg->count = 0;
	memset(&(_revd_msg->msg_p),'\0',sizeof(_revd_msg->msg_p)/sizeof(char));
	return 0;
}

char * cat_major_msg(revd_msg_s * _revd_msg,size_t _len){
	char * major_msg = NULL;
	major_msg = (char *)calloc (_revd_msg->count,1024);
	if(major_msg == NULL){
		return NULL;
	}
	cat_major_msg_special(_revd_msg,major_msg,_revd_msg->count*1024);
	return major_msg;
}

int classify_by_user_id(char * _filename,map<size_t,vector<revd_msg_s> > &_userid_map_msg){
	FILE * fp;
	fp = fopen(_filename, "r");
	if(fp == NULL){
		fprintf(stderr,"error:file open\n");
		return 1;
	}

	char * str_vdm_pos = NULL;
	char * major_msg = NULL;
	size_t user_id = 0;

	revd_msg_s revd_msg;
	clear_revd_msg(&revd_msg);

	while(!feof(fp)){
		fgets(revd_msg.msg_p[0],1024,fp);

		// 判断是否为vdm类型的报文.
		str_vdm_pos = strstr(revd_msg.msg_p[0],"VDM");

		if (str_vdm_pos != NULL ){
			// 将多行报文一起接收.
			recv_all_msg(&revd_msg,&fp);
			major_msg = cat_major_msg(&revd_msg,revd_msg.count*1024);
			if (major_msg == NULL){
				fprintf(stderr,"error:out of memory!\n");
				return 1;
			}
			// OK.
			//fprintf(stdout,"%s\n",major_msg);
			convert_to_decimal(major_msg,8,30,&user_id);
			// For debug. check the user_id.
			//fprintf(stdout,"%ld\n",user_id);
			_userid_map_msg[user_id].push_back(revd_msg);
		}
		// -----------------
		free(major_msg);
		major_msg = NULL;
		clear_revd_msg(&revd_msg);
	}
	fclose(fp);
	return 0;
}

int save_by_user_id(map<size_t,vector<revd_msg_s> > &_userid_map_msg){
	char filename[16];
	memset(filename,'\0',sizeof(filename)/sizeof(char));
	for (map<size_t,vector<revd_msg_s> >::iterator uit = _userid_map_msg.begin(); uit != _userid_map_msg.end();++uit) {
		sprintf(filename,"%d",uit->first);
		strncpy(filename+strlen(filename),".txt",4);
		// For debug.
		//fprintf(stdout,"%s %d\n",filename,strlen(filename));
		//continue;
		FILE * wfp;
		wfp = fopen(filename,"w");
		if (wfp == NULL){
			fprintf(stderr,"error:file open\n");
			return 1;
		}
		vector<revd_msg_s>::iterator
		wit = uit->second.begin(),
		wend = uit->second.end();
		while (wit != wend) {
			for (size_t i = 0;i < wit->count;i++){
				fprintf(wfp,"%s",wit->msg_p[i]);
			}
			wit++;
		}
		memset(filename,'\0',sizeof(filename)/sizeof(char));
		fclose(wfp);
	}
	return 0;
}