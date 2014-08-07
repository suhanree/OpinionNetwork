// 
// 	Filename : GraphND3.h
//
//	Author : Suhan Ree
//	Date   : 10-15-2003

#ifndef GRAPHND3_H
#define GRAPHND3_H

#include "Graph.h"
#include "Types.h"
#include <fstream>
#include <set>
#include <map>

// Class for graphs (varying # of vertices, no weight on edges)
class GraphND3 : public Graph3 {
   public :
	// Constructor.
   	GraphND3() {};
	// Virtual destructor.
	~GraphND3() {};

	// Remove a given vertex. Returns 0 if it doesn't exist.
	// (Edges associated with this vertex will be removed also.)
	int remove_vertex(AgentID v);
	// Add a given vertex. Returns 0 if it already exists.
	int add_vertex(AgentID v);
	// Remove a given edge. Returns 0 if it doesn't exist.
	int remove_edge(AgentID v1, AgentID v2);
	// Add a given edge. 
	// Returns -1 if it has a non-existing vertex, 0 if the edge
	// already exists, 1 if successful.
	int add_edge(AgentID v1, AgentID v2, EdgeStrength str=1);

	// Find the vertices that affect a given vertex. (Return the number
	// 	of vertices or -1 if the vertex doesn't belong to the graph.)
	long find_dep(AgentID v, AgentIDMap &deps) const;
	long find_dep(AgentID v, AgentIDSet &deps) const;
	long find_in_dep(AgentID v, AgentIDMap &deps) const {
		return find_dep(v,deps);
	};
	long find_in_dep(AgentID v, AgentIDSet &deps) const {
		return find_dep(v,deps);
	};
	long find_out_dep(AgentID v, AgentIDMap &deps) const {
		return find_dep(v,deps);
	};
	long find_out_dep(AgentID v, AgentIDSet &deps) const {
		return find_dep(v,deps);
	};

	// Find degree information.
	// Find the number of degrees for a given vertex.
	// Returns -1 if the vertex doesn't exist.
	long find_degree(AgentID v) const;
	long find_in_deg(AgentID v) const {
		return find_degree(v);
	};
	long find_out_deg(AgentID v) const {
		return find_degree(v);
	};
	// True if directional
	bool if_directional() const {
		return false;
	};

	// Print the graph showing all vertices and edges.
	void print() const;
	void write1(std::ofstream &of) const;
	void write2(std::ofstream &of) const;

	// Read the graph info from a file.
	void read1(std::ifstream &ifile);
	void read2(std::ifstream &ifile);
};
   	
#endif
