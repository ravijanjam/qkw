#ifndef CMD_H
#define CMD_H

#pragma once

#include "default.h"
#include "app.h"
#include "qkw.h"

using namespace std;


class cmd : public qkw{

        public:
		cmd(string&);
		~cmd();


		static int fn(void *data, int argc, char **argv, char **azColName);

		void getAlltblcontent(string&);
		void createtbls(string&);
		void search(string&, string);
		void getall();
		int getexpl(string&, string sd="all"); 
		void setexpl(string&);
		void insfromfile(string&,string opt="L");
		void deletefromfile(string&,string opt="L");
		int writeToFile(string&,string opt="all",string dt="");
		void copytbl(string&, string&);
		void modifydata(string&);
		int getLV(string&,string);
		void setrLV(string&);
		void getrLV(string&,string);
		void setLE(string&);
		void getrLE(string&,string);
		int getV(string&,string);
		void getrV(string&,string);
		void getlabel(string &sl, string opt);
		void gettemplate(string &fN);

		MSS_t mqc = {

			{"Q1","CREATE TABLE IF NOT EXISTS {}(L VARCHAR NOT NULL, V BLOB, E VARCHAR, UNIQUE(L))"},
			{"Q2.0","INSERT INTO {} ({}) VALUES (\"{}\")"},
			{"Q2.1","INSERT INTO {} ({}) VALUES ({})"},
			{"Q3","INSERT INTO {} (L,V,E) VALUES (\"{}\", \"{}\", \"{}\")"},
			{"Q4","INSERT INTO {} ({}) VALUES('{}','{}','\"\"')"},
			{"Q5","SELECT * FROM {} WHERE {} in ({})"},
			{"Q5.1","SELECT * FROM {} WHERE {} in ({})"},
			{"Q6","UPDATE {0} SET {1}='{2}' WHERE {3}='{4}'"},
			{"Q6.1","UPDATE {0} SET {1}=\"{2}\" WHERE {3}='{4}'"},
			{"Q7","SELECT count(*) as CC FROM {} WHERE L in ('{}')"},
			{"Q8","INSERT INTO {} ({}) VALUES('{}')"},
			{"Q9","INSERT INTO {} (L,V) VALUES('{}','{}')"},
			{"Q10","INSERT INTO {} (L,V,E) SELECT * FROM {}"},
			{"Q11","DELETE FROM {} WHERE L in ('{}')"},

		};


};


#endif
