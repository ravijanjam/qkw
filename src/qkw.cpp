#include "utils.h"
#include "qkw.h"

using namespace std;

qkw::~qkw(){
	sqlite3_close(this->sdb);
}

qkw::qkw(string &dbn):utils(){

	fileexists(dbn);
	this->dbname = dbn;

        if(sqlite3_open(dbn.c_str(), &(this->sdb))){
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(this->sdb));
		sqlite3_close(this->sdb);
	}//c:condn

	sd = new SD;
	sd->cq = this;

	int cs = cfgchk();

        sqlite3_create_function(this->sdb, "rxset", 3, SQLITE_UTF8, NULL, this->rxset, NULL, NULL );

}



void qkw::cproc(string &st, int fn(void*, int, char**, char**)){

	int rc = sqlite3_exec(this->sdb, st.c_str(), fn, this->sd, &(this->zErrMsg));

	if (rc == SQLITE_OK){
	}
	else if ( rc != SQLITE_OK ){

	    fprintf(stderr, "SQL error: %s\n", this->zErrMsg);
	    sqlite3_free(zErrMsg);

	}

}


int qkw::initdb(char *dbn, int typ=0){

	this->dbn = dbn;
	int rc; 
	rc = sqlite3_open(dbn,&(this->sdb));
	if(rc != SQLITE_OK){
		exit(127);
	}

	qS = fmt::format(mq["Q5"],this->tblname);
	sd->n = -1;
	this->proc(qS);


	return rc;

}


void qkw::search(string &rgs, string col){

	regex rgx(rgs);
	sd->rgx = rgx;
	sd->scol = col;
	if(col != "all"){
		sd->n = 6;
		qS = fmt::format(mq["Q1"], this->tblname);
		this->proc(qS);
		sd->n = -1;
	}
	else{
		qS = fmt::format(mq["Q1"], this->tblname);
		sd->n = 4;
		this->proc(qS);
		sd->n = -1;
	}

}


int qkw::insertpath(string &s){

	    char *d; 
	    d = getcwd((char*)NULL,0);
	    cout << "current path: " << d << endl;
	    if (d != NULL){
	       string _st = fmt::format("{}:{}",s,d);
	       this->insertdata(_st); 
	       return 0; 
	    }
	    else{
	       return 1;
	    }
	   
	return 1;
}


int qkw::insertdata(string &sd){

	VS_t vs;
	string _st;
	smatch sm;
	this->splitatcolon(sd,sm);
	_st = fmt::format("'{}','{}'",sm.str(1),sm.str(2));
	qS = fmt::format(mq["Q7"],this->tblname,"L,V",_st);
	this->proc(qS);

	return 0;

}


void qkw::mergetbls(string &tbl, string &tf){

	  string _ss;
	  VS_t _vs;
	  this->splitstr(tbl,_vs,',');
	  if (_vs.size() > 1){

		_ss = _vs[0];
		this->getschema(_ss);

		if(sd->ri == 0){

	  		qS = fmt::format(mq["Q5.1"],tf,sd->ss);
			proc(qS);

			qS = fmt::format(mq["Q28"],tf);
			sd->n = 10;
			proc(qS);

			addquotes(sd->vs);
			vstr2csv(sd->vs,sd->scol);
			sd->scol = fmt::format("({})",sd->scol);

			for(int i=0; i < _vs.size()-1; i++){
				qS = fmt::format(mq["Q27"],tf,sd->scol,_vs[i],_vs[i+1]);
				proc(qS);
			}
		}
	  	
	  }
	  else{
	  	fmt::format("\e[31mERROR: 2 tables required min, <T,T..,T> <new_tbl>\e[0m");
	  }
		

}

int qkw::getschema(string &tbl){
	
	qS = fmt::format(mq["Q26.1"],tbl);
	sd->n = 9;
	this->proc(qS);
	sd->n = -1;
	return sd->ri;

}


void qkw::listtbls_v1(string tbl, string opt = "all"){

	string _ss;
	if (opt == "all"){
		sd->n = 2;
		this->proc(mq["Q3"]);
		if (vtbls.size()>0){
			for(int i=0; i < (vtbls.size()); i++){
				_ss = fmt::format("'{}'",vtbls[i]);
				qS = fmt::format(mq["Q26"],_ss);
				sd->n = 8;
				this->proc(qS);
			}
			cout << "\n  total count: " << vtbls.size() << "\n";
		}
		sd->n = -1;
	};

	if (opt=="one"){

	  VS_t _vs;
	  this->splitstr(tbl,_vs,',');
	  this->addquotes(_vs);
	  this->vstr2csv(_vs,tbl);

		sd->n = 8;
		qS = fmt::format(mq["Q26"],tbl);
		this->proc(qS);
		sd->n = -1;
	}
}


