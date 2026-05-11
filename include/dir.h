#ifndef DIR_H
#define DIR_H

#pragma once

#include "default.h"
#include "app.h"
#include "qkw.h"

using namespace std;


class dir : public qkw{

        public:
		dir(string&);
		~dir();

		static int fn(void *data, int argc, char **argv, char **azColName);

		int addpath(string&);
		void listlabels(string&,string);
		bool getpath(string&);
		int setdata(string&);
		void insfromfile(string&,string);
		int writeToFile(string&,string&,string opt="all");
		void deletefromfile(string &fN, string opt);
		int checkpath(string&);
		int lappend(string&,string&,string);
		int ltrim(string&,string&,string);
		int checkaccess(string&,string);
		void search(string&,string);
		int editdata(string&,string&,string);
		int modifydata(string&,string&,string);
		void editdata(string&,string&,string&,string);

		MSS_t mqd = {
			{"Q1","CREATE TABLE IF NOT EXISTS {}(L varchar UNIQUE NOT NULL, V varchar)"},
			{"Q2","INSERT INTO {} VALUES ('{}', '{}')"},
			{"Q2.1","INSERT INTO {} (L,V) VALUES ('{}', '{}')"},
			{"Q3","SELECT count(*) FROM {} WHERE V in ({})"},
			{"Q4","SELECT count(*) as CC FROM {} WHERE L in ('{}')"},
			{"Q5","SELECT * FROM {} WHERE L in ({})"},
			{"Q6.0","UPDATE {} SET L = '{}', V = '{}'"},
			{"Q6","UPDATE {0} SET {1} = rxset(\"{2}\",'{3}',{1})"},
			{"Q7","UPDATE {0} SET {1} = rxset(\"{2}\",'{3}',{1}) WHERE {1} IN ({4})"},
			{"Q7.1","UPDATE {0} SET {1} = rxset(\"{2}\",'{3}',{1}) WHERE L IN ({4})"},
			{"Q7.2","UPDATE {0} SET {1} = rxset(\"{2}\",'{3}',{1}) WHERE rowid IN ({4})"},
			{"Q8","SELECT * FROM {} WHERE rowid in ({})"},
			{"Q9","SELECT rowid,* FROM {} WHERE L in ({})"},
			{"Q10","SELECT * FROM {} WHERE rowid in ({})"},
			{"Q11","SELECT rowid, * FROM {}"},
			{"Q12","DELETE FROM {} WHERE L IN ('{}')"},
			{"Q13","SELECT rowid,L FROM {}"},
		};


};


#endif
