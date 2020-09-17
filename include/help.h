#ifndef HELP_H
#define HELP_H

#include "utils.h"

using namespace std;

class help: public utils{

	public:
		help(){};	
		void getstr(string);
		CS_t cs;
		string sc, csv;
};

#endif
