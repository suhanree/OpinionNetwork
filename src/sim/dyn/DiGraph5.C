// 
// 	Filename : DiGraph5.C
//
//	Author : Suhan Ree
//	Date   : 07-30-2003

#include "Errors.h"
#include "Types.h"
#include "DiGraph5.h"
#include <iostream>
#include <fstream>
#include <set>
#include <list>
#include <map>

#ifndef MAX_CHARS
#define MAX_CHARS 1000
#endif

using namespace std;

// Define a class that represents an edge in a graph.
// A vertex is represented by an integer.
// Constructor.
Edge::Edge(AgentID o, AgentID d, EdgeStrength st) {
	if (o!=d && st>=0.0) {
		ori=o;
		des=d;
		str=st;
	}
	else {
		Error::Bad_Edge error;
		throw error;
	};
};
		
// Constructors.
DiGraph5::DiGraph5(long Nvertex) : Graph(Nvertex) {
	for (AgentID i=0;i<Nvertex;i++) vertexset.insert(i);
};

DiGraph5::DiGraph5(const AgentID * array_vertices, const Edge *array_edges, \
		long Nvertex, long Nedge) : Graph(Nvertex,Nedge) {
	for (AgentID i=0;i<Nvertex;i++) vertexset.insert(array_vertices[i]);
	for (AgentID i=0;i<Nedge;i++)
		// Look for the bad edges that have a bad vertex.
		if (vertexset.find(array_edges[i].show_ori()) != \
			vertexset.end() && vertexset.find( \
			array_edges[i].show_des()) != vertexset.end())
			edgeset.push_back(array_edges[i]);
		else {
			Error::Bad_Edge error;
			throw error;
		};
};

DiGraph5::DiGraph5(const AgentIDSet & vertices, const list<Edge> & edges) {
	vertexset=vertices;
	for (list<Edge>::const_iterator i=edges.begin(); \
		i!=edges.end(); i++)
		// Look for the bad edges that have a bad vertex.
		if (vertexset.find((*i).show_ori()) == \
			vertexset.end() || vertexset.find( \
			(*i).show_des()) == vertexset.end()) {	
			Error::Bad_Edge error;
			throw error;
		};
	edgeset=edges;
	nvertices=vertexset.size();
	nedges=edgeset.size();;
};

// Assignment function.
void DiGraph5::copy(const Graph &gr) {
	this->clear();
	gr.find_vertices(vertexset);
	for (AgentIDSet::const_iterator i=vertexset.begin();i!=vertexset.end();i++) {
		AgentIDMap deps;
		gr.find_out_dep(*i,deps);
		for (AgentIDMap::const_iterator j=deps.begin();j!=deps.end();\
			j++) {
			this->add_edge(*i,j->first,j->second);
		};
	};
};

// Remove a given vertex.
int DiGraph5::remove_vertex(AgentID vertex) {
	AgentIDSet::iterator i=vertexset.find(vertex);
	if (i != vertexset.end()) {
		for (list<Edge>::iterator j=edgeset.begin();\
			j!=edgeset.end();j++)
			if (j->compare_ori(vertex) || j->compare_des(vertex)) {
				edgeset.erase(j);
				j--; // Rewind because it is removed.
			};
		vertexset.erase(i);
		nvertices--;
		return 1;
	}
	else {
		return 0;
	};
};

// Add a given vertex.
int DiGraph5::add_vertex(AgentID vertex) {
	if (vertexset.insert(vertex).second) {
		nvertices++;
		return 1;
	}
	else 
		return 0;
};

// Remove a given edge.
int DiGraph5::remove_edge(AgentID ori, AgentID des) {
	for (list<Edge>::iterator i=edgeset.begin();\
		i!=edgeset.end();i++) 
		if ((*i).compare_ori(ori) && (*i).compare_des(des)){
			edgeset.erase(i);
			nedges--;
			return 1;
		};
	return 0;
};

// Add a given edge.
int DiGraph5::add_edge(AgentID o, AgentID d, EdgeStrength st) {
	if (o!=d && vertexset.find(o)!=vertexset.end() && \
		vertexset.find(d)!=vertexset.end()) {
		for (list<Edge>::iterator i=edgeset.begin();\
			i!=edgeset.end();i++)
			if (i->compare_ori(o) && i->compare_des(d)) {
				i->change_str(st);
				return 0;
			};
		Edge e(o,d,st);
		edgeset.push_back(e);
		nedges++;
		return 1;
	}
	else {
//		Error::Bad_Edge error;
//		throw error;
		return -1;
	};
};

// Clear and make a new graph with N vertices with no edges.
void DiGraph5::new_graph_without_edge(long n) {
	this->clear();
	for (AgentID i=0;i<n;i++) this->add_vertex(i);
	nvertices=n;
	nedges=0;
};

// Find the vertices that affect a given vertex. (Return the number
// 	of vertices or -1 if the vertex doesn't belong to the graph.)
long DiGraph5::find_dep(AgentID v, AgentIDMap &deps) const {
	// This is meaningless for directional graphs, but we can define
	// it as below.
	if (vertexset.find(v)!=vertexset.end()) {
		find_in_dep(v,deps);
		for (list<Edge>::const_iterator i=edgeset.begin();\
			i!=edgeset.end();i++)
			if (i->compare_ori(v)) \
				deps[i->show_des()]=i->show_str();
		return deps.size();
	}
	else
		return -1;
};

long DiGraph5::find_dep(AgentID v, AgentIDSet &deps) const {
	// This is meaningless for directional graphs, but we can define
	// it as below.
	if (vertexset.find(v) != vertexset.end()) {
		find_in_dep(v,deps);
		for (list<Edge>::const_iterator i=edgeset.begin();\
			i!=edgeset.end();i++)
			if (i->compare_ori(v)) deps.insert(i->show_des());
		return deps.size();
	}
	else
		return -1;
};