void qkw::listtbls(string opt = "all"){

	if (opt == "all"){
		sd->n = 2;
		this->proc(mq["Q3"]);
		if (vtbls.size()>0){
			cout << "  ";
			for(int i=0; i < (vtbls.size() - 1); i++){
				cout << vtbls[i] << ",";
			}
			cout << vtbls[vtbls.size()-1] << "\n";
			cout << "  count: " << vtbls.size() << "\n";
		}
		sd->n = -1;
	};
}


void qkw::modifyvalue(string &lbl, string opt){

	smatch _sm;
	string _li, _lf;
	this->splitatcolon(lbl,_sm);
	_li = _sm.str(1);
	_lf = _sm.str(2);

	if(opt=="L"){

		this->sd->sm = _sm;
		qS = fmt::format(mq["Q9.2"], this->tblname, _lf, _li);
		this->proc(qS);
		sd->n = -1;

	}
	if(opt=="r"){

		this->sd->sm = _sm;
		qS = fmt::format(mq["Q9.3"], this->tblname, _lf, _li);
		this->proc(qS);
		sd->n = -1;
	}
	
	sd->n = -1;

}


void qkw::modifylabel(string &lbl,string opt){

	smatch _sm;
	string _li, _lf;
	this->splitatcolon(lbl,_sm);
	_li = _sm.str(1);
	_lf = _sm.str(2);

	if(opt == "L"){

		this->sd->sm = _sm;
		qS = fmt::format(mq["Q9"], this->tblname, _lf, _li);
		this->proc(qS);
		sd->n = -1;

	}
	if(opt == "r"){

		this->sd->sm = _sm;
		qS = fmt::format(mq["Q9.1"], this->tblname, _lf, _li);
		this->proc(qS);
		sd->n = -1;
	}
	
	sd->n = -1;

}



int qkw::editdata(string &rx, string &data, string opt){

	if(opt == "L"){
		qS = fmt::format(mq["Q24"],this->tblname,"L",rx,data);
		this->proc(qS);
	}

	return 5;

}


void qkw::gettblcontent(string &st, string &opt){

	if(br) {
		qS = fmt::format(mq["Q17"],this->tblname, opt, st);
		sd->n = 3;
	}
	else {
		qS = fmt::format(mq["Q15"],this->tblname, opt, st);
		sd->n = 0;
	}
	this->proc(qS);
	sd->n = -1;

}


void qkw::getAlltblcontent(string &tbn){

	if(br) {
		qS = fmt::format(mq["Q14"],tbn);
		sd->n = 3;
	}
	else {
		qS = fmt::format(mq["Q1"],tbn);
		sd->n = 0;
	}

	this->proc(qS);
	sd->n = -1;


}


void qkw::getlabel(string &sl, string opt){

	sd->scol = "V";
	if(opt == "L"){
		qS = fmt::format(mq["Q23"],this->tblname, "L", sl);
		sd->n = 7;
		this->proc(qS);
	}

	if(opt == "r"){
		qS = fmt::format(mq["Q23"],this->tblname, "rowid", sl);
		sd->n = 7;
		this->proc(qS);
	}
	sd->n = -1;

}

void qkw::cleartbls(string &st){

	VS_t _vs;
	this->splitstr(st,_vs,',');
	for(auto _tbl : _vs){
		qS = fmt::format(mq["Q8.0"],_tbl);
		this->proc(qS);
	}

}


void qkw::delentries(string &inf, string type){

	VS_t _vs;
	  this->splitstr(inf,_vs,',');
	  this->addquotes(_vs);
	  this->vstr2csv(_vs,inf);


	if(type == "L"){ 
		qS = fmt::format(mq["Q8"],this->tblname, "L", inf);
		this->sd->n = -1;
		this->proc(qS);
	}

	if(type == "r"){ 
		qS = fmt::format(mq["Q8"],this->tblname, "rowid", inf);
		this->sd->n = -1;
		this->proc(qS);
	}

}


