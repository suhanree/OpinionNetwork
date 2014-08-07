// 
// 	Filename : Output.h 
//
//	Author : Suhan Ree
//	Date   : 08-26-2003

#ifndef OUTPUT_H
#define OUTPUT_H

#include "Agent.h"
#include "Graph.h"
#include <fstream>
#include <string>

// An base class that handles the output.
// This class will be inherited to a derived class,
// which will contain more specific member functions
// for outputs.

class Output {
   public:
   	// Constructors.
	Output(const std::string &file);
	Output(const char *file);
	// Destructor.
   	~Output() {
		if (ofile) ofile.close();
	};	

	// Write objects of fundamental types.
	void write(bool tf) {
		ofile << tf;
	};
	void write(short sh) {
		ofile << sh;
	};
	void write(unsigned short us) {
		ofile << us;
	};
	void write(int in) {
		ofile << in;
	};
	void write(unsigned int ui) {
		ofile << ui;
	};
	void write(long lo) {
		ofile << lo;
	};
	void write(unsigned long lo) {
		ofile << lo;
	};
	void write(char c) {
		ofile << c;
	};
	void write(const char *str) {
		ofile << str;
	};
	void write(std::string &str) {
		ofile << str;
	};
	void write(double a) {
		ofile << a;
	};
	void write(float a) {
		ofile << a;
	};


	// Write the information about a graph.
	// Format 1 (fixed vertices), format 2 (no strength)(des ori1 ori2 ori3 ...)
	void write_graph1(const Graph &gra) {
		gra.write1(ofile);
	};
      
	void write_graph2(const Graph &gra) {
		gra.write2(ofile);
	};

	// Write the summary of the graph
	//      format: # of vertices, # of edges, average degree.
	void write_graph_summary(const Graph &gra) {
		gra.write_summary(ofile);
	}; 
	      
	// Close the file.
	void close() {
		ofile.close();
	};

   private:
   	std::string filename; // Output file name.
   protected:
	std::ofstream ofile; // Output file stream.

   private:
   	Output() {}; // Prevent using the default constructor.
};

#endif