long DiGraph5::find_in_dep(AgentID v, AgentIDMap &deps) const {
	if (vertexset.find(v)!=vertexset.end()) {
		deps.clear();
		for (list<Edge>::const_iterator i=edgeset.begin();\
			i!=edgeset.end();i++)
			if (i->compare_des(v)) \
				deps[i->show_ori()]=i->show_str();
		return deps.size();
	}
	else
		return -1;
};

long DiGraph5::find_in_dep(AgentID v, AgentIDSet &deps) const {
	if (vertexset.find(v) != vertexset.end()) {
		deps.clear();
		for (list<Edge>::const_iterator i=edgeset.begin();\
			i!=edgeset.end();i++)
			if (i->compare_des(v)) deps.insert(i->show_ori());
		return deps.size();
	}
	else
		return -1;
};

long DiGraph5::find_out_dep(AgentID v, AgentIDMap &deps) const {
	if (vertexset.find(v)!=vertexset.end()) {
		deps.clear();
		for (list<Edge>::const_iterator i=edgeset.begin();\
			i!=edgeset.end();i++)
			if (i->compare_ori(v)) \
				deps[i->show_des()]=i->show_str();
		return deps.size();
	}
	else
		return -1;
};

long DiGraph5::find_out_dep(AgentID v, AgentIDSet &deps) const {
	if (vertexset.find(v) != vertexset.end()) {
		deps.clear();
		for (list<Edge>::const_iterator i=edgeset.begin();\
			i!=edgeset.end();i++)
			if (i->compare_ori(v)) deps.insert(i->show_des());
		return deps.size();
	}
	else
		return -1;
};

// Find the set of vertices.
void DiGraph5::find_vertices(AgentIDSet &vertices) const {
	vertices=vertexset;
};

// Find degree information.
// Find the number of degrees for a given vertex.
long DiGraph5::find_degree(AgentID v) const {
	if (vertexset.find(v) != vertexset.end()) {
		AgentIDSet deps;
		for (list<Edge>::const_iterator i=edgeset.begin();\
			i!=edgeset.end();i++) {
			if (i->compare_des(v)) deps.insert(i->show_ori()) ;
			if (i->compare_ori(v)) deps.insert(i->show_des()) ;
		};
		return deps.size();
	}
	else 
		return -1;
};

long DiGraph5::find_in_deg(AgentID v) const {
	if (vertexset.find(v) != vertexset.end()) {
		AgentID total=0;
		for (list<Edge>::const_iterator i=edgeset.begin();\
			i!=edgeset.end();i++)
			if (i->compare_des(v)) total++;
		return total;
	}
	else
		return -1;
};

long DiGraph5::find_out_deg(AgentID v) const {
	if (vertexset.find(v) != vertexset.end()) {
		long total=0;
		for (list<Edge>::const_iterator i=edgeset.begin();\
			i!=edgeset.end();i++)
			if (i->compare_ori(v)) total++;
		return total;
	}
	else
		return -1;
};

// Clearing all vetices and edges.
void DiGraph5::clear() {
	vertexset.clear();
	edgeset.clear();
	nvertices=0;
	nedges=0;
};
	
// Clearing all edges only.
void DiGraph5::clear_edges() {
	edgeset.clear();
	nedges=0;
};

// Find the clusters of the graph.
// (Returns the number of clusters.)
long DiGraph5::find_clusters(vector<AgentIDSet> &clusters) const {
	retrun 1;
};
	
// Print the graph showing all vertices and edges.
void DiGraph5::print() const {
	cout << "=== vertices ===\n";
	for (AgentIDSet::const_iterator i=vertexset.begin(); \
		i!=vertexset.end();i++) 
		cout << *i << ' ';
	cout << endl;
	cout << "=== edges ===\n";
	for (list<Edge>::const_iterator i=edgeset.begin();\
		i!=edgeset.end();i++) {
		cout << (*i).show_ori() << '\t' << (*i).show_des();
		cout << '\t' << (*i).show_str() << '\n';
	};
	cout << endl;
};
void DiGraph5::write1(ofstream &of) const {
	for (list<Edge>::const_iterator i=edgeset.begin();\
		i!=edgeset.end();i++) {
		of << (*i).show_ori() << '\t' << (*i).show_des();
		of << '\t' << (*i).show_str() << '\n';
	};
};
void DiGraph5::write2(ofstream &of) const {
	AgentIDSet deps;
	for (AgentIDSet::const_iterator i=vertexset.begin(); \
		i!=vertexset.end();i++) {
		long num=find_in_dep(*i,deps);
		of << *i;
		for (AgentIDSet::const_iterator j=deps.begin();\
			j!=deps.end();j++)
			of << '\t' << *j;
		of << '\n';
	};
};

// Read the graph info from a file.
void DiGraph5::read1(std::ifstream &ifile) {
	long nagents;
	char tmpstr[MAX_CHARS+1];

	// Read the number of vertices. Vertices will be
	// numbered from 0 to nagent-1.
	while (ifile.peek()=='#')
		ifile.getline(tmpstr, MAX_CHARS, '\n');
	ifile >> nagents;

	// Erase and make graph with no edges.
	this->new_graph_without_edge(nagents);

	// Add edges.
	AgentID ori, des;
	EdgeStrength str;
	do {
		if(ifile.peek()!='#' && ifile >> ori >> des >> str)
			this->add_edge(ori,des,str);
	} while (ifile.getline(tmpstr, MAX_CHARS, '\n'));
};

void DiGraph5::read2(std::ifstream &ifile) {

};