void qkw::rxset(sqlite3_context *sqc, int argc, sqlite3_value **sqv){

        string _sx,_sp,_sd;
        if (argc == 3){ 

                _sx = fmt::format("{}",sqlite3_value_text(sqv[0]));
                _sp = fmt::format("{}",sqlite3_value_text(sqv[1]));
                _sd = fmt::format("{}",sqlite3_value_text(sqv[2]));

                regex _re(_sx);
                if(regex_search(_sd ,_re)){
                        _sd = regex_replace(_sd, _re, _sp);
                        sqlite3_result_text(sqc, _sd.c_str(), -1, SQLITE_TRANSIENT);

                }
                else{
                        sqlite3_result_text(sqc, _sd.c_str(), -1, SQLITE_TRANSIENT);
                }
        }

        else{
                fmt::print("\e[31mERROR\e[0m");
                sqlite3_result_null(sqc);
        }

}


void qkw::deletetbls(string &tbls){

	VS_t vs;
	this->splitstr(tbls,vs,',');
	string opt;

	cout << "Would you like to delete the table [y]: \n";
	cout << "--------------------------------------\n";

	for(auto ts: vs){
	    cout << ts << "  : ";
	    cin >> opt;
	    if(opt == "y"){
	    	ts = fmt::format(mq["Q4"],ts);
		this->proc(ts);
	    }
	    else{
		    fmt::print("The table {} is not deleted\n", ts);
	    }

	}

}


void qkw::copytbl(string &from, string &to){


	sd->n = 1;
	this->vtbls.clear();
	this->tblcolcount(from);

	qS = fmt::format(this->mq["Q1"],to);
	this->proc(qS);

	qS = fmt::format(this->mq["Q13"],from,to);
	this->proc(qS);

}


void qkw::proc(string &st){

	int rc = sqlite3_exec(this->sdb, st.c_str(), this->fn, this->sd, &(this->zErrMsg));
	if ( rc != SQLITE_OK ){

	    fprintf(stderr, "SQL error: %s\n", this->zErrMsg);
	    sqlite3_free(zErrMsg);

	}

}


void qkw::gettbltype(string &st){

	VS_t vs;
	this->splitstr(st,vs,',');
	for(string ss: vs){
		sd->ri = 0;
		this->tblcolcount(ss);
		if(sd->ri == 2) cout << ss << " : D" << endl;
		if(sd->ri == 3) cout << ss << " : C" << endl;
	}

}


void qkw::createtbls(string &st){

	VS_t _vs;
	splitstr(st, _vs, ',');
	string _ss;

	for(auto tn: _vs){
		_ss = fmt::format(this->mq["Q5"],tn);
		this->proc(_ss);
		sd->n = -1;
	}
	
}


int qkw::renametbl(string &from, string &to){

	this->vtbls.clear();
	this->listtbls("all");
	int f = 0;
	for(auto ss : this->vtbls){
		if(ss == to) {
			cout << "found " << to << endl;
			f = 1;
			break;
		}
	}

	if(f == 0){
		string ss = fmt::format(mq["Q11"],from,to);
		this->proc(ss);
		return 2;
	}

	return f;

}


void qkw::listlabels(string &st, string opt){

	if(opt == "LA" ){
		qS = fmt::format(mq["Q29"],this->tblname);
		sd->n = 11;
		this->cproc(qS,this->fn);
		fmt::print("\n\n---------------------");
		fmt::print("\nTotal #labels: {}",sd->cc/2);
		fmt::print("\n---------------------\n");
		sd->cc = 0;
		sd->n = -1;
	}
}//c:func


