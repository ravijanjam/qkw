#ifndef UTILS_H
#define UTILS_H

#pragma once

#include "default.h"
#include "app.h"
#include "ktypes.h"

using namespace std;

class utils{

	public:

		utils();

		int optstr(string&);
		void suboptsplit(string&);
		string normalizegaps(string &s, int d, string _ts="");
		bool matchopts(CS_t&,string);
		void fileexists(string&);
		bool charcheck(string,string);
		string tbltype(string&);
		bool checkformat(string);
		int parsesqlstmt(string&);
		bool islineempty(string&);
		bool tagmatch(string&);
		bool rmtrailnewline(string&);
		VMSS_t fileparser(string&,string opt="label");
		VMSS_t vfd;
		void addquotes(VS_t&);
		void vstr2csv(VS_t&,string&);
		bool emptystr(string);
		bool cstr2qstr(string&);
		void stdinstr();
		static void h(int);
		int g(int);
	    	CS_t splitstr2set(const string);
	    	bool splitstr(string&, VS_t&,char);
	    	string rmspaces(string&);
		bool splitatcolon(string&,smatch&);
		string nullstr2empty(char*);
		bool checkinlist(VS_t&, string&);
		void print_constrain(string&,int size=100);
		void print_format(string&,int);
		int cfgchk(); 
		int cfgdata(YN_t&);
		int cfggetdata(string&);
		bool charchk(string&);
		void cfgmodify(string&,string&);
		const char *cfgfile=NULL, *envtag = "QKW_CONFIG";
		YN_t yf;
		CS_t cs;
		
		string str;
};


#endif
