// 
// 	Filename : Errors.h
//
//	Author : Suhan Ree
//	Date   : 10-01-2003

// errors for the AWDSIM project.

#include <string>

#ifndef ERRORS_H
#define ERRORS_H

namespace Error {

// Edge is bad (two vertices are the same, non-existing vertex, etc)
struct Bad_Edge {}; 

// Maximum number of random number for a given generator has been reached.
// To be effective the number of random numbers should be lower than randmax.
struct TOO_MANY_RN_NEEDED {}; 

// Maximum number of random number for each agent has been reached.
struct MAX_RN_REACHED {}; 

// Bad input file.
struct Bad_Input_File {
	Bad_Input_File(): filename(), message() {};
	Bad_Input_File(std::string file): filename(file), message() {};
	Bad_Input_File(std::string file, std::string mes): filename(file), message(mes) {};
	std::string filename;
	std::string message;
};

// Bad input value from a file.
struct Bad_Input_Value {
	Bad_Input_Value(): filename(), line(0) {};
	Bad_Input_Value(std::string file, long line1): 
		filename(file), line(line1) {};
	std::string filename;
	long line;
};

// Torus size is given with non-positive numbers.
struct Bad_Torus_Size {};

}; // End of namespace Errors.

#endif
