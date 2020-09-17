#include "cmd.h"

using namespace std;

cmd::~cmd(){}

cmd::cmd(string &dbn):qkw(dbn){
};


int cmd::fn(void *data, int argc, char **argv, char **azColName){

	SD *sd = (SD*)data;
	switch(sd->n){

		case 6:
		{
			sd->ri = atoi(argv[0]);
		}
		break;




		case 8:
		{

		   string _azc, _val;
		   for(int i=0; i < argc; i++){

			_azc = sd->null2str(azColName[i]);
			_val = sd->null2str(argv[i]);

			if(_azc == "V") sd->cq->print_format(_val,4);

		   }

		}
		break;

		case 7:
		{

		   string _azc, _val;
		   for(int i=0; i < argc; i++){

			_azc = sd->null2str(azColName[i]);
			_val = sd->null2str(argv[i]);

			if(_azc == "rowid") fmt::print("[{}] : ",_val);
			if(_azc == "V") sd->cq->print_format(_val,1);
			if(_azc == "L") sd->cq->print_format(_val,0);

		   }
		   cout << "\n\n";


		}
		break;



		case 5:
		{

		   string _azc, _val;
		   for(int i=0; i < argc; i++){


			_azc = sd->null2str(azColName[i]);
			_val = sd->null2str(argv[i]);

			if(_azc == "V") sd->cq->print_format(_val,1);
			if(_azc == "L") sd->cq->print_format(_val,0);

		   }
		   cout << "\n\n";


		}
		break;


		case 4:
		{

		   string _azc, _val; bool b = 0;
		   for(int i=0; i < argc; i++){

			_azc = sd->null2str(azColName[i]);
			_val = sd->null2str(argv[i]);

			if(_azc == sd->scol ) b = 1;

		   }

		}
		break;


		case 3:
		{

			bool _b = 0, c = 0;
			string _azc, _val, rid;
			int i;
			for(i=0; i < argc; i++){

				_azc = sd->null2str(azColName[i]);
				_val = sd->null2str(argv[i]);

				if(_azc == "rowid") rid = fmt::format("[{}]:",_val);

				if(c == 1){

					if(_azc == "L") {
					  _val = rid+_val;
				 	  sd->cq->print_format(_val,0);
					}
					if(_azc == "V") sd->cq->print_format(_val,1);
					if(_azc == "E") sd->cq->print_format(_val,2);

				}


				if( (_azc == sd->scol) and 
				    (std::regex_search(_val.begin(),_val.end(),sd->rgx)) and
				    (c == 0)
				    ){
					c = 1;
					i = -1;
				}
				
				if ( sd->scol == "all" ){
					if((std::regex_search(_val.begin(),_val.end(),sd->rgx)) and
					    (c == 0)
					    ){
						c = 1;
						i = -1;
					
					}
				}


			}

		}
		break;


		case 2:
		{

		   string _azc, _val;
		   for(int i=0; i < argc; i++){


		        _azc = sd->null2str(azColName[i]);
			_val = sd->null2str(argv[i]);

			if(_azc == "L") sd->cq->print_format(_val,0);
			if(_azc == "V") sd->cq->print_format(_val,1);
			if(_azc == "E") sd->cq->print_format(_val,2);

		   }


		}
		break;

		case 9:
		{

			sd->fs << "\n";
			sd->fs << "label:\n";
			sd->fs << "<label/tag here, mandatory field>\n\n";

			sd->fs << "value:\n";
			sd->fs << "<value, command, string, etc data here, can be empty>\n\n";

			sd->fs << "expl:\n";
			sd->fs << "<explanation/short note here, field can be empty>\n";
		 	sd->fs << "\n---\n";
		}
		break;


		case 1:
		{
			  string _azc,_val;
			  for(int i=0; i < argc; i++){

				_azc = sd->null2str(azColName[i]);
				_val = sd->null2str(argv[i]);

				if( _azc == "rowid" and sd->ri == 1 ){
				    
				    sd->fs << "id:\n";
				    sd->fs << _val;
				    sd->fs << "\n\n";

				}

				if(_azc == "L" and sd->ri == 0 ){

				    sd->fs << "label:\n";
				    sd->fs << _val;
				    sd->fs << "\n\n";

				}

				if(_azc == "V"){

				    sd->fs << "value:\n";
				    sd->fs << _val;
				    sd->fs << "\n\n";

				}

				if(_azc == "E"){

				    sd->fs << "expl:\n";
				    sd->fs << _val;

				    sd->fs << "\n\n";
			  	    sd->fs << "\n---\n";

				}

			  }

		}
		break;


		case 0:
		{

		   string _azc, _val,_rval;
		   int p=0;
		   for(int i=0; i < argc; i++){

			_azc = sd->null2str(azColName[i]);
			_val = sd->null2str(argv[i]);

			if( _azc == "rowid"){
				_rval = fmt::format("[{}]:",_val);
			}
			if(_azc == "L" ){ 
				_val = _rval + _val;	
				sd->cq->print_format(_val,0);
				cout << "\n";
			}
			if(_azc == "V" ){
			  if( not sd->cq->emptystr(_val)) sd->cq->print_format(_val,1);
			  else{ p++;}
			}
			if(_azc == "E"){
			  if( not sd->cq->emptystr(_val)) {sd->cq->print_format(_val,2); cout << endl;}
			  else{ p++; }
			 }

		   }
		   if(p==1) cout << endl;

		}
		break;

		}


	return 0;

}



