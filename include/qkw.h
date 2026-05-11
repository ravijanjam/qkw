#ifndef QKW_H
#define QKW_H

#pragma once

#include "default.h"
#include "app.h"
#include "ktypes.h"
#include "utils.h"

using namespace std;


class qkw : public utils{

        public:
		qkw(string&);
		~qkw();
		sqlite3 *sdb;

		void query(string&);
		void movetable(string&, string&); 
		bool ltrm(string &ss, string &ms);
		bool rtrm(string &ss, string &ms);
		int initdb(char*,int);
		int getextcfgdata();
		void tblcolcount(string&);
		void copytbl(string&, string&);
		void createtbls(string&); 
		int renametbl(string&, string&);
		void deletetbls(string&);
		void listtbls(string);
		void listtbls_v1(string,string);
		void search(string&,string); 
		void gettbltype(string&); 
		void insertvalue(); 
		void getmatch();
		void insfrmfile(string&);
		int insertpath(string&);
		void modifyvalue(string&,string);
		void chginstbl(string&);
		void getAlltblcontent(string&);
		void listtblsbytype();
		void getlabel(string&,string);
		void gettblcontent(string&, string&); 
		void listlabels(string&,string);
		void modifylabel(string&,string);
		void cleartbls(string&);
		void delentries(string&,string type = "L");
		int insertdata(string&); 
		int editdata(string&,string&,string);
		void insertdatafrmfile(string&);
		void mergetbls(string&,string&);
		int getschema(string &tbl);
		int objcount=0;


		static int fn(void *data, int argc, char **argv, char **azColName);
		MSS_t mq ={
			{"Q1","SELECT * FROM {}"},
			{"Q2","SELECT * FROM {} WHERE {}"},
			{"Q3","SELECT name FROM sqlite_master WHERE type='table' ORDER BY NAME"},
			{"Q4","DROP TABLE IF EXISTS {}"},
			{"Q5","CREATE TABLE IF NOT EXISTS {}(L varchar UNIQUE NOT NULL, V varchar)"},
			{"Q5.1","CREATE TABLE IF NOT EXISTS {}{}"},
			{"Q6","DROP TABLE {}"},
			{"Q7","INSERT INTO {} ({}) VALUES({})"},
			{"Q8.0","DELETE FROM {}"},
			{"Q8","DELETE FROM {} WHERE {} IN ({})"},
			{"Q9","UPDATE {} SET L='{}' WHERE L='{}'"},
			{"Q9.1","UPDATE {} SET L='{}' WHERE rowid='{}'"},
			{"Q9.2","UPDATE {} SET V='{}' WHERE L='{}'"},
			{"Q9.3","UPDATE {} SET V='{}' WHERE rowid='{}'"},
			{"Q10","SELECT sql from sqlite_master WHERE NAME = {}"},
			{"Q11","ALTER TABLE {} RENAME TO {}"},
			{"Q12","SELECT name FROM sqlite_master WHERE type=\'table\' AND name=\'{}\'"},
			{"Q13","INSERT INTO {} SELECT * FROM {}"},
			{"Q14","SELECT rowid, * FROM {}"},
			{"Q15","SELECT L,V FROM {} WHERE {} IN ({})"},
			{"Q16","SELECT {} FROM {} WHERE {} NOT IN ({})"},
			{"Q17","SELECT rowid, L,V FROM {} WHERE {} IN ({})"},
			{"Q18","SELECT count(*) FROM {} WHERE L IN ('{}')"},
			{"Q19","SELECT L,V FROM {} WHERE L IN ({})"},
			{"Q20","SELECT L,V FROM {} WHERE rowid IN ({})"},
			{"Q21","SELECT {0}, count({0}) as count from {1} where {0} in ('{2}')"}, 
			{"Q22","SELECT rowid, * FROM {} WHERE rowid in ({})"},
			{"Q23","SELECT V FROM {} WHERE {} = '{}'"},
			{"Q24","UPDATE {0} SET {1} = rxset(\"{2}\",'{3}',{1})"},
			{"Q25","UPDATE {0} SET {1} = rxset(\"{2}\",'{3}',{1}) WHERE {1} IN ({4})"},
			{"Q26","SELECT name,sql FROM sqlite_master where type = 'table' and name in ({})"},
			{"Q26.1","SELECT sql FROM sqlite_master where name in ('{}')"},
			{"Q27","INSERT INTO {} {} SELECT * FROM (SELECT * FROM {} UNION SELECT * FROM {})"},
			{"Q28","SELECT name FROM PRAGMA_TABLE_INFO('{}')"},
			{"Q29","SELECT rowid,L FROM {} order by rowid"},
		};



		void proc(string&);
		void cproc(string &st, int fn(void*, int, char**, char**));

		static void rxset(sqlite3_context *sqc, int argc, sqlite3_value **sqv);

		struct SR{
			string s;
			VS_t vs;
			int c;
		} *sr;

		struct SD{
			int n, ri, cc=0;
			int rS;
			VS_t vs;
			fstream fs;
			regex rgx;
			smatch sm;
			string scol, ss;
			MSS_t ms;
			bool b = true;
			string null2str(char *s){
				
				if(s == NULL){
					return "";
				}
				return (string)s;

			}
			qkw *cq;
		} *sd;

		char *zErrMsg;
		string tblname, tbltyp, Ctbl, Dtbl;
		char *dbn;
		string dbname;
		bool br = false;
		static void sqlite3_ltrm(sqlite3_context*,int,sqlite3_value**);
		static void sqlite3_rtrm(sqlite3_context*,int,sqlite3_value**);
		VS_t vtbls;
		string qS;


        private:
            VS_t _vsl;
};


#endif
