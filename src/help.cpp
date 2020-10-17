#include "help.h"

void help::getstr(string opt){

	csv = "{0},{0}...,{0}";
	
	cs.merge(splitstr2set(opt));

	if( matchopts(cs,"lTA")
	  ){
		sc = fmt::format("qkw -{0}\n", opt, sc);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}


	if( matchopts(cs,"dTC") or 
	    matchopts(cs,"dTD") or
	    matchopts(cs,"cTC") or
	    matchopts(cs,"cTD") or
	    matchopts(cs,"tC") or
	    matchopts(cs,"tD") 
	  ){
		sc = fmt::format(csv,"T");
		sc = fmt::format("qkw -{0} <{1}>\n", opt, sc);
		sc = fmt::format("{}  T:<table_name>\n",sc);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}

	if(matchopts(cs, "grC") or
	   matchopts(cs, "grD")
	  ){
		sc = fmt::format("qkw -{0} <rowid>\n", opt);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}//c:condn


	if(matchopts(cs, "sCL") or
	   matchopts(cs, "sDL") or
	   matchopts(cs, "sCV") or
	   matchopts(cs, "sDV") or
	   matchopts(cs, "sCE") or
	   matchopts(cs, "sDE") or
	   matchopts(cs, "sC") or
	   matchopts(cs, "sD") or
	   matchopts(cs, "sCA") or
	   matchopts(cs, "sDA") 
	  ){
		sc = fmt::format("qkw -{0} <regex>\n", opt);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}//c:condn
	
	

	if(matchopts(cs, "gC") or
	   matchopts(cs, "gD")
	  ){
		sc = fmt::format("qkw -{0} <label>\n", opt);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}//c:condn
	

	if(matchopts(cs, "iC") or
	   matchopts(cs, "iD") 
	  ){
		sc = fmt::format("qkw -{0} <label>:\"<value>\"\n", opt);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}//c:condn
	

	if(matchopts(cs, "mLC")){

		sc = fmt::format("<i{0}:f{0}>","L");
		sc = fmt::format(csv,sc);
		sc = fmt::format("qkw -{0} {1}\n", opt, sc);
		sc = fmt::format("{}  iL: initial label, fL: final label\n",sc);
		sc = fmt::format("\e[1m{}\e[0m",sc);
		
	}//c:condn


	if( matchopts(cs, "wrfC") or 
	    matchopts(cs, "wrfD") 
	  ){
	  	sc = fmt::format(csv,"r");
		sc = fmt::format("qkw -{0} {1}\n", opt, sc);
		sc = fmt::format("{}  r:<rowid>\n", sc);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}



	// no options required
	if( matchopts(cs, "lCA") or 
	    matchopts(cs, "lDA") or
	    matchopts(cs, "lDA+s") or
	    matchopts(cs, "lCA+s")
	  ){
		sc = fmt::format("qkw -{0}\n", opt, sc);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}


	if( matchopts(cs, "lC") or 
	    matchopts(cs, "lD") or
	    matchopts(cs, "mLD") or
	    matchopts(cs, "mLC") or
	    matchopts(cs, "mVC") or
	    matchopts(cs, "mVD") or
	    matchopts(cs, "lLC") or
	    matchopts(cs, "lLD") or
	    matchopts(cs, "dC") or
	    matchopts(cs, "dD") or
	    matchopts(cs, "dLC") or
	    matchopts(cs, "dLD") 
	  ){
	  	sc = fmt::format(csv,"L");
		sc = fmt::format("qkw -{0} <{1}>\n", opt, sc);
		sc = fmt::format("{}  L:<label>\n", sc);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}



	if( matchopts(cs, "wfC") or 
	    matchopts(cs, "wfD") or
	    matchopts(cs, "wLfC") or
	    matchopts(cs, "wLfD") 
	  ){
	  	sc = fmt::format(csv,"L");
		sc = fmt::format("qkw -{0} <filename> <{1}>\n", opt, sc);
		sc = fmt::format("{}  L:<label>\n", sc);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}


	if( matchopts(cs, "wAfC") or 
	    matchopts(cs, "wAfD") 
	  ){
		sc = fmt::format("qkw -{0} <filename>\n", opt);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}


	if( matchopts(cs, "mfC") or 
	    matchopts(cs, "mfD") or 
	    matchopts(cs, "ifC") or 
	    matchopts(cs, "ifD") or 
	    matchopts(cs, "dfC") or 
	    matchopts(cs, "dfD") 
	  ){
		sc = fmt::format("qkw -{0} <inputfile>\n", opt);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}


	if(opt == "exec"){
		sc = fmt::format("qkw -{0} <commandstring_in_quotes>\n", opt);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}



	if(opt == "gettemplate"){
		sc = fmt::format("qkw -{0} <outputfilename>\n", opt);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}


	if(opt == "tbl"){
		sc = fmt::format("qkw -{0} <table_name>\n", opt);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}

	if(opt == "dbname"){
		sc = fmt::format("qkw -{0}\n", opt);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}

	if( opt == "cpyTC" or 
	    opt == "cpyTD" ){
		sc = fmt::format(csv,"T");
		sc = fmt::format("qkw -{0} <{1}>\n", opt, sc);
		sc = fmt::format("{}  T:<table_name>\n",sc);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}

	if( opt == "mergetbls" ){
		sc = fmt::format(csv,"iT");
		sc = fmt::format("qkw -{0} <{1}> <{2}f>\n", opt, sc, "T");
		sc = fmt::format("{}  iT:initial <table_name>  fT:final <table_name>  \n",sc);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}


	if( opt == "cleartbls" ){
		sc = fmt::format(csv,"T");
		sc = fmt::format("qkw -{0} <{1}>\n", opt, sc);
		sc = fmt::format("{}  T:<table_name>\n",sc);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}


	if( opt == "addpath" ){
		sc = fmt::format("qkw -{0} <label>\n", opt);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}


	if( opt == "setcfg" ){
		sc = fmt::format("qkw -{0} <cfgfile>\n", opt);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}


	if( opt == "lappend+r" ){
		sc = fmt::format("qkw -{0} <regex> <replacement>\n", opt);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}
	

	if( opt == "tbltype" ){
		sc = fmt::format(csv,"T");
		sc = fmt::format("qkw -{0} <{1}>\n", opt, sc);
		sc = fmt::format("{}  T:<table_name>\n",sc);
		sc = fmt::format("\e[1m{}\e[0m",sc);
	}

	fmt::print(sc);
	
}//c:func



