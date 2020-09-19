#include "utils.h"

utils::utils(){
	this->cfgchk();
}

bool utils::cstr2qstr(string &ss){

	VS_t vs;

	this->splitstr(ss,vs,',');
	this->addquotes(vs);
	this->vstr2csv(vs,ss);

	if (ss.size() > 0) return true;
	return false;

}


bool utils::matchopts(CS_t &cs, string data){

	if (cs == this->splitstr2set(data)) return true;
	return false;
}

void utils::fileexists(string &sf){

	if(access(sf.c_str(), F_OK)!=0){
		fmt::print("\e[31m\e[1m ERROR: \"{}\" not accessible... \n\e[0m", sf);
		exit(EXIT_FAILURE);
	}

}


CS_t utils::splitstr2set(string ss){

	this->cs.clear();
	for(char ch : ss){
		this->cs.insert(ch);
	}

	return this->cs;

}


bool utils::charcheck(string str, string opt){

	if(opt=="L"){
		regex re("[^a-z0-9A-Z.-_#@+]+");
		if(regex_search(str.begin(),str.end(),re)) return true;
	}
	return false;

}


string utils::rmspaces(string &sd){
	regex re("\\s");
	return regex_replace(sd,re,"");
}


VMSS_t utils::fileparser(string &fN, string opt){

		string sd;
	        MSS_t  md;
		fstream nf;

		regex RC("\"");
		string lb="", tp, rs = "";
		nf.open(fN, ios::in);
		if(nf.is_open()){

			while(getline(nf,tp)){


				if(tagmatch(tp)){

				if(tp == opt | tp == "value" | tp == "expl"){

					this->rmtrailnewline(rs);
					if(lb=="value" or lb=="expl") rs = regex_replace(rs,RC,"\\\"\"");
					md[lb] = rs;
					lb = tp;
					rs = "";

				}

				if(tp == "---"){

					this->rmtrailnewline(rs);
					md[lb] = rs;
					lb = tp;

					this->vfd.push_back(md);

					lb = "";
					rs = "";
				}

				continue;
			        }

				rs += tp;
				rs += "\n";

			}
			
		}
		else{
			fmt::print("\e[31m\e[1m ERROR: file can't be opened... \e[0m\n");
		}
		nf.close();

	return this->vfd;


}


bool utils::islineempty(string &sd){

	smatch ms;
	regex re("^\\s{0,}");
	if(regex_match(sd, ms, re)){
		return true;
	}

	return false;

}


bool utils::tagmatch(string &sd){

	smatch ms;
	regex re("(^label:|^value:|^expl:|^---)\\s{0,}");
	if(regex_match(sd, ms, re)){
		regex rs(":|\\s");
		sd = regex_replace(ms.str(0), rs, "");
		return true;
	}

	return false;

}


bool utils::rmtrailnewline(string &sd){

	int n = sd.size()-1, j = n;
	for(int i = j ; i > 0 and j == i ; i--){
		if(sd[i]=='\n') {
			sd.pop_back();
			j--;
		}
	}

	if (n>sd.size()-1) return true;
	else return false;

}


void utils::vstr2csv(VS_t &vs, string &rs){

	rs = "";
	if (vs.size()>1){
	for(int i=0; i < vs.size()-1; i++){
		rs += fmt::format("{},",vs[i]);
	}
	rs += fmt::format("{}",vs[vs.size()-1]);
	}
	else if (vs.size() == 1){
		rs = vs[0];
	}

}

void utils::addquotes(VS_t &vs){

	int i=0; 
	for(auto s : vs){
		s.insert(0,"'");
		s.insert(s.size(),"'");
		vs[i] = s;
		i++;
	}

}

int utils::cfgchk(){

	const char *ifile=0; 
        if(secure_getenv(this->envtag)){

                ifile = secure_getenv(this->envtag);
                try{
                        YAML::LoadFile(ifile);
                }
                catch(...){
                        fmt::print("---------------------------------------------\n");
                        fmt::print("\e[31m\e[1m  ERROR: configuration file can't be read \e[0m\n");
                        fmt::print("---------------------------------------------\n");
			exit(1);
                }
        }
        else{
                fmt::print("-----------------------------------------------------------------\n");
                fmt::print("\e[31m\e[1m  ERROR: \"{}\" environment variable unavailable \e[0m\n", this->envtag);
                fmt::print("-----------------------------------------------------------------\n");
		exit(2);
        }

	this->cfgfile = ifile;

	return 0;

}


int utils::optstr(string &st){

	regex r("-([a-zA-Z0-9+]+)");
	smatch m;
	if(regex_search(st,m,r) == true){
		st = m.str(1);
		return 0;
	}else{
		return 1;
	}

}


int utils::cfgdata(YN_t &yf){

	if(cfgchk() == 0){
		yf = YAML::LoadFile(this->cfgfile);
		return 0;
	}

	return 1;
}


int utils::cfggetdata(string &st){

	VS_t vs; int ec;
	this->splitstr(st,vs,'.');

	YN_t yn;
	ec = this->cfgdata(yn);
	if (ec != 0) return 1;

	if ( vs.size() == 3 ){
		st = yn[vs[0]][vs[1]][vs[2]].as<string>(); 
	}else{
		return 2;
	}


	return 0;
	
}


