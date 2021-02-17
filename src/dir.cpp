#include "dir.h"

using namespace std;

dir::~dir(){
	sqlite3_close(this->sdb);
}

dir::dir(string &dbn):qkw(dbn){
};


int dir::fn(void *data, int argc, char **argv, char **azColName){

	SD *sf = (SD*)data;

	switch(sf->n){

		case 5:
		{

		    string _azc,_val;
		    for(int i=0; i < argc; i++){

		        _azc = sf->null2str(azColName[i]);
		        _val = sf->null2str(argv[i]);
			if(_azc == "L") {
				sf->fs << _val;
				sf->fs << ":";
			}
			if(_azc == "V") {
				sf->fs << _val;
				sf->fs << "\n";
			}
		    }
    
		}
		break;
	
		

		case 4:
		{

		    for(int i=0; i < argc-1; i++){
			if(i==0) fmt::print("[{}]  ",argv[i]);
			if(i==1) cout << argv[i] << "\t: ";
		    }
		    cout << argv[argc-1];
		    cout << "\n";
    
		}
		break;
		


		case 3:
		{

		   string _azc, _val;
		   for(int i=0; i < argc; i++){

		        _azc = sf->null2str(azColName[i]);
			_val = sf->null2str(argv[i]);
			}
			if (atoi(argv[0]) == 1) sf->ri = 1;
			else sf->ri = 0;

		}
		break;


		case 2:
		{

			bool _b = 0, c = 0;
			string _azc, _val;
			smatch _sm;
			for(int i=0; i < argc; i++){

				_azc = sf->null2str(azColName[i]);
				_val = sf->null2str(argv[i]);

				if( (_azc == sf->scol) and 
				    (regex_search(_val,_sm,sf->rgx)==true) and
				    (c == 0)
				    ){
					c = 1;
					break;
				    }


				if( (sf->scol == "all") and 
				    (regex_search(_val,_sm,sf->rgx)==true) and
				    (c == 0)
				    ){
					c = 1;
					break;
				    }


				if( (("r+"+_azc) == sf->scol) and 
				    (regex_search(_val,_sm,sf->rgx)==true) and
				    (c == 0)
				    ){
					c = 2;
					break;
				    }


				if( (sf->scol == "r+all") and 
				    (regex_search(_val,_sm,sf->rgx)==true) and
				    (c == 0)
				    ){
					c = 2;
					break;
				    }


			}

			if(c == 1){

			    for(int i=0; i < argc-1; i++){
				cout << argv[i] << "\t:  ";
			    }
			    if(argc-1 >= 0)cout << argv[argc-1];
			    cout << "\n";
			}

			if(c == 2){

				    for(int i=0; i < argc-1; i++){
					if(i==0) fmt::print("[{}]  ",argv[i]);
					if(i==1) cout << argv[i] << "\t: ";
				    }
				    cout << argv[argc-1];
				    cout << "\n";
			}

		}
		break;


		case 1:
		{

		    for(int i=0; i < argc-1; i++){
			cout << argv[i] << "\t:  ";
		    }
		    cout << argv[argc-1];
		    cout << "\n";

    
		}
		break;


		case 0:
		{

		    DIR *dp; struct dirent *dr;
		    dp = opendir(argv[1]);

		    if (dp != NULL){
		       printf(" [Y] : %s\t%s\n", argv[0], argv[1]); 
		    }
		    else{
		       printf(" [N] : %s\t%s\n", argv[0], argv[1]); 
		    }

		}
		break;


	}

	return 0;

}


int dir::checkaccess(string &st, string opt){
        
        cout << "\nDirectory accessibility : Y|N" 
             << "\n-------------------------------"
             << endl;
	
	string qS = fmt::format(qkw::mq["Q1"],this->tblname);
	if (opt == "all"){
		this->sd->n = 0;
		this->cproc(qS,this->fn);
		this->sd->n = -1;
	}
	else if(opt == "L"){
		if(not cstr2qstr(st)) return 1;
		qS = fmt::format(mqd["Q5"],this->tblname, st);	
		this->sd->n = 0;
		this->cproc(qS,this->fn);
		this->sd->n = -1;
		cout << endl;

	}

	
	return 0;
}


void dir::insfromfile(string &fN, string opt){

	this->fileexists(fN);
	smatch _sm;
	fstream nf;
	string tp;
	nf.open(fN, ios::in);
	while(getline(nf,tp)){
		
		if(this->splitatcolon(tp,_sm)){

			if (opt == "insert"){
				qS = fmt::format(mqd["Q2.1"],this->tblname,_sm.str(1),_sm.str(2));
				this->proc(qS);
			}
			if (opt == "update"){
				qS = fmt::format(mqd["Q6.0"],this->tblname,_sm.str(1),_sm.str(2));
				this->proc(qS);
			}

			_sm.str(1) = "";
			_sm.str(2) = "";

		}
		
	}
	nf.close();

}


void dir::deletefromfile(string &fN, string opt){

	this->fileexists(fN);
	smatch _sm;
	fstream nf;
	string tp;
	nf.open(fN, ios::in);
	while(getline(nf,tp)){
		
		if(this->splitatcolon(tp,_sm)){

			if (opt == "L"){
				qS = fmt::format(mqd["Q12"],this->tblname,_sm.str(1));
				this->proc(qS);
			}

			_sm.str(1) = "";
			_sm.str(2) = "";

		}
		
	}
	nf.close();

}


int dir::writeToFile(string &fN, string &st, string opt){

	sd->fs.open(fN, ios::out);

	if(opt == "all"){
		qS = fmt::format(qkw::mq["Q1"],this->tblname);
		sd->n = 5;
		this->cproc(qS,this->fn);
		sd->n =-1;
	}

	if ( not cstr2qstr(st) ) {
		sd->fs.close();
		return 1;
	}

	if(opt == "L"){
		qS = fmt::format(mqd["Q5"],this->tblname,st);
		sd->n = 5;
		this->cproc(qS,this->fn);
		sd->n =-1;
	}

	sd->fs.close();
	return 0;
}