void cmd::search(string &rgs, string col){

	string _qS; 
	regex rgx(rgs);
	sd->rgx = rgx;
	sd->scol = col; 

	if(col == "L" or col == "V" or col == "E" or col == "all"){
		_qS = fmt::format(mq["Q14"], this->tblname);
		sd->n = 3;
		this->cproc(_qS,this->fn);
		sd->n = -1;
	}

}


int cmd::writeToFile(string &fN, string opt, string dt){


	sd->fs.open(fN, ios::out);
	string _qS;
	sd->ri = 0;

	if(opt == "all"){
		_qS = fmt::format(mq["Q1"],this->tblname);
		sd->n = 1;
		this->cproc(_qS,this->fn);
		sd->n = -1;
	}

	if(opt == "L"){

		  if ( not(cstr2qstr(dt)) ) {
		  	sd->fs.close();
		  	return 1;
		  }

		  _qS = fmt::format(this->mqc["Q5"], this->tblname, "L", dt);
		  sd->n = 1;
		  this->cproc(_qS,this->fn);
		  sd->n = -1;

	}
	
	sd->fs.close();
	return 0;

}



void cmd::getlabel(string &sl, string opt){

	sd->scol = "V";
	if(opt == "L"){
		qS = fmt::format(mq["Q23"],this->tblname, "L", sl);
		sd->n = 8;
		this->cproc(qS,this->fn);
	}

	if(opt == "r"){
		qS = fmt::format(mq["Q23"],this->tblname, "rowid", sl);
		sd->n = 8;
		this->cproc(qS,this->fn);
	}
	sd->n = -1;

}


void cmd::deletefromfile(string &fN, string opt){

	this->fileexists(fN);

	VMSS_t _vdata;

	string _qS, _key, _val, _str;
	MSS_t _mll = {{"label","L"}, {"value","V"}, {"expl","E"}, {"id","rowid"}};

	if(opt == "L" || opt == "m+L") _vdata = this->fileparser(fN);
	if(opt == "id"|| opt == "m+id") _vdata = this->fileparser(fN,"id");


	for(auto _data : _vdata){

		_str = "label";
		_key = _data[_str];

		if(not emptystr(_data[_str])){

			if(opt == "L"){ 
				_qS = fmt::format(mqc["Q11"],this->tblname,_key);
			}
			this->proc(_qS);
			sd->n = -1;

		}else{
			continue;
		}

	}
}


