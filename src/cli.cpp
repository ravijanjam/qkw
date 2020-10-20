#include "qkw.h"
#include "dir.h"
#include "cmd.h"
#include "utils.h"
#include "ktypes.h"
#include "help.h"

using namespace std;

#define QKW_VERSION "1.0"

template<typename T>
T* init(T *tc, utils *ut, US_t &vstbl, 
        string &sdb, string &tbl, bool fg){

	YN_t yn;
	string opt;
	int ird, irc, irt, ir;

	irc = ut->cfggetdata(sdb);

	if ( irc == 0 ){
		tc = new T(sdb);
	}//c:condn
	else{
		exit(1);
	}//c:condn

	if(fg == 0){
		irt = ut->cfggetdata(tbl);

		if ( irt == 0 ){
			tc->tblname = tbl;
		}//c:condn
		else{
			exit(1);
		}//c:condn
	}


	if (ut->cfggetdata(tbl) == 0 and fg == 1){

		VS_t _vs;
		if(ut->splitstr(tbl,_vs,',')) {
			for(auto _t : _vs){
				vstbl.insert(ut->rmspaces(_t));
			}
		}//c:if
		else{
			fmt::print("\e[31mERROR: {}\e[1m",tbl);
		}
		
	}//c:condn

	return tc;
}//c:func

