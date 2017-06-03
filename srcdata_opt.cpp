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

const char * find_char_by_count(const char * _str,char _check,size_t _count){
	const char * p = _str;
	while (*p != '\0'){
		if(*p == _check){
			--_count;
		}
		if (_count == 0){
			return p;
		}
		p++;
	}
	return NULL;
}

const char * find_major_beg(const char * _str){
	const char * p = NULL;
	p = find_msg_header (_str);
	if(p == NULL){
		return NULL;
	}
	p = find_char_by_count(p,',',5);
	if (p == NULL){
		return NULL;
	}
	if (p + 1 == NULL){
		return NULL;
	}
	return p+1;
}

const char * find_major_end(const char * _str){
	const char * p = NULL;
	p = find_msg_header (_str);
	if(p == NULL){
		return NULL;
	}
	p = find_char_by_count(p,',',6);
	if (p == NULL){
		return NULL;
	}
	return p;
}

int find_major_beg_end(const char *_str, const char **_beg, const char **_end){
	const char * beg_tmp = NULL;
	const char * end_tmp = NULL;

	*_beg = ((beg_tmp = find_major_beg(_str)) == NULL) ? NULL : beg_tmp;
	*_end = ((end_tmp = find_major_end(_str)) == NULL) ? NULL : end_tmp;

	return 0;
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

int recv_all_msg(revd_msg_s * _revd_msg,FILE **_fp){
	const char * p = NULL;
	const char * first_msg_p = _revd_msg->msg[0].c_str();
	p = find_msg_header(first_msg_p);

	if(p == NULL){
		return 1;
	}
	p = find_char_by_count(p, ',', 1);
	if(p == NULL){
		return 1;
	}
	if (p + 1 == NULL){
		return 1;
	}
	_revd_msg->count = *(++p) - 48;

	char input[1024];

	for(size_t i = 1;i<_revd_msg->count;i++){
		fgets(input, 1024, *_fp);
		_revd_msg->msg[i] = input;
	}
	return 0;
}

int clear_revd_msg(revd_msg_s *_revd_msg){
	_revd_msg->count = 0;
	//memset(&(_revd_msg->msg_p),'\0',sizeof(_revd_msg->msg_p)/sizeof(char));
	return 0;
}

char * cat_major_msg(revd_msg_s * _revd_msg){
	char * all_major_msg = NULL;
	all_major_msg = (char *)calloc(_revd_msg->count, 1024);
	if (all_major_msg == NULL){
		return NULL;
	}
	const char *beg = NULL,*end = NULL;
	signed int len = 0;
	char *all_major_msg_tmp = all_major_msg;

	for (size_t i = 0; i < _revd_msg->count; i++){
		find_major_beg_end(_revd_msg->msg[i].c_str(), &beg, &end);

		if (beg == NULL || end == NULL){
			free(all_major_msg_tmp);
			return NULL;
		}
		len = end - beg;
		strncpy(all_major_msg_tmp, beg, len);
		all_major_msg_tmp += len;
	}

	return all_major_msg;
}

int classify_by_user_id(char * _filename,map<size_t,vector<revd_msg_s> > &_userid_map_msg){
	FILE * fp;
	fp = fopen(_filename, "r");
	if(fp == NULL){
		fprintf(stderr,"error:file open\n");
		return 1;
	}

	char * major_msg = NULL;
	size_t user_id = 0;

	revd_msg_s revd_msg;
	clear_revd_msg(&revd_msg);
	char input[1024];

	while(!feof(fp)){
		fgets(input, 1024, fp);
		revd_msg.msg[0] = input;

		// 判断是否为vdm类型的报文.
		if (string::npos != revd_msg.msg[0].find("VDM")){
			// 将多行报文一起接收.
			recv_all_msg(&revd_msg,&fp);
			major_msg = cat_major_msg(&revd_msg);
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
				fprintf(wfp,"%s",wit->msg[i].c_str());
			}
			wit++;
		}
		memset(filename,'\0',sizeof(filename)/sizeof(char));
		fclose(wfp);
	}
	return 0;
}

int read_srcdata(const char * _filename , vector<revd_msg_s> &_revd_msg_vec){
    FILE * fp = NULL;
	fp = fopen(_filename, "r");
	if(fp == NULL){
		fprintf(stderr,"error:file open\n");
		return 1;
	}
	char * str_vdm_pos = NULL;
	char * all_major_msg = NULL;

	revd_msg_s revd_msg;
	clear_revd_msg(&revd_msg);
	char input[1024];
	while(!feof(fp)){
		fgets(input, 1024, fp);
		revd_msg.msg[0] = input;

		// 判断是否为vdm类型的报文.
		if (revd_msg.msg[0].find("VDM") != string::npos){

			recv_all_msg(&revd_msg,&fp);
			revd_msg.major_msg = (cat_major_msg(&revd_msg));
			
			_revd_msg_vec.push_back(revd_msg);

		}

		clear_revd_msg(&revd_msg);
	}
	fclose(fp);
	return 0;
}






























