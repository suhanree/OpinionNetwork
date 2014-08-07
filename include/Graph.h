// 
// 	Filename : Graph.h
//
//	Author : Suhan Ree
//	Date   : 06-10-2004

#ifndef GRAPH_H
#define GRAPH_H

#include "Types.h"
#include <set>
#include <map>
#include <vector>
#include <fstream>

// An abstract base class that represents a graph.
// It only contains the basic operations of the graph 
// regardless of the data structure of the graph.
class Graph {
   public :
	// Constructor.
   	Graph(long Nvertex=0, long Nedge=0) : nvertices(Nvertex), nedges(Nedge) {};
	
	// Virtual destructor.
	virtual ~Graph() {};

	// Show sizes of data members.
   	long show_vertex_size() const {
		return nvertices;
	};

	long show_edge_size() const {
		return nedges;
	};

	// Clear and make a new graph with N vertices with no edges.
	virtual void new_graph_without_edge(long n)=0;

	// Find the set of vertices.
	virtual void find_vertices(AgentIDSet &vertexset) const=0;

	// Assignment function.
	virtual void copy(const Graph &gr)=0;

	// Clearing all vetices and edges.
	virtual void clear()=0;
	// Clearing all edges only.
	virtual void clear_edges()=0;

	// Remove a given vertex. Returns 0 if it doesn't exist.
	// (Edges associated with this vertex will be removed also.)
	virtual int remove_vertex(AgentID v)=0;
	// Add a given vertex. Returns 0 if it already exists.
	virtual int add_vertex(AgentID v)=0;
	// Remove a given edge. Returns 0 if it doesn't exist.
	virtual int remove_edge(AgentID v1, AgentID v2)=0;
	// Add a given edge. 
	// Returns -1 if it has a non-existing vertex, 0 if the edge
	// already exists, 1 if successful.
	virtual int add_edge(AgentID v1, AgentID v2, EdgeStrength str=1)=0;

	// Find the vertices that affect a given vertex. (Return the number
	// 	of vertices or -1 if the vertex doesn't belong to the graph.)
	virtual long find_dep(AgentID v, AgentIDMap &deps) const=0;
	virtual long find_dep(AgentID v, AgentIDSet &deps) const=0;
	virtual long find_in_dep(AgentID v, AgentIDMap &deps) const=0;
	virtual long find_in_dep(AgentID v, AgentIDSet &deps) const=0;
	virtual long find_out_dep(AgentID v, AgentIDMap &deps) const=0;
	virtual long find_out_dep(AgentID v, AgentIDSet &deps) const=0;

	// Find degree information.
	// Find the number of degrees for a given vertex. 
	// Returns -1 if the vertex doesn't exist.
	virtual long find_degree(AgentID v) const=0;
	virtual long find_in_deg(AgentID v) const=0;
	virtual long find_out_deg(AgentID v) const=0;
	// True if directional
	virtual bool if_directional() const=0;

	// Find the clusters of the graph.
	// (Returns the number of clusters.)
	virtual long find_clusters(std::vector<AgentIDSet> &clusters) const=0;
	
	// Print the graph showing all vertices and edges.
	// 	print  : show vertices and edges separately.
	// 	write1 : format1 (show all the links each in a line)
	//				(assuming vertices are fixed)
	//			ex. ori des strength
	// 	write2 : format2 (show all vertices with link info)
	//				(assuming strengths are equal)
	//			ex. destination ori1 ori2 ori3 ...
	virtual void print() const=0;	// To stdout.
	virtual void write1(std::ofstream &of) const=0;	// To a file.
	virtual void write2(std::ofstream &of) const=0;	// To a file.

	// Write or print the summary of the graph
	//	format: # of vertices, # of edges, average degree 
	void write_summary(std::ofstream &of) const;
	void print_summary() const;
	
	// Read the graph info from a file. (using format 1 and 2)
	virtual void read1(std::ifstream &ifile)=0;
	virtual void read2(std::ifstream &ifile)=0;

   protected:
   	long nvertices; // Number of vertices.
   	long nedges; // Number of edges.
};
	

// Abstract class that represents graphs (fixed vertices, no edge strength)
class Graph1 : public Graph {
   public :
	// Constructors.
	Graph1() : Graph() {};
	Graph1(AgentID Nvertex) : Graph(Nvertex), gra(Nvertex) {};

	// Destructor.
	~Graph1() {};

	// Clear and make a new graph with N vertices with no edges.
	void new_graph_without_edge(long n);
	
	// Find the set of vertices.
	void find_vertices(AgentIDSet &vertexset) const;

	// Assignment function.
	void copy(const Graph &gr);

	// Clearing all vetices and edges.
	void clear();

	// Clearing all edges only.
	void clear_edges();

	// Find the clusters of the graph.
	// (Returns the number of clusters.)
	long find_clusters(std::vector<AgentIDSet> &clusters) const;
	
   protected :
	std::vector<AgentIDSet> gra;
};

/* 

// Abstract class that represents graphs (fixed vertices, with edge strength)
class Graph2 : public Graph {
   public :
	// Constructors.
	Graph2() : Graph() {};

	// Destructor.
	~Graph2() {};

	// Clear and make a new graph with N vertices with no edges.
	void new_graph_without_edge(long n);
	
	// Find the set of vertices.
	void find_vertices(AgentIDSet &vertexset) const;

	// Assignment function.
	void copy(const Graph &gr);

	// Clearing all vetices and edges.
	void clear();

	// Clearing all edges only.
	void clear_edges();

	// Find the clusters of the graph.
	// (Returns the number of clusters.)
	long find_clusters(std::vector<AgentIDSet> &clusters) const;
	
   protected :
	std::vector<AgentIDMap> gra;
};

// Abstract class that represents graphs (varying vertices, no edge strength)
class Graph3 : public Graph {
   public :
	// Constructors.
	Graph3() : Graph() {};

	// Destructor.
	~Graph3() {};

	// Clear and make a new graph with N vertices with no edges.
	void new_graph_without_edge(long n);
	
	// Find the set of vertices.
	void find_vertices(AgentIDSet &vertexset) const;

	// Assignment function.
	void copy(const Graph &gr);

	// Clearing all vetices and edges.
	void clear();

	// Clearing all edges only.
	void clear_edges();

	// Find the clusters of the graph.
	// (Returns the number of clusters.)
	long find_clusters(std::vector<AgentIDSet> &clusters) const;
	
   protected :
	std::map<AgentID,AgentIDSet> gra;
	     
};

// Abstract class that represents graphs (varying vertices, with edge strength)
class Graph4 : public Graph {
   public :
	// Constructors.
	Graph4() : Graph() {};

	// Destructor.
	~Graph4() {};

	// Clear and make a new graph with N vertices with no edges.
	void new_graph_without_edge(long n);
	
	// Find the set of vertices.
	void find_vertices(AgentIDSet &vertexset) const;

	// Assignment function.
	void copy(const Graph &gr);

	// Clearing all vetices and edges.
	void clear();

	// Clearing all edges only.
	void clear_edges();

	// Find the clusters of the graph.
	// (Returns the number of clusters.)
	long find_clusters(std::vector<AgentIDSet> &clusters) const;
	
   protected :
	std::map<AgentID,AgentIDMap> gra;
	     

};

*/

#endif