void cmd::insfromfile(string &fN, string opt){

	this->fileexists(fN);

	VMSS_t _vdata;

	string _qS, _key, _val, _str;
	MSS_t _mll = {{"label","L"}, {"value","V"}, {"expl","E"}, {"id","rowid"}};

	if(opt == "L" || opt == "m+L") _vdata = this->fileparser(fN);
	if(opt == "id"|| opt == "m+id") _vdata = this->fileparser(fN,"id");


	for(auto _data : _vdata){

		_str = "label";
		_key = _data[_str];

		if(not emptystr(_data[_str])){

			if(opt == "L") _qS = fmt::format(mqc["Q2.0"],this->tblname,_mll[_str],_data[_str]);
			if(opt == "m+L"){
				_qS = fmt::format(mqc["Q6.1"],this->tblname,_mll[_str],_data[_str],_mll["label"],_key);
			}
			this->cproc(_qS,this->fn);
			sd->n = -1;

		}else{
			continue;
		}


		_str = "expl";

		if(not emptystr(_data[_str])){

			_qS = fmt::format(mqc["Q6.1"],this->tblname,_mll[_str],_data[_str],_mll["label"],_key);
			this->cproc(_qS,this->fn);
			sd->n = -1;

		}else{
			_qS = fmt::format(mqc["Q2.1"],this->tblname,_mll[_str],"NULL");
			this->cproc(_qS,this->fn);
			sd->n = -1;
		}


		_str = "value";

		if(not emptystr(_data[_str])){

			_qS = fmt::format(mqc["Q6.1"],this->tblname,_mll[_str],_data[_str],_mll["label"],_key);
			this->cproc(_qS,this->fn);
			sd->n = -1;

		}else{
			_qS = fmt::format(mqc["Q2.1"],this->tblname,_mll[_str],"NULL");
			this->cproc(_qS,this->fn);
			sd->n = -1;
		}

	}
	
}


int cmd::getexpl(string &dt, string sd){

	if ( not cstr2qstr(dt) ) return 1;

	string _qS;
	if (sd == "L"){
	  _qS = fmt::format(this->mqc["Q5.1"], this->tblname, "L", dt);

	  this->sd->n = 2;
	  this->cproc(_qS,this->fn);
	  this->sd->n = -1;
	}
	else if(sd == "r"){
	  _qS = fmt::format(this->mqc["Q5"], this->tblname, "rowid", dt);
	  this->sd->n = 2;
	  this->proc(_qS);
	  this->sd->n = -1;
	}

	return 0;
	
}



void cmd::getall(){

	string _qS;
	  _qS = fmt::format(qkw::mq["Q14"], this->tblname);

	  this->sd->n = 0;
	  this->cproc(_qS,this->fn);
	  this->sd->n = -1;
	
}


void cmd::setrLV(string &st){
	
	smatch _sm;
	this->splitatcolon(st,_sm);
	qS = fmt::format(mqc["Q6"],this->tblname,"V",_sm.str(2),"rowid",_sm.str(1));
	sd->n=-1;
	this->proc(qS);

}


void cmd::createtbls(string &st){

	VS_t _vs;
	splitstr(st, _vs, ',');
	addquotes(_vs);
	string _qS;

	if(_vs.size() > 0){
		for(auto tn: _vs){
			_qS = fmt::format(this->mqc["Q1"],tn);
			this->proc(_qS);
			sd->n = -1;
		}
	}
	else{
		_qS = fmt::format(this->mqc["Q1"],st);
		this->proc(_qS);
		sd->n = -1;
	}
	
}


int cmd::getV(string &st, string sd){

	if( not cstr2qstr(st) ) return 1;

	string _qS;
	if (sd == "V"){
	  _qS = fmt::format(this->mqc["Q5"], this->tblname, "L", st);

	  this->sd->n = 5;
	  this->cproc(_qS,this->fn);
	  this->sd->n = -1;
	}
	else if(sd == "r"){
	  _qS = fmt::format(this->mqc["Q5"], this->tblname, "rowid", st);
	  this->sd->n = 7;
	  this->proc(_qS);
	  this->sd->n = -1;
	}

	return 0;

}


int cmd::getLV(string &st, string sd){

	  if( not cstr2qstr(st) ) return 1;

	string _qS;
	if (sd == "L"){
	  _qS = fmt::format(this->mqc["Q5"], this->tblname, "L", st);

	  this->sd->n = 4;
	  this->cproc(_qS,this->fn);
	  this->sd->n = -1;
	}
	else if(sd == "r"){
	  _qS = fmt::format(this->mqc["Q5"], this->tblname, "rowid", st);
	  this->sd->n = 4;
	  this->proc(_qS);
	  this->sd->n = -1;
	}

	return 0;

}


void cmd::gettemplate(string &fN){

	sd->fs.open(fN, ios::out);
	sd->b = false;

	sd->n = 9;
	qS = fmt::format("select 1");
	this->cproc(qS,this->fn);
	sd->n = -1;

	sd->fs.close();

}


void cmd::copytbl(string &from, string &to){

	sd->n = 1;
	this->vtbls.clear();
	this->tblcolcount(from);

	qS = fmt::format(this->mqc["Q1"],to);
	this->proc(qS);

	qS = fmt::format(this->mqc["Q10"],this->tblname,from,to);
	this->proc(qS);

}

