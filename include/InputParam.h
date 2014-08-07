// 
// 	Filename : InputParam.h 
//
//	Author : Suhan Ree
//	Date   : 09-29-2003

#ifndef INPUTPARAM_H
#define INPUTPARAM_H

#include <iostream>
#include <string>
#include <map>
#include "Input.h"

// A class that handles the input file for input parameters.
// Usage:	Input inp(arg[1]); // Input filename given.
//		inp.read(); // Read all the key-value pairs.
//
//		// When there are two kinds of keys, "ABC" and "DFG",
//		// representing a (int) and d (double) respectively,
//		// a and d will be obtained like this.
//		inp.get("ABC", a);
//		inp.get("DFG", d);

		

class InputParam : public Input {
   public:
	// "infile" is the filename of the input file.
	InputParam(): Input("input"), key_val() {};
   	InputParam(const std::string &infile): Input(infile), key_val() {};
   	InputParam(const char *infile): Input(infile), key_val() {};
   	~InputParam() {};

	// Read the input file and save the info in the map.
	// When the same key appears more than once, the last one overwrite
	// the previous values.
	void read();

	// Print key-value pairs read.
	void print_key_val();

	// Delete the all values stored.
	void clear() {
		key_val.clear();
	};

  	// Return the value of a key in the second argument
	bool get(const std::string str,  std::string &str1, std::ostream &ofile);
	bool get(const std::string str,  bool &tf, std::ostream &ofile);
	bool get(const std::string str,  short &num, std::ostream &ofile);
	bool get(const std::string str,  int &num, std::ostream &ofile);
	bool get(const std::string str,  long &num, std::ostream &ofile);
	bool get(const std::string str,  unsigned long &num, std::ostream &ofile);
	bool get(const std::string str,  float &num, std::ostream &ofile);
	bool get(const std::string str,  double &num, std::ostream &ofile);

   private:
	// Input parameters will be given as a key value pair inside
	// the input file.
	std::map<std::string,std::string> key_val;
};

#endif