int qkw::fn(void *data, int argc, char **argv, char **azColName){

	SD *sf = (SD*)data;

	switch (sf->n){

		case 11:
		{

		    string _azc,_val,ss;

		    for(int cc=sf->cc,i=0,
			    g1=1,g2=4,g3=25;
			i < argc; 
			i++,sf->cc++){

		        _azc = sf->null2str(azColName[i]);
		        _val = sf->null2str(argv[i]);

			if(sf->cc%4 == 0) cout << "\n";

			if(_azc == "rowid") {

				fmt::print("|{}|{} ",_val,sf->cq->normalizegaps(_val,g2));

			}
			if(_azc == "L") {
				fmt::print("{}{}",_val,sf->cq->normalizegaps(_val,g3));
				ss = " ";
				fmt::print("{}",sf->cq->normalizegaps(ss,g1));
			}
			

		    }//c:loop

		}
		break;



		case 10:
		{
			if(argv[0] != NULL){
				sf->vs.push_back((string)argv[0]);
			}
			
		}
		break;

		case 9:
		{
			string _ss;
			if (argv[0] != NULL) {
				sf->ss = (string)argv[0];
				if(sf->cq->parsesqlstmt(sf->ss)==0){
					sf->ri = 0;
				}
			}
			else{
				sf->ri = 1;
			}
		}
		break;

		case 8:
		{
			string _azc, _val, sk[3];
			for(int i=0; i<argc; i++){

				if(azColName[i] == NULL) _azc = "";
				else {_azc = (string)azColName[i];}

				if(argv[i] == NULL) _val = "";
				else {_val = (string)argv[i];}

				if(_azc == "name") cout << _val << "   : ";
				if(_azc == "sql") cout << sf->cq->tbltype(_val) << "\n";
			}
		}

		break;

		case 2:
			if (argv[0] != NULL) sf->cq->vtbls.push_back((argv[0]));
		break;

		case 7:
		{
			string _azc, _val;
			for(int i=0; i < argc; i++){

				if(azColName[i] == NULL) _azc = "";
				else {_azc = (string)azColName[i];}

				if(argv[i] == NULL) _val = "";
				else {_val = (string)argv[i];}

				if(sf->scol == _azc){
					fmt::print("{}\n",_val);
				}
			}
		}
		break;

		case 5:
		{
			string _ss = argv[0];
		    	sf->ri = atoi(argv[0]);
		}
		break;


		case 6:
		{
			bool _b = 0;
			for(int i=0; i < argc; i++){

				sf->ss = fmt::format("{}",argv[i]);
				if( (std::regex_search(sf->ss,sf->sm,sf->rgx)==true)){
					_b = 1;
					break;
				}
			}
			if(_b) 
				for(int i=0; i < argc; i++){
				        if(i%argc == 1){
						fmt::print("{}\n",argv[i]);
					}
					else{
						fmt::print("{}  \t:  ",argv[i]);
					}
				}
		}
		break;
		


		case 4:
		{
			bool _b = 0;
			for(int i=0; i < argc; i++){

				sf->ss = fmt::format("{}",argv[i]);
				if( (std::regex_search(sf->ss,sf->sm,sf->rgx)==true) && ((string)azColName[i] == sf->scol)){

					_b = 1;

					break;
				}
			}
			if(_b) 
				for(int i=0; i < argc; i++){
				        if(i%argc == 1){
						fmt::print("{}\n",argv[i]);
					}
					else{
						fmt::print("{}  \t:  ",argv[i]);
					}
				}
		}
		break;



		case 3:
			fmt::print("[{}]  ",argv[0]);
			for(int i=1; i < argc-1; i++){
				cout << argv[i] << "\t";
			}
			cout << argv[argc-1];
			printf("\n");
		break;


		case 0:
			for(int i=0; i < argc-1; i++){
				cout << argv[i] << "\t: ";
			}
			cout << argv[argc-1];
			printf("\n");
		break;


		case 1:

			string ss = argv[0];
			bool t=false; int cc=1;
			for(int i=0; i < ss.size(); i++){
				if (ss[i] == '(') t = true;
				if(t && ss[i]==',') cc+=1;
				if (ss[i] == ')') t = false;
			}
			sf->ri = cc;
			sf->n = -1;

		break;

	}

	return 0;

}


void qkw::sqlite3_ltrm(sqlite3_context* ctx,int i,sqlite3_value** vl){

	string ms = (char*)sqlite3_value_text(vl[0]);
	string ss = (char*)sqlite3_value_text(vl[1]);

	if(ms == ss.substr(0,ms.size())) {
		sqlite3_result_int(ctx,1);
	}
	else{
		sqlite3_result_int(ctx,0);
	}

}


void qkw::sqlite3_rtrm(sqlite3_context* ctx,int i,sqlite3_value** vl){
}


bool qkw::ltrm(string &ss, string &ms){

	if(ms == ss.substr(0,ms.size())) return 1;
	else return 0;

}


bool qkw::rtrm(string &ss, string &ms){

	int n = ss.size();
	if(ms == ss.substr(n - ms.size(), n)) return 1;
	else return 0;

}

void qkw::tblcolcount(string &st){

	this->sd->n = 1;
	st = fmt::format("\'{}\'",st);
	string sr = fmt::format(this->mq["Q10"], st);
	this->proc(sr);

}


void qkw::query(string &sq){

	cout << endl;
	this->sd->n = 0;
	string sr = fmt::format(this->mq["Q1"],sq);
	this->proc(sr);

}
