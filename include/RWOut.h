// 
// 	Filename : RWOut.h 
//
//	Author : Suhan Ree
//	Date   : 09-19-2003

#ifndef RWOUT_H
#define RWOUT_H

#include "Output.h"
#include "Graph.h"
#include "GraphND1.h"
#include "Types.h"
#include "RWTypes.h"
#include "RWState.h"
#include <fstream>
#include <string>
#include <vector>
#include <map>

// An abstract class that handles the output.

class RWOut : public Output {
   public:
   	// Constructors.
	RWOut(const string &outfile): Output(outfile) {};
	RWOut(const char *outfile): Output(outfile) {};
	// Destructor.
   	~RWOut() {};	

	// Write the information about an agent.
	void write_agent(AgentID id, const AgentMap &amap, const Graph1 &ag, const Sgraph &sg, long time=-1);
	void write_agent(AgentID id, const AgentVec &avec, const Graph1 &ag, const Sgraph &sg, long time=-1);

	// Write the information about given agents.
	void write_all_agents(const AgentMap &amap, long time=-1);
	void write_all_agents(const AgentVec &avec, long time=-1);

	// When this value is used with the constructor, no output will be made.
	static std::string noout;

   private:
   	RWOut(): Output("Output") {}; // Prevent using the default constrcutor.
};

#endif
