// 
// 	Filename : RWIn.h 
//
//	Author : Suhan Ree
//	Date   : 09-29-2003

#ifndef RWIN_H
#define RWIN_H

#include <string>
#include "Input.h"
#include "Graph.h"
#include "Agent.h"
#include "RWTypes.h"

// A class that handles the input file.
// Usage:	Input inp(arg[1]); // Input filename given.
//		inp.read(); // Read all the key-value pairs.
//
//		// When there are two kinds of keys, "ABC" and "DFG",
//		// representing a (int) and d (double) respectively,
//		// a and d will be obtained like this.
//		inp.get("ABC", a);
//		inp.get("DFG", d);

		

class RWIn : public Input {
   public:
   	RWIn(const std::string &filename): Input(filename) {};
   	RWIn(const char *filename): Input(filename) {};
	~RWIn() {};

	// Read the RWAgent info from the file.
	void read_all_agents(AgentMap &amap);
	void read_all_agents(AgentVec &avec);

};

#endif