int utils::parsesqlstmt(string &ss){
	
		int b,e;
		for(int i=0; i < ss.size(); i++){
			if(ss[i] == '(') {
				b = i;
				break;
			}
		}

		for(int i=ss.size(); i >=0 ; i--){
			if(ss[i] == ')') {
				e = i;
				break;
			}
		}

		if( (b > 0 and e > 0 and e > b) ) {
			ss = ss.substr(b,e);
			return 0;
		}
	
	return 1;
}


string utils::tbltype(string &ss){

		int b,e;
		for(int i=0; i < ss.size(); i++){
			if(ss[i] == '(') {
				b = i;
				break;
			}
		}

		for(int i=ss.size(); i >=0 ; i--){
			if(ss[i] == ')') {
				e = i;
				break;
			}
		}

		if(not (b > 0 and e > 0 and e > b) ) return "none";
		ss = ss.substr(b,e);
		ss = regex_replace(ss,regex("VARCHAR|NOT|NULL|CREATE|BLOB|UNIQUE|TABLE|[(),]"),"");
		smatch sm;
		int cc=0;
		if(regex_search(ss,sm,regex("(L)",regex_constants::icase))) cc++;
		if(regex_search(ss,sm,regex("(V)",regex_constants::icase))) cc++;
		if(regex_search(ss,sm,regex("(E)",regex_constants::icase))) cc++;
		if(cc == 3) return "cmd";
		if(cc == 2) return "dir";
		return "none";

}


bool utils::splitatcolon(string &s, smatch &m){

    regex r("(.*):(.*)");

    if (regex_search(s, m, r) == true){
        return true;
    }
        return false;
    
}


bool utils::splitstr(string &ss, VS_t &vs, char delim){

	string RS, rxs, ts, rs = "";
	if (delim == '.') RS = "[,a-zA-Z0-9{}_-]";
	if (delim == ',') RS = "[.a-zA-Z0-9:{}_-]";
	if (delim == ':') RS = "[/,.a-zA-Z0-9{}_-]";
	
	rxs = fmt::format(RS,delim);
	regex r(rxs);
	bool b;

	for(auto c : ss){

		ts = c;
		b = regex_match(ts, r);
		if(b){
			if(c != delim) rs += c;
		}
		else{
			return false;
		}

		if(c == delim){
			if(rs.size()>0)vs.push_back(rs);
			rs = "";
		}
	}
	if(rs.size()>0 and rs != fmt::format("{}",delim))vs.push_back(rs);

	return true;

}


void utils::print_constrain(string &sg, int size){

	cout << "   ";

	for(int i=0, cc=0; i < sg.size(); i++){

                if ( cc%size == 0 ) {cout << "\n  ";}
		if (sg[i] == '\n') { continue; }
                cout << sg[i];
		cc++;

        }
        cout << "\n\n";

}


string utils::nullstr2empty(char *str){

	if(str == NULL) return "";
	return (string)str;
}


void utils::h(int s){
	exit(1);
}


void utils::stdinstr(){

	signal(SIGINT, [](int a){
		exit(1);
	});

	char *c=NULL;
	size_t z;
	str = "";
	while(getline(&c,&z,stdin)){
		str += c;
				
	}
}


void utils::print_format(string &sg, int I){ 

	regex RD("\\\\\""), 
	RN("\n");

        switch(I){

                case 0:
                        sg.insert(0,"\033[4m");
                        sg.insert(sg.size(), "\e[0m");
                        cout << " " << sg << endl;
                break;


                case 1:
		{
                        sg.insert(0, "\e[1m");
                        sg.insert(sg.size(), "\e[0m");
			sg = regex_replace(sg,RD,"\"");
			sg = regex_replace(sg,RN,"\n  ");
                        cout << "  " << sg << "\n";
		}
                break;


                case 2:
		{
			cout << "\n";
			sg = regex_replace(sg,RD,"\"");
			sg = regex_replace(sg,RN,"\n  ");
                        cout << "  " << sg << "\n\n";

		}
		break;
                

                case 3:
		{
			sg = regex_replace(sg,RD,"\"");
			sg = regex_replace(sg,RN,"\n  ");
                        cout << "  " << sg << endl;
		}
                break;



                case 4:
		{
			regex RS("^\\s{0,}");
			sg = regex_replace(sg,RS,"");
			sg = regex_replace(sg,RD,"\"");
			sg = regex_replace(sg,RN,"\n");
                        cout << sg << "\n";
		}
                break;
    

        }
}



bool utils::emptystr(string str){

	regex rx("[\n\t]|\\s{1,}");
	int NS = str.size(), nc=0;;
	string sc;
	for(int i=0; i < NS ; i++){
		sc = str[i];
		if(regex_search(sc, rx)) nc++;
	}
	if ( NS == nc )return true;
	return false;

}



bool utils::checkinlist(VS_t &vs, string &ps){

	for(auto ss : vs){
		if (ss == ps) return true;
	}

	return false;

}