int main(int argc, char *argv[]){

	utils *ut = new utils();
	dir *qiD; cmd *qiC; 
	dir *qsD; cmd *qsC; 

	help *hl = new help();

	string _sk[3];
	int l=0, nl, hf=0;

	YN_t yn;
	string sdb, tbl, opt, sc;
	int ird, irc, irt, ir;

	MUSS_t vstbl;

	CS_t cs;
	cs.clear();

	sdb = "cmd.insert.db";
	tbl = "cmd.insert.table";
	qiC = init<cmd>(qiC,ut,vstbl["C"],sdb,tbl,0);

	sdb = "cmd.search.db";
	tbl = "cmd.search.table";
	qsC = init<cmd>(qsC,ut,vstbl["C"],sdb,tbl,1);


	sdb = "dir.insert.db";
	tbl = "dir.insert.table";
	qiD = init<dir>(qiD,ut,vstbl["D"],sdb,tbl,0);


	sdb = "dir.insert.db";
	tbl = "dir.insert.table";
	qsD = init<dir>(qsD,ut,vstbl["D"],sdb,tbl,0);


	if(argc == 1){

		fmt::print("\e[1mqkw version {}\e[0m\n",QKW_VERSION);
		fmt::print("To get help: \e[1mqkw -h <option_string>\e[0m");
	}

	for( ; l < argc; l++ ){

		opt = (string)argv[l];
		ir = ut->optstr(opt);

		nl = argc - l;
		
		if( opt == "h" or opt == "help" ) {
			hf = 1;
			if(nl == 1) fmt::print("To get help: \e[1mqkw -h <option_string>\e[0m");
			cs.clear();
			continue;
		}

		
		if( opt == "v" or opt == "version" ) {
			fmt::print("\e[1mqkw version {}\e[0m\n",QKW_VERSION);
			cs.clear();
			continue;
		}


		if( opt == "setcfg" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}


			if(nl > 1){

				l++;
				if(setenv(ut->envtag,argv[l],1) == 0){

					ut->cfgchk();


					sdb = "cmd.insert.db";
					tbl = "cmd.insert.table";
					qiC = init<cmd>(qiC,ut,vstbl["C"],sdb,tbl,0);

					sdb = "cmd.search.db";
					tbl = "cmd.search.table";
					qsC = init<cmd>(qsC,ut,vstbl["C"],sdb,tbl,1);


					sdb = "dir.insert.db";
					tbl = "dir.insert.table";
					qiD = init<dir>(qiD,ut,vstbl["D"],sdb,tbl,0);


					sdb = "dir.insert.db";
					tbl = "dir.insert.table";
					qsD = init<dir>(qsD,ut,vstbl["D"],sdb,tbl,0);



				}
			}
			else{
				fmt::print("  \e[1m[{}] argument required\e[0m\n",1);
			}

			cs.clear();
			continue;
		
		}




		if (opt == "dbname"){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}

			fmt::print("insert databases");
			fmt::print("  cmd[C]: {}\n", qiC->dbname);
			fmt::print("  dir[D]: {}\n", qiD->dbname);

			fmt::print("search databases");
			fmt::print("  cmd[C]: {}\n", qsC->dbname);
			fmt::print("  dir[D]: {}\n", qsD->dbname);

			continue;

		}//c:condn


		// copy tables
		if( opt == "cpyTC" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
			

			if(nl > 2){

				l++;
				_sk[0] = argv[l];

				l++;
				_sk[1] = argv[l];

				qiC->copytbl(_sk[0],_sk[1]);
			}
			else{
				fmt::print("\e[1mNOTE: \e[33m-cpyTC <from> <to>\e[0m\n");
				fmt::print("  \e[1m[{}] argument required\e[0m\n",2);
			}
			continue;
		}


		if( opt == "mergetbls" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
		

			if(nl > 2){

				l++;
				_sk[0] = argv[l];

				l++;
				_sk[1] = argv[l];

				qiC->mergetbls(_sk[0],_sk[1]);
			}
			else{
				fmt::print("\e[1mNOTE: \e[33m-mergetbls <T,T...,T> <new_T>\e[0m\n");
				fmt::print("  \e[1m[{}] argument required\e[0m\n",2);
			}
			continue;
		}


		if( opt == "cpyTD" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
	

			if(nl > 2){
				l++;
				_sk[0] = argv[l];

				l++;
				_sk[1] = argv[l];

				qiD->copytbl(_sk[0],_sk[1]);
			}
			else{
				fmt::print("\e[1mNOTE: \e[33m-cpyTD <from> <to>\e[0m\n");
				fmt::print("  \e[1m[{}] argument required\e[0m\n",2);
			}
			continue;
		}


		if( opt == "tD" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
	

			if(nl > 1){

				l++;
				_sk[0] = argv[l];

				qiD->tblname = _sk[0];
			}
			else{
				fmt::print("  \e[1m[{}] argument required\e[0m\n",1);
			}
			continue;
		
		}


		if( opt == "tbl" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}

			if(nl > 1){

				l++;
				_sk[0] = argv[l];

				qiD->tblname = _sk[0];
				qiC->tblname = _sk[0];
			}
			else{
				fmt::print("  \e[1m[{}] argument required\e[0m\n",1);
			}
			continue;
		}


		if( opt == "db" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}

			if(nl > 1){

				l++;
				_sk[0] = argv[l];

				qiC = new cmd(_sk[0]);
				qiD = new dir(_sk[0]);
			}
			else{
				fmt::print("  \e[1m[{}] argument required\e[0m\n",1);
			}
			continue;
		}
		
	
		
		


		if( opt == "tC" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
			

			if(nl > 1){

				l++;
				_sk[0] = argv[l];

				qiC->tblname = _sk[0];
			}
			else{
				fmt::print("  \e[1m[{}] argument required\e[0m\n",1);
			}
			continue;
		
		}



		if( opt == "exec" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}

			if(nl > 1){
				l++;
				_sk[0] = argv[l];
				system(argv[l]);

			}
			else{
				fmt::print("  \e[1m[{}] argument required\e[0m\n",1);
			}
			continue;
		}


		if( opt == "gettemplate" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}

			if(nl > 1){
				l++;
				_sk[0] = argv[l];


				qiC->gettemplate(_sk[0]);
			}
			else{
				fmt::print("  \e[1m[{}] argument required\e[0m\n",1);
			}
			continue;
		}


		if( opt == "cleartbls" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
	

			if(nl > 1){

				l++;
				_sk[0] = argv[l];

				qiC->cleartbls(_sk[0]);
			}
			else{
				fmt::print("  \e[1m[{}] argument required\e[0m\n",1);
			}
			continue;
		}




		if( opt == "addpath" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
			
			if(nl > 1){
			l++;
			_sk[0] = argv[l];
			qiD->addpath(_sk[0]);
			}
			else{
				fmt::print("\e[1mNOTE: \e[33m-addpath <label>\e[0m\n");
				fmt::print("  \e[1m[{}] argument required\e[0m\n",1);
			}
			continue;

		}



		if( opt == "tbltype" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
		
			if(nl > 1){
			l++;
			_sk[0] = argv[l];
			qiD->listtbls_v1(_sk[0],"one");
			}
			else{
				fmt::print("  \e[1m[{}] argument required\e[0m\n",1);
			}
			continue;

		}


		if( opt == "lappend+r" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
			
			if(nl > 1){
			l++;
			_sk[0] = argv[l];

			l++;
			_sk[1] = argv[l];
			qiD->lappend(_sk[0],_sk[1],"r");
			}
			else{
				fmt::print("\e[1mNOTE: \e[33m-lappend+r <r,r..r>\e[0m\n");
				fmt::print("  \e[1m[{}] argument required\e[0m\n",2);
			}
			continue;

		}



		if( opt == "lappend" ){
			if(nl > 1){

				if(hf == 1) {
					hl->getstr(opt);
					break;
				}
		
			l++;
			_sk[0] = argv[l];

			l++;
			_sk[1] = argv[l];
			qiD->lappend(_sk[0],_sk[1],"L");
			}
			else{
				fmt::print("\e[1mNOTE: \e[33m-lappend <L,L..L>\e[0m\n");
				fmt::print("  \e[1m[{}] argument required\e[0m\n",2);
			}
			continue;

		}


		if( opt == "ltrim+r" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
		
			if(nl > 1){
				l++;
				_sk[0] = argv[l];

				l++;
				_sk[1] = argv[l];

				qiD->ltrim(_sk[0],_sk[1],"r");
			}
			else{
				fmt::print("\e[1mNOTE: \e[33m-ipath <label>\e[0m\n");
				fmt::print("  \e[1m[{}] argument required\e[0m\n",2);
			}
			continue;

		}



		if( opt == "ltrim" ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}

			if(nl > 2){
				l++;
				_sk[0] = argv[l];

				l++;
				_sk[1] = argv[l];

				qiD->ltrim(_sk[0],_sk[1],"L");
			}
			else{
				fmt::print("\e[1mNOTE: \e[33m-ltrim <regex> <L,L,>\e[0m\n");
				fmt::print("  \e[1m[{}] argument required\e[0m\n",2);
			}
			continue;

		}





		/************
		   CONFIG 
		************/

		if( opt == "cfgfile" ){


			if(hf == 1) {
				hl->getstr(opt);
				break;
			}

			fmt::print("\e[1m{}\n\e[0m",ut->cfgfile);
			continue;
		}
		

		if( ir==0 ){
			cs.merge(ut->splitstr2set(opt));
		}


		/************
		   LABELS 
		************/
		if(ut->matchopts(cs, "eDAV") && nl > 2){

			l++;
			_sk[0] = argv[l];

			l++;
			_sk[1] = argv[l];

			_sk[2] = "";
			qiD->editdata(_sk[0],_sk[1],_sk[2],"all");
		}


		if(ut->matchopts(cs, "eDLV") && nl > 3){

			l++;
			_sk[0] = argv[l];

			l++;
			_sk[1] = argv[l];

			l++;
			_sk[2] = argv[l];
			qiD->editdata(_sk[0],_sk[1],_sk[2],"L");
			cs.clear();

		}
		

		if(ut->matchopts(cs, "eDrV") && nl > 3){

			if (nl > 3){

			l++;
			_sk[0] = argv[l];

			l++;
			_sk[1] = argv[l];

			l++;
			_sk[2] = argv[l];
			qiD->editdata(_sk[0],_sk[1],_sk[2],"r");
			}
			cs.clear();
		}


		/************
		   TABLES 
		************/
		if(ut->matchopts(cs, "lTA")){


			if(hf == 1) {
				hl->getstr("lTA");
				break;
			}

			fmt::print("\nTables from the 'cmd' database:\n");
			qiC->listtbls_v1("","all");

			fmt::print("\nTables from the 'dir' database:\n");
			qiD->listtbls_v1("","all");
			cs.clear();
		}

		if(ut->matchopts(cs, "lTC")){

			if(hf == 1) {
				hl->getstr("lTC");
				break;
			}

			fmt::print("\nTables from the 'cmd' database:\n");
			qiC->listtbls_v1("","all");
			cs.clear();
		}

		if(ut->matchopts(cs, "lTD")){

			if(hf == 1) {
				hl->getstr("lTD");
				break;
			}
			
			fmt::print("\nTables from the 'dir' database:\n");
			qiD->listtbls_v1("","all");
			cs.clear();
		}


		// rename tables
		if( ut->matchopts(cs, "mTD")){ 

			if(hf == 1) {
				hl->getstr("mTD");
				break;
			}
		
		    if( nl > 2 ){
			
			l++;
			_sk[0] = argv[l];
			l++;
			_sk[1] = argv[l];
			qiD->renametbl(_sk[0],_sk[1]);
		    }
		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",2);
		    }
		    cs.clear();
		}


		if( ut->matchopts(cs, "mTC") ){

			if(hf == 1) {
				hl->getstr("mTC");
				break;
			}
		

			if( nl > 2 ){
				_sk[0] = argv[l];
				l++;
				_sk[1] = argv[l];
				qiC->renametbl(_sk[0],_sk[1]);
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",2);
			}
 
			cs.clear();
		}


		// insert LV data
		if(ut->matchopts(cs, "lDA")){

			if(hf == 1) {
				hl->getstr("lDA");
				break;
			}
		

			_sk[0] = "";
			qiD->listlabels(_sk[0],"all");
			cs.clear();
		}


		// insert LV data
		if(ut->matchopts(cs, "lDrA")){


			if(hf == 1) {
				hl->getstr("lDrA");
				break;
			}
		
			_sk[0] = "";
			qiD->listlabels(_sk[0],"r+all");
			cs.clear();
		}



		if( ut->matchopts(cs, "lDL") or 
		    ut->matchopts(cs, "lD") ){


			if(hf == 1) {
				hl->getstr("lD");
				break;
			}
		

			if( nl > 1 ){
			l++;
			_sk[0] = argv[l];
			qiD->listlabels(_sk[0],"L");
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();

		}



		if( ut->matchopts(cs, "lDrL") or
		    ut->matchopts(cs, "lDr") ){ 


			if(hf == 1) {
				hl->getstr("lDr");
				break;
			}
		

			if( nl > 1 ){
			l++;
			_sk[0] = argv[l];
			qiD->listlabels(_sk[0],"r");
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();

		}



		if( ut->matchopts(cs, "gD") ){



			if(hf == 1) {
				hl->getstr("gD");
				break;
			}
		

			if( nl > 1 ){
				l++;
				_sk[0] = argv[l];
				qiD->getlabel(_sk[0],"L");
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();
			

		}


		if( ut->matchopts(cs, "gC") ){

			if(hf == 1) {
				hl->getstr("gC");
				break;
			}
		

			if( nl > 1 ){
				l++;
				_sk[0] = argv[l];
				qiC->getlabel(_sk[0],"L");
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();
			

		}


		if( ut->matchopts(cs, "gDr")){


			if(hf == 1) {
				hl->getstr("gDr");
				break;
			}
		

			if( nl > 1 ){
				l++;
				_sk[0] = argv[l];
				qiD->getlabel(_sk[0],"r");
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();
		}

	

		if( ut->matchopts(cs, "lDr") ){


			if(hf == 1) {
				hl->getstr("lDr");
				break;
			}
		
			if( nl > 1 ){
				_sk[0] = argv[l];
				qiD->listlabels(_sk[0],"r");
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();

		}


		// create table 
		if(ut->matchopts(cs, "cTC")){


			if(hf == 1) {
				hl->getstr("cTC");
				break;
			}
		
			if( nl > 1 ){
				l++;
				_sk[0] = argv[l];
				qiC->createtbls(_sk[0]);
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();
		}

		if(ut->matchopts(cs, "cTD")){


			if(hf == 1) {
				hl->getstr("cTD");
				break;
			}
		

			if( nl > 1 ){
			
			l++;
			_sk[0] = argv[l];
			qiD->createtbls(_sk[0]);
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();
		}


		// delete tables
		if(ut->matchopts(cs, "dTC")){


			if(hf == 1) {
				hl->getstr("dTC");
				break;
			}
		

			if( nl > 1 ){
				l++;
				_sk[0] = argv[l];
				qiD->deletetbls(_sk[0]);
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();
		}


		if(ut->matchopts(cs, "dTD")){


			if(hf == 1) {
				hl->getstr("dTD");
				break;
			}
		

			if(nl > 1){
				l++;
				_sk[0] = argv[l];
				qiD->deletetbls(_sk[0]);
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();
		}


		/************
		   DIR 
		************/


		if( ut->matchopts(cs, "drD") or 
		    ut->matchopts(cs, "drLD") ){


			if(hf == 1) {
				hl->getstr("drD");
				break;
			}
		

		       if( nl > 1 ){

			
			l++;
			_sk[0] = argv[l];
			qiD->delentries(_sk[0], "r");

			}else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();
		}


		if( ut->matchopts(cs, "dD") 
		    or ut->matchopts(cs, "dLD") ){


			if(hf == 1) {
				hl->getstr("dD");
				break;
			}
		
		    if( nl > 1 ){

			l++;
			_sk[0] = argv[l];
			qiD->delentries(_sk[0], "L");
		     }
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();
		}

		if( ut->matchopts(cs, "dC") 
		    or ut->matchopts(cs, "dLC") ){


			if(hf == 1) {
				hl->getstr("dC");
				break;
			}
		
		    if( nl > 1 ){

			l++;
			_sk[0] = argv[l];
			qiC->delentries(_sk[0], "L");
		    }
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();
		}


		if( ut->matchopts(cs, "drC") ){
		    if( nl > 1 ){

			if(hf == 1) {
				hl->getstr("drC");
				break;
			}
		

			l++;
			_sk[0] = argv[l];
			qiC->delentries(_sk[0], "r");
		    }
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}

		    cs.clear();
		}



		if( ut->matchopts(cs, "drD")) {

			if(hf == 1) {
				hl->getstr("drD");
				break;
			}
		

			if( nl > 1 ){
			
			l++;
			_sk[0] = argv[l];
			qiD->delentries(_sk[0], "r");
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}

			cs.clear();
		}



		if( ut->matchopts(cs, "iD")){


			if(hf == 1) {
				hl->getstr("iD");
				break;
			}
		
			if( nl > 1 ){

			l++;	
			_sk[0] = argv[l];
			qiD->setdata(_sk[0]);
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}

			cs.clear();
		}


		if( ut->matchopts(cs, "mLD") 
		    ){

			if(hf == 1) {
				hl->getstr("mLD");
				break;
			}
		

			if( nl > 1 ){
				l++;
				_sk[0] = argv[l];
				VS_t _vs;
				qiD->splitstr(_sk[0],_vs,',');
				qiD->br = true;
				for(auto e: _vs){
					qiD->modifylabel(e,"L");
				}//c:loop
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();

		}


		if( ut->matchopts(cs, "mrLD") 
		    ){


			if(hf == 1) {
				hl->getstr("mrLD");
				break;
			}
		
			if( nl > 1 ){
				l++;
				_sk[0] = argv[l];
				VS_t _vs;
				qiD->splitstr(_sk[0],_vs,',');
				qiD->br = true;
				for(auto e: _vs){
					qiD->modifylabel(e,"r");
				}//c:loop
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();

		}


		if( ut->matchopts(cs, "mVD") 
		    ){

			if(hf == 1) {
				hl->getstr("mVD");
				break;
			}
		

			if( nl > 1 ){
				l++;
				_sk[0] = argv[l];
				qiD->modifyvalue(_sk[0],"L");
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();
		}


		if( ut->matchopts(cs, "mVC") 
		    ){

			if(hf == 1) {
				hl->getstr("mVC");
				break;
			}
		

			if( nl > 1 ){
				l++;
				_sk[0] = argv[l];
				qiC->modifyvalue(_sk[0],"L");
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();
		}



		if( ut->matchopts(cs, "mVrD") 
		    ){

			if(hf == 1) {
				hl->getstr("mVrD");
				break;
			}
		

			if( nl > 1 ){
				l++;
				_sk[0] = argv[l];
				qiD->modifyvalue(_sk[0],"r");
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}
			cs.clear();
		}

		


		// check access for all directories
		if( ut->matchopts(cs, "cDA") ){


			if(hf == 1) {
				hl->getstr("cDA");
				break;
			}
		

			_sk[0] = "all";
			qiD->checkaccess(_sk[0],"all");
			cs.clear();

		}

		// check access for specific directories
		if( ut->matchopts(cs,"cDL") or
		    ut->matchopts(cs,"cD")
		  ){


			if(hf == 1) {
				hl->getstr("cD");
				break;
			}
		

			if(nl > 1){
				l++;
				_sk[0] = argv[l];
				qiD->checkaccess(_sk[0],"L");
				cs.clear();
			}//c:condn
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}//c:condn

		}//c:condn


		// search: L
		if( ut->matchopts(cs, "sDrL") ){

			if(hf == 1) {
				hl->getstr("sDrL");
				break;
			}
		

			if(nl > 1){
			
				l++;
				_sk[0] = argv[l];
				for(auto _tbl : vstbl["D"]){

					fmt::print("\n");
					fmt::print("Table: \e[1m{}\e[0m\n", _tbl);
					fmt::print("------\n");
					qsD->tblname = _tbl;
					qsD->search(_sk[0], "r+L");
				}

			}//c:condn
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}//c:condn
			cs.clear();

		}


		// search: L
		if( ut->matchopts(cs, "sDrV") ){

			if(hf == 1) {
				hl->getstr("sDrV");
				break;
			}
		

			if(nl > 1){
			
				l++;
				_sk[0] = argv[l];
				//VS_t _vs;
				//ut->splitstr(_sk[0],_vs,',');
				for(auto _tbl : vstbl["D"]){

					fmt::print("\n");
					fmt::print("Table: \e[1m{}\e[0m\n", _tbl);
					fmt::print("------\n");
					qsD->tblname = _tbl;
					//for(auto _l : _vs) qD->search(_l, "L");
					qsD->search(_sk[0], "r+V");
				}

			}//c:condn
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}//c:condn
			cs.clear();
		}



		// search: L
		if( ut->matchopts(cs, "sDL") ){


			if(hf == 1) {
				hl->getstr("sDL");
				break;
			}
		
			if(nl > 1){
			
				l++;
				_sk[0] = argv[l];
				//VS_t _vs;
				//ut->splitstr(_sk[0],_vs,',');
				for(auto _tbl : vstbl["D"]){

					fmt::print("\n");
					fmt::print("Table: \e[1m{}\e[0m\n", _tbl);
					fmt::print("------\n");
					qsD->tblname = _tbl;
					//for(auto _l : _vs) qD->search(_l, "L");
					qsD->search(_sk[0], "L");
				}

			}//c:condn
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}//c:condn
			cs.clear();

		}


		// search: L
		if( ut->matchopts(cs, "sDV") ){


			if(hf == 1) {
				hl->getstr("sDV");
				break;
			}
		
			if(nl > 1){
			
				l++;
				_sk[0] = argv[l];
				//VS_t _vs;
				//ut->splitstr(_sk[0],_vs,',');
				for(auto _tbl : vstbl["D"]){

					fmt::print("\n");
					fmt::print("Table: \e[1m{}\e[0m\n", _tbl);
					fmt::print("------\n");
					qsD->tblname = _tbl;
					qsD->search(_sk[0], "V");
				}

			}//c:condn
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}//c:condn
			cs.clear();

		}


		// search: L
		if( ut->matchopts(cs, "sD") ){


			if(hf == 1) {
				hl->getstr("sD");
				break;
			}
		
			if(nl > 1){
			
				l++;
				_sk[0] = argv[l];
				for(auto _tbl : vstbl["D"]){

					fmt::print("\n");
					fmt::print("Table: \e[1m{}\e[0m\n", _tbl);
					fmt::print("------\n");
					qsD->tblname = _tbl;
					qsD->search(_sk[0], "all");
				}

			}//c:condn
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}//c:condn
			cs.clear();

		}



		// search: L
		if( ut->matchopts(cs, "sDr") ){


			if(hf == 1) {
				hl->getstr("sDr");
				break;
			}
		

			if(nl > 1){
			
				l++;
				_sk[0] = argv[l];
				//VS_t _vs;
				//ut->splitstr(_sk[0],_vs,',');
				for(auto _tbl : vstbl["D"]){

					fmt::print("\n");
					fmt::print("Table: \e[1m{}\e[0m\n", _tbl);
					fmt::print("------\n");
					qsD->tblname = _tbl;
					//for(auto _l : _vs) qD->search(_l, "L");
					qsD->search(_sk[0], "r+all");
				}

			}//c:condn
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}//c:condn
			cs.clear();

		}


		// search: V
		if( ut->matchopts(cs, "sDV") ){


			if(hf == 1) {
				hl->getstr("sDV");
				break;
			}
		
			if (nl > 1){

			l++;
			_sk[0] = argv[l];

			for(auto _tbl : vstbl["D"]){

				fmt::print("-------------------\n");
				fmt::print("Data from the table: {}\n", _tbl);
				fmt::print("-------------------\n");
				qsD->tblname = _tbl;
				qsD->search(_sk[0], "V");
			}
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			}//c:condn
			cs.clear();

		}


		// list all from search as well
		if( ut->matchopts(cs, "lDA+s") ){


			if(hf == 1) {
				hl->getstr("lDA+s");
				break;
			}
		
			_sk[0] = "";

			for(auto _tbl : vstbl["D"]){

				fmt::print("-------------------\n");
				fmt::print("Data from the table: {}\n", _tbl);
				fmt::print("-------------------\n");
				qsD->tblname = _tbl;
				qsD->listlabels(_sk[0],"all");
			}
			cs.clear();

		}


		// list all from search as well
		if( ut->matchopts(cs, "lCA+s") ){


			if(hf == 1) {
				hl->getstr("lCA+s");
				break;
			}
		
			
			_sk[0] = "";

			for(auto _tbl : vstbl["C"]){

				fmt::print("-------------------\n");
				fmt::print("Data from the table: {}\n", _tbl);
				fmt::print("-------------------\n");
				qsC->tblname = _tbl;
				qsC->getall();
			}
			cs.clear();

		}





		/************
		   CMD 
		************/

		if( ut->matchopts(cs, "lCA") or
		    ut->matchopts(cs, "lCrA")
		){


			if(hf == 1) {
				hl->getstr("lCA");
				break;
			}
		
			qiC->getall();
			cs.clear();
		}


		if( ut->matchopts(cs, "lCE") ){


			if(hf == 1) {
				hl->getstr("lCE");
				break;
			}
		
		    if( nl > 1 ){
			
			l++;
			_sk[0] = argv[l];
			qiC->getexpl(_sk[0],"L");
		    }
		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
		    }//c:condn
			cs.clear();
		}


		if( ut->matchopts(cs, "iCf") )
		{

			if(hf == 1) {
				hl->getstr("iCf");
				break;
			}
		
			if( nl > 1 ){

				l++;
				_sk[0] = argv[l];
				qiC->insfromfile(_sk[0]);
			}

		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
		    }//c:condn
		    cs.clear();

		}


		if( ut->matchopts(cs, "iDf") ){


			if(hf == 1) {
				hl->getstr("iDf");
				break;
			}
		
			
			if( nl > 1 ){

			l++;
			_sk[0] = argv[l];
			qiD->insfromfile(_sk[0],"insert");
			}
		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
		    }//c:condn

			cs.clear();

		}


		if( ut->matchopts(cs, "dDf")){


			if(hf == 1) {
				hl->getstr("dDf");
				break;
			}
		
			
			if( nl > 1 ){

			l++;
			_sk[0] = argv[l];
			qiD->deletefromfile(_sk[0],"L");
			}
		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
		    }//c:condn
			cs.clear();

		}		


		if( ut->matchopts(cs, "dCf") ){


			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
		
		    if( nl > 1 ){
			
			l++;
			_sk[0] = argv[l];
			qiC->deletefromfile(_sk[0],"L");

		    }
		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
		    }//c:condn
			cs.clear();

		}		


		if( ut->matchopts(cs, "mCf") ){


			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
		
		    if( nl > 1 ){
			
			l++;
			_sk[0] = argv[l];
			qiC->insfromfile(_sk[0],"m+L");
		    }
		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
		    }//c:condn
			cs.clear();

		}


		if( ut->matchopts(cs, "mDf") ){


			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
		
		    if( nl > 1 ){
			
			l++;
			_sk[0] = argv[l];
			qiD->insfromfile(_sk[0],"update");
		    }
		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
		    }//c:condn
			cs.clear();
		}

		


		if( ut->matchopts(cs, "wACf") ){


			if(hf == 1) {
				hl->getstr("wACf");
				break;
			}
		
		    if( nl > 1 ){

			l++;
			_sk[0] = argv[l];
			qiC->writeToFile(_sk[0],"all");
		    }
		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
		    }//c:condn
			cs.clear();
		}


		if( ut->matchopts(cs, "wCf") or
		    ut->matchopts(cs, "wCLf") ){


			if(hf == 1) {
				hl->getstr("wCf");
				break;
			}
		

		    if( nl > 2 ){

			l++;	
			_sk[0] = argv[l];

			l++;
			_sk[1] = argv[l];

			_sk[2] = "L";

			qiC->writeToFile(_sk[0],_sk[2],_sk[1]);
		    }
		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",2);
			hl->getstr("wCf");
		    }//c:condn
			cs.clear();
		}


		if( ut->matchopts(cs, "wDAf") ){

			if(hf == 1) {
				hl->getstr("wDAf");
				break;
			}
		

		    if( nl > 1 ){
			l++;	
			_sk[0] = argv[l];

			_sk[1] = "";

			qiD->writeToFile(_sk[0],_sk[1],"all");
		    }
		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			hl->getstr("wDAf");
		    }//c:condn
		    cs.clear();
		}


		if( ut->matchopts(cs, "wDf") ){

			if(hf == 1) {
				hl->getstr("wDf");
				break;
			}
		

		    if( nl > 2 ){
			l++;	
			_sk[0] = argv[l];

			l++;	
			_sk[1] = argv[l];

			qiD->writeToFile(_sk[0],_sk[1],"L");
		    }
		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
			hl->getstr("wDf");
		    }//c:condn
		    cs.clear();
		}



		if( ut->matchopts(cs, "dLC") ){


			if(hf == 1) {
				hl->getstr("dLC");
				break;
			}
		

			if( nl > 1 ){
				l++;	
				_sk[0] = argv[l];
				qiC->delentries(_sk[0], "L");
			}
			else {
				fmt::print("  \e[1m[{}] argument required\e[0m\n",2);
			}
			cs.clear();
		}


		if( ut->matchopts(cs, "lC") or
		    ut->matchopts(cs, "lCV")){

			if(hf == 1) {
				hl->getstr("lC");
				break;
			}
		
			if( nl > 1 ){
				l++;
				_sk[0] = argv[l];
				qiC->getV(_sk[0], "V");
			}
			else {
				fmt::print("  \e[1m[{}] argument required\e[0m\n",2);
			}
			cs.clear();
		}


		if( ut->matchopts(cs, "lrC") or
		    ut->matchopts(cs, "lrCV")){


			if(hf == 1) {
				hl->getstr("lrCV");
				break;
			}
		
			if( nl > 1 ){
				l++;	
				_sk[0] = argv[l];
				qiC->getV(_sk[0], "r");
			}
			else {
				fmt::print("  \e[1m[{}] argument required\e[0m\n",2);
				hl->getstr("lrCV");
			}
			cs.clear();
		}
		


		//[X]:DOESNT WORK, copied
		if( ut->matchopts(cs, "mCL") or
		    ut->matchopts(cs, "mC") 
		  ){


			if(hf == 1) {
				hl->getstr("mC");
				break;
			}
		
		    if( nl > 1 ){

			l++;
			_sk[0] = argv[l];
			VS_t _vs;
			qiC->splitstr(_sk[0],_vs,',');
			qiC->br = true;
			for(auto e: _vs){
				qiC->modifylabel(e,"L");
			}//c:loop
		     }else {
				fmt::print("  \e[1m[{}] argument required\e[0m\n",1);
		     }
		     cs.clear();

		}


		// search: L
		if( ut->matchopts(cs, "sCL") 
		  ){


			if(hf == 1) {
				hl->getstr("sCL");
				break;
			}
		
		     if( nl > 1 ){

			l++;	
			_sk[0] = argv[l];
			for(auto _tbl : vstbl["C"]){

				fmt::print("-------------------\n");
				fmt::print("Data from the table: {}\n", _tbl);
				fmt::print("-------------------\n");
				qsC->tblname = _tbl;
				qsC->search(_sk[0], "L");
			}
		     }
		     else {
				fmt::print("  \e[1m[{}] argument required\e[0m\n",1);
				hl->getstr("sCL");
		     }

			cs.clear();
		}

		// search: V
		if( ut->matchopts(cs, "sCV") 
		  ){


			if(hf == 1) {
				hl->getstr("sCV");
				break;
			}
		
		    if( nl > 1 ){

		 	l++;	
			_sk[0] = argv[l];

			for(auto _tbl : vstbl["C"]){

				fmt::print("-------------------\n");
				fmt::print("Data from the table: {}\n", _tbl);
				fmt::print("-------------------\n");

				qsC->tblname = _tbl;
				qsC->search(_sk[0], "V");
			}
		        }else {
				fmt::print("  \e[1m[{}] argument required\e[0m\n",1);
				hl->getstr("sCV");
		        }

			cs.clear();
		}


		// search: V
		if( ut->matchopts(cs, "sCE") 
		  ){

			if(hf == 1) {
				hl->getstr("sCE");
				break;
			}
		
			if(nl > 1){

				l++;	
				_sk[0] = argv[l];

				for(auto _tbl : vstbl["C"]){

					fmt::print("-------------------\n");
					fmt::print("Data from the table: {}\n", _tbl);
					fmt::print("-------------------\n");

					qsC->tblname = _tbl;
					qsC->search(_sk[0], "E");
				}
			}
		        else {
				fmt::print("  \e[1m[{}] argument required\e[0m\n",1);
				hl->getstr("sCE");
		        }

			cs.clear();
		}


		// search: V
		if( ut->matchopts(cs, "sC") or
		    ut->matchopts(cs, "sCA")
		    ){


			if(hf == 1) {
				hl->getstr("sC");
				break;
			}
		
			if(nl > 1){
				l++;	
				_sk[0] = argv[l];

				for(auto _tbl : vstbl["C"]){

					fmt::print("-------------------\n");
					fmt::print("Data from the table: {}\n", _tbl);
					fmt::print("-------------------\n");

					qsC->tblname = _tbl;
					qsC->search(_sk[0], "all");
				}
			}
			else{
				fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
				hl->getstr("sC");
			}
			cs.clear();
		}



		// via a:b format
		if( ut->matchopts(cs, "iC") 
		  ){


			if(hf == 1) {
				hl->getstr("iC");
				break;
			}
		
		    if( nl > 1 ){

			l++;
			_sk[0] = argv[l];
			qiC->insertdata(_sk[0]);
		     }
		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
		    }
			cs.clear();
		}



		// via a:b format
		if( ut->matchopts(cs, "eCL") 
		    ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
		

		    if(nl > 2){

			l++;
			_sk[0] = argv[l];

			l++;
			_sk[1] = argv[l];

			qiC->editdata(_sk[0],_sk[1],"L");
		    }
		    cs.clear();
		}


		// via a:b format
		if( ut->matchopts(cs, "eDV") 
		    ){


			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
		

		    if(nl > 2){

			l++;
			_sk[0] = argv[l];

			l++;
			_sk[1] = argv[l];

			qiD->editdata(_sk[0],_sk[1],"V");
		    }

		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
		    }
		    cs.clear();
		}



		// via a:b format
		if( ut->matchopts(cs, "eDL") ){

			if(hf == 1) {
				hl->getstr(opt);
				break;
			}
		
		    if(nl > 2){

			l++;
			_sk[0] = argv[l];

			l++;
			_sk[1] = argv[l];

			qiD->editdata(_sk[0],_sk[1],"L");
		   }

		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
		    }
		   cs.clear();
		}





		// via a:b format
		if( ut->matchopts(cs, "mrCV") or
		    ut->matchopts(cs, "mrC") 
		  ){
		    if( nl > 1 ){

			l++;
			_sk[0] = argv[l];
			qiC->setrLV(_sk[0]);
			cs.clear();
		    }
		    else{
			fmt::print("\e[1mNOTE: [{}] argument required\e[0m\n",1);
		    }
		}

	

		_sk[0].clear(); 
		_sk[1].clear(); 
		_sk[2].clear(); 

	}//c:loop

	delete ut,hl,qiC,qsC,qiD,qsD;

	return 0;
}//c:main
