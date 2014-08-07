// 
// 	Filename : Input.h 
//
//	Author : Suhan Ree
//	Date   : 09-29-2003

#ifndef INPUT_H
#define INPUT_H

#include <fstream>
#include <iostream>
#include <string>
#include "Graph.h"

// A class that handles the input file.

class Input {
   public:
   	// Constructors
   	Input(const std::string &file);
   	Input(const char *file);
   	~Input() {
		ifile.close();
	};

	// close the file.
	void close() {
		ifile.close();
	};

	// Get the filename.
	std::string get_filename() const {
		return filename;
	};
	
	// EOF
	bool eof() const {
		return ifile.eof();
	};

	// Read objects of fundamental types.
	bool read(bool &tf) {
		return ifile >> tf;
	};
	bool read(short &sh) {
		return ifile >> sh;
	};
	bool read(int &in) {
		return ifile >> in;
	};
	bool read(long &lo) {
		return ifile >> lo;
	};
	bool read(unsigned long &lo) {
		return ifile >> lo;
	};
	bool read(char &c) {
		return ifile >> c;
	};
	bool read(std::string &str) {
		return ifile >> str;
	};
	bool read(double &a) {
		return ifile >> a;
	};
	bool read(float &a) {
		return ifile >> a;
	};

	// Peek
	int peek() {
		return ifile.peek();
	};

	// Read the given number of lines and ignore them
	bool read_lines(int nlines);

	// Read the graph from the input file.
	void read_graph(Graph &gra) {
		gra.read1(ifile);
	};
	void read_graph2(Graph &gra) {
		gra.read2(ifile);
	};
	  
   private:
   	std::string filename; // Input file name.
   protected:
	std::ifstream ifile; // Input file stream.

   private:
   	Input() {}; // Hiding the default constructor.
};

#endif
