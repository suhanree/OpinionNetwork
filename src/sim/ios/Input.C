// 
// 	Filename : Input.C 
//
//	Author : Suhan Ree
//	Date   : 08-26-2003


#include "Input.h"
#include "Graph.h"
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <cstdlib>

#define MAX_CHARS 1000

using namespace std;

// Constructors.
Input::Input(const string &file): filename(file) {
	ifile.open(filename.c_str(),ios::in);
	if (!ifile) {
		cerr << "# Error: Input file, " << filename;
		cerr << ", doesn't exist.\n";
		exit(1);
	};
};
Input::Input(const char *file): filename(file) {
	ifile.open(filename.c_str(),ios::in);
	if (!ifile) {
		cerr << "# Error: Input file, " << filename;
		cerr << ", doesn't exist.\n";
		exit(1);
	};
};

// Read the given number of lines and ignore.
bool Input::read_lines(int nlines) {
	char tmpstr[MAX_CHARS+1];
	while (nlines--) {
		if (!ifile.getline(tmpstr, MAX_CHARS, '\n'))
			return false;
	};
	return true;
};
