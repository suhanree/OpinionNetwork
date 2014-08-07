// 
// 	Filename : InputParam.C 
//
//	Author : Suhan Ree
//	Date   : 08-26-2003


#include "InputParam.h"
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib>

#ifndef MAX_CHARS
#define MAX_CHARS 1000
#endif
#ifndef SUCCESS
#define SUCCESS true
#endif
#ifndef NO_KEY
#define NO_KEY false
#endif

using namespace std;


// Read the input file and save the info in the map.
void InputParam::read() {
	char tmpstr[MAX_CHARS+1];
	string key, value;

	do {
		if(ifile.peek()!='#' && ifile >> key >> value)
			key_val[key] = value;
	} while (ifile.getline(tmpstr, MAX_CHARS, '\n'));
};

// Print key-value pairs read.
void InputParam::print_key_val() {
	for(map<string,string>::const_iterator i=key_val.begin();\
		i!=key_val.end();i++)
		cout << i->first << '\t' << i->second << endl;
};
     
// Return the value of a key in the second argument
bool InputParam::get(const string str, string & str1, ostream &ofile) {
	if(key_val.find(str)!=key_val.end()) {
		str1 = key_val[str];
		return SUCCESS;
	};
	ofile << "# Parameter not found: " << str;
	return NO_KEY;
};

bool InputParam::get(const string str, bool & tf, ostream &ofile) {
	if(key_val.find(str)!=key_val.end()) {
		char c=*(key_val[str].c_str());
		if (c=='t' || c=='T' || (c>='1' && c<='9')) {
			tf=true;
			return SUCCESS;
		}
		else if (c=='f' || c=='F' || c=='0') {
			tf=false;
			return SUCCESS;
		}
		else {
			ofile << "# Paramter, " << str;
			ofile << ", has invalid value.";
			return NO_KEY;
		};
	};
	//ofile << "# Parameter not found: " << str;
	return NO_KEY;
};

bool InputParam::get(const string str, short & num, ostream &ofile) {
	if(key_val.find(str)!=key_val.end()) {
		num = atoi(key_val[str].c_str());
		return SUCCESS;
	};
	//ofile << "# Parameter not found: " << str;
	return NO_KEY;
};

bool InputParam::get(const string str, int & num, ostream &ofile) {
	if(key_val.find(str)!=key_val.end()) {
		num = atoi(key_val[str].c_str());
		return SUCCESS;
	};
	//ofile << "# Parameter not found: " << str;
	return NO_KEY;
};

bool InputParam::get(const string str, long & num, ostream &ofile) {
	if(key_val.find(str)!=key_val.end()) {
		num = atol(key_val[str].c_str());
		return SUCCESS;
	};
	//ofile << "# Parameter not found: " << str;
	return NO_KEY;
};

bool InputParam::get(const string str, unsigned long & num, ostream &ofile) {
	if(key_val.find(str)!=key_val.end()) {
		num = atol(key_val[str].c_str());
		return SUCCESS;
	};
	//ofile << "# Parameter not found: " << str;
	return NO_KEY;
};

bool InputParam::get(const string str, float & num, ostream &ofile) {
	if(key_val.find(str)!=key_val.end()) {
		num = atof(key_val[str].c_str());
		return SUCCESS;
	};
	//ofile << "# Parameter not found: " << str;
	return NO_KEY;
};

bool InputParam::get(const string str, double & num, ostream &ofile) {
	if(key_val.find(str)!=key_val.end()) {
		num = atof(key_val[str].c_str());
		return SUCCESS;
	};
	//ofile << "# Parameter not found: " << str;
	return NO_KEY;
};

