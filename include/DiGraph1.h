// 
// 	Filename : DiGraph1.h
//
//	Author : Suhan Ree
//	Date   : 10-15-2003

#ifndef DIGRAPH1_H
#define DIGRAPH1_H

#include "Graph.h"
#include "Types.h"
#include <set>
#include <map>
#include <vector>
#include <fstream>

using namespace std;

// Class for graphs (fixed # of vertices, no weight on edges)
// Enhanced (but using more memory) version of DiGraph1 
// by having two data sets, one for the in-edges and the other for the out-edges.
class DiGraph1 : public Graph1 {
   public :
	// Constructors.
   	DiGraph1() {}; // Default constructor for no vertex and no edge.
	DiGraph1(long Nvertex): Graph1(Nvertex), gra_out(Nvertex) {};
	// Destructor.
	~DiGraph1() {};

	// Remove a given vertex. In this graph, # of vertices are fixed,
	// so a vertex cannot be removed, thereby the function returns 0.
	int remove_vertex(AgentID v) {
		return 0;
	};
	// Add a given vertex. In this graph, # of vertices are fixed,
	// so a vertex cannot be added, thereby the function returns 0.
	int add_vertex(AgentID v) {
		return 0;
	};

	// Remove a given edge. Returns 0 if it doesn't exist.
	int remove_edge(AgentID o, AgentID d);
	// Add a given edge. 
	// Returns -1 if it has a non-existing vertex, 0 if the edge
	// already exists, 1 if successful.
	int add_edge(AgentID ori, AgentID des, EdgeStrength str=1);

	// Find the vertices that affect a given vertex. (Return the number
	// 	of vertices or -1 if the vertex doesn't belong to the graph.)
	// (overloaded)
	long find_dep(AgentID v, AgentIDMap &deps) const;
	long find_dep(AgentID v, AgentIDSet &deps) const;
	long find_in_dep(AgentID v, AgentIDMap &deps) const;
	long find_in_dep(AgentID v, AgentIDSet &deps) const;
	long find_out_dep(AgentID v, AgentIDMap &deps) const;
	long find_out_dep(AgentID v, AgentIDSet &deps) const;

	// Find degree information.
	// Find the number of degrees for a given vertex.
	// Returns -1 if the vertex doesn't exist.
	long find_degree(AgentID v) const;
	long find_in_deg(AgentID v) const;
	long find_out_deg(AgentID v) const;

	// True if directional
	bool if_directional() const {
		return true;
	};

	// Clear and make a new graph with N vertices with no edges.
	void new_graph_without_edge(long n);
	
	// Assignment function.
	void copy(const Graph &gr);

	// Clearing all vetices and edges.
	void clear();

	// Clearing all edges only.
	void clear_edges();

	// Print the graph showing all vertices and edges.
	void print() const;
	// Writing all edges. (origin and destination in a line)
	void write1(std::ofstream &of) const;
	// For each destination, a set of origins are given.
	void write2(std::ofstream &of) const;

	// Read the graph info from a file.
	void read1(std::ifstream &ifile);
	void read2(std::ifstream &ifile);

   private :
   	// Information about out-edges for each vertex. 
	// 'gra' in Graph1 only contains the informaion about in-edges.
	// By having this information, we gain speed but lose some memory space.
	std::vector<AgentIDSet> gra_out;
};

#endif
