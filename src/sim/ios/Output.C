// 
// 	Filename : Output.C
//
//	Author : Suhan Ree
//	Date   : 08-26-2003

#include "Output.h"
#include <cstdlib>

Output::Output(const std::string &file): filename(file) {
	std::string noout("noout");
	if (filename!=noout) ofile.open(filename.c_str(), std::ios::out);
};

Output::Output(const char *file): filename(file) {
	std::string noout("noout");
	if (filename!=noout) ofile.open(filename.c_str(), std::ios::out);
};
