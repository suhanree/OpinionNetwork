// 
// 	Filename : DiGraph5.h
//
//	Author : Suhan Ree
//	Date   : 07-30-2003

#ifndef GRAPHND5_H
#define GRAPHND5_H

#include "Graph.h"
#include "Types.h"
#include <list>
#include <set>
#include <map>
#include <fstream>

using namespace std;

// Defining a class that represents an edge in a graph of vertices.
// A vertex is represented by an integer (positive).
class Edge {
   public :
   	// User-defined constructors. (It's an error if the default
	//	constructor is used because ori=des.)
	Edge(AgentID o=0, AgentID d=0, EdgeStrength st=1);
	// Show data members.
	AgentID show_ori() const {return ori;};
	AgentID show_des() const {return des;};
	EdgeStrength show_str() const {return str;};
	// Compare an integer with ori or des.
	bool compare_ori(AgentID o) const {return ori==o;};
	bool compare_des(AgentID d) const {return des==d;};
	// Change the strength.
	void change_str(EdgeStrength st) {str=st;};
	// Destructor.
	~Edge() {};
	
   private :
   	AgentID ori, des; // Origin and destination.
	EdgeStrength str;
};

// Less Than operation of the class Edge.
class EdgeLessThan {
   public :
   	inline bool operator() (const Edge &e1, const Edge &e2) {
		return (e1.show_ori()==e2.show_ori()? e1.show_des() < \
			e2.show_des() : e1.show_ori() < e2.show_ori());
	};
};

// Class for graphs (varied # of vertices
// using the Edge class, no weight on edges)
class DiGraph5 : public Graph {
   public :
	// Constructors.
   	DiGraph5() {}; // Default constructor for no vertex and no edge.
	DiGraph5(long Nvertex);
	DiGraph5(const AgentID * array_vertices, const Edge *array_edges, \
		AgentID Nvertex, AgentID Nedge);
	DiGraph5(const AgentIDSet & vertices, const list<Edge> & edges);
	// Destructor.
	~DiGraph5() {};

	// Assignment function.
	void copy(const Graph &gr);

	// Show sizes of data members.
	long show_vertex_size()  const {return vertexset.size();};
	long show_edge_size()  const {return edgeset.size();};

	// Remove a given vertex. Returns 0 if it doesn't exist.
	// (Edges associated with this vertex will be removed also.)
	int remove_vertex(AgentID vertex);
	// Add a given vertex. Returns 0 if it already exists.
	int add_vertex(AgentID vertex);
	// Remove a given edge. Returns 0 if it doesn't exist.
	int remove_edge(AgentID o, AgentID d);
	// Add a given edge. 
	// Returns -1 if it has a non-existing vertex, 0 if the edge
	// already exists, 1 if successful.
	int add_edge(AgentID ori, AgentID des, EdgeStrength str=1);

	// Clear and make a new graph with N vertices with no edges.
	void new_graph_without_edge(long n);

	// Find the vertices that affect a given vertex. (Return the number
	// 	of vertices or -1 if the vertex doesn't belong to the graph.)
	// (overloaded)
	long find_dep(AgentID v, AgentIDMap &deps) const;
	long find_dep(AgentID v, AgentIDSet &deps) const;
	long find_in_dep(AgentID v, AgentIDMap &deps) const;
	long find_in_dep(AgentID v, AgentIDSet &deps) const;
	long find_out_dep(AgentID v, AgentIDMap &deps) const;
	long find_out_dep(AgentID v, AgentIDSet &deps) const;

	// Find the set of vertices.
	void find_vertices(AgentIDSet &vertices) const;

	// Find degree information.
	// Find the number of degrees for a given vertex.
	// Returns -1 if the vertex doesn't exist.
	long find_degree(AgentID v) const; // sum of in-degree and out-degree
	long find_in_deg(AgentID v) const;
	long find_out_deg(AgentID v) const;
	// True if directional
	bool if_directional() const {
		return true;
	};

	// Clearing all vetices and edges.
	void clear();
	// Clearing all edges only.
	void clear_edges();

	// Find the clusters of the graph.
	// (Returns the number of clusters.)
	long find_clusters(vector<AgentIDSet> &clusters) const;
	
	// Print the graph showing all vertices and edges.
	void print() const;
	void write1(std::ofstream &of) const;
	void write2(std::ofstream &of) const;

	// Read the graph info from a file.
	void read1(std::ifstream &ifile);
	void read2(std::ifstream &ifile);

   private :
   	AgentIDSet vertexset;
	list<Edge> edgeset;
};

   	
#endif