int dir::ltrim(string &rx, string &st, string opt){

	if ( not cstr2qstr(st) ) return 1;

	string _ss;
	_ss = "^"+rx;
	
	if(opt == "L"){
		qS = fmt::format(mqd["Q7.1"],this->tblname,"V",_ss,"",st);
		this->proc(qS);
	}


	if(opt == "r"){
		qS = fmt::format(mqd["Q7.2"],this->tblname,"V",_ss,"",st);
		this->proc(qS);
	}

	return 0;
}


int dir::lappend(string &st, string &ups, string opt){

	if(not cstr2qstr(st)) return 1;
	if(opt == "L"){
		qS = fmt::format(mqd["Q7.1"],this->tblname,"V","^",ups,st);
		this->proc(qS);
	}

	if(opt == "r"){
		qS = fmt::format(mqd["Q7.2"],this->tblname,"V","^",ups,st);
		this->proc(qS);
	}

	return 0;
	
}

int dir::editdata(string &rx, string &data, string opt){

	if(opt == "V"){
		qS = fmt::format(mqd["Q6"],this->tblname,"V",rx,data);
		this->proc(qS);
	}

	if(opt == "L"){
		qS = fmt::format(mqd["Q6"],this->tblname,"L",rx,data);
		this->proc(qS);
	}

	return 5;

}


bool dir::getpath(string &s){

    char *d; 
    d = getcwd((char*)NULL,0);
    cout << "added directory: " << d << endl;
    if (d != NULL){
	    s = (string)d;
       return true; 
    }
    else{
       return false;
    }
    
    
}


void dir::editdata(string &rgx, string &fstr, string &lf, string opt){


	VS_t _vs;
	string _sp;
	if(opt == "L"){

		if(cstr2qstr(lf)){
		qS = fmt::format(mqd["Q7"],this->tblname,"L",rgx,fstr,lf);
		this->proc(qS);
		}
	}


	if(opt == "all"){
		qS = fmt::format(mqd["Q6"],this->tblname,"L",rgx,fstr);
		this->proc(qS);
	}


	if(opt == "r"){

		if(cstr2qstr(lf)){
		qS = fmt::format(mqd["Q7"],this->tblname,"rowid",rgx,fstr,lf);
		}
	}


}


int dir::setdata(string &st){

	smatch _sm;
	this->splitatcolon(st,_sm);

	qS = fmt::format(mqd["Q4"],this->tblname, st);
	sd->n = 3;
	this->proc(qS);
	sd->n =-1;
	if(sd->ri == 0){
		fmt::format("\e[31mERROR: No label named: {} found\e[0m\n",st);	
		return 1;
	}

	if (_sm.str(2).size() == 0){
		fmt::format("\e[31mERROR: Empty string, not updated \e[0m\n");	
		return 2;
	}

	qS = fmt::format(mqd["Q2"],this->tblname, _sm.str(1), _sm.str(2));
	sd->n = -1;
	this->proc(qS);

	return 0;


}



void dir::search(string &rgs, string opt){

	string _qS; 
	regex rgx(rgs);
	this->sd->rgx = rgx;
	this->sd->scol = opt; 

	if(opt == "L" or opt == "V" or opt == "all"){
		_qS = fmt::format(mq["Q1"], this->tblname);
		this->sd->n = 2;
		this->cproc(_qS,this->fn);
		this->sd->n = -1;
	}


	if(opt == "r+L" or opt == "r+V" or opt == "r+all"){
		_qS = fmt::format(mqd["Q11"], this->tblname);
		this->sd->n = 4;
		this->cproc(_qS,this->fn);
		this->sd->n = -1;
	}

}


int dir::checkpath(string &st){

	string _sd;
	if(!this->getpath(_sd)){
		fmt::print("\e[31m\e[1m ERROR: failed \e[0m");
		return 1;
	}

        string _qS; 

	_qS = fmt::format(mqd["Q3"], this->tblname, _sd);

	this->sd->n = 0;
	this->cproc(_qS,this->fn);
	this->sd->n = -1;

	return 0;
}


void dir::listlabels(string &st, string opt){

	if(opt == "all" ){
		sd->n = 1;
		qS = fmt::format(qkw::mq["Q1"],this->tblname);
		this->cproc(qS,this->fn);
		sd->n = -1;

	}


	if(opt == "r+all" ){
		sd->n = 4;
		qS = fmt::format(qkw::mq["Q14"],this->tblname);
		this->cproc(qS,this->fn);
		sd->n = -1;

	}


	if(opt == "L" ){
		if(cstr2qstr(st)){
		qS = fmt::format(mqd["Q5"],this->tblname,st);
		sd->n = 1;
		this->cproc(qS,this->fn);
		sd->n = -1;
		}
	}


	if(opt == "LA" ){
		qkw::listlabels(st,opt);
	}


	if(opt == "r" ){

		if(cstr2qstr(st)){
		qS = fmt::format(qkw::mq["Q22"],this->tblname,st);
		sd->n = 4;
		this->cproc(qS,this->fn);
		sd->n = -1;
		}

	}

}


int dir::addpath(string &sl){

	string _sd;
	if(!this->getpath(_sd)){
		fmt::print("\e[31m\e[1m ERROR: failed \e[0m");
		return 1;
	}

        string _qS; 
	_qS = fmt::format(mqd["Q2"], this->tblname, sl, _sd);

	this->sd->n = 0;
	this->proc(_qS);
	this->sd->n = -1;

	return 0;

}

