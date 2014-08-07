// 
// 	Filename : GraphND1.C
//
//	Author : Suhan Ree
//	Date   : 10-15-2003

#include "Errors.h"
#include "Types.h"
#include "GraphND1.h"
#include <iostream>
#include <fstream>
#include <set>
#include <map>

#ifndef MAX_CHARS
#define MAX_CHARS 1000
#endif

using namespace std;

// Remove a given edge. Returns 0 if it doesn't exist.
int GraphND1::remove_edge(AgentID v1, AgentID v2) {
	if (v1<0 || v2<0 || v1>=gra.size() || v2>=gra.size())
		return 0;
	else {
		if (!gra[v1].erase(v2)) return 0;
		gra[v2].erase(v1);
		nedges--;
		return 1;
	};
};
	
// Add a given edge. 
// Returns -1 if it has a non-existing vertex, 0 if the edge
// already exists, 1 if successful.
int GraphND1::add_edge(AgentID v1, AgentID v2, EdgeStrength str) {
	if (v1==v2 || v1<0 || v2<0 || v1>=gra.size() || v2>=gra.size())
		return -1;
	else {
		if (gra[v1].insert(v2).second && gra[v2].insert(v1).second) {
			nedges++;
			return 1;
		}
		else
			return 0;
	};
};

// Find the vertices that affect a given vertex. (Return the number
// 	of vertices or -1 if the vertex doesn't belong to the graph.)
long GraphND1::find_dep(AgentID v, AgentIDMap &deps) const {
	deps.clear();
	if (v<0 || v>=gra.size()) return -1;
	else {
		for(AgentIDSet::const_iterator i=gra[v].begin(); \
			i!=gra[v].end();i++) 
			deps[*i]=1; // Weight is 1 for all edges here.
		return gra[v].size();
	};
};

long GraphND1::find_dep(AgentID v, AgentIDSet &deps) const {
	deps.clear();
	if (v<0 || v>=gra.size()) return -1;
	else {
		deps=gra[v];
		return gra[v].size();
	};
};

// Find degree information.
// Find the number of degrees for a given vertex.
long GraphND1::find_degree(AgentID v) const {
	if (v<0 || v >= gra.size()) return -1;
	else return gra[v].size();
};

// Print the graph showing all vertices and edges.
void GraphND1::print() const {
	long size=gra.size();
	cout << "=== vertices ===\n";
	cout << "There are " << size << " vertices";
	if (size) cout << ", from 0 to " << size-1;
	cout << ".\n";
	cout << "=== edges ===\n";
	cout << "There are " << show_edge_size() << " non-directional edges.\n";
	for (long j=0; j<gra.size();j++) {
		cout << j << ": ";
		for (AgentIDSet::const_iterator i=gra[j].begin();\
			i!=gra[j].end();i++)
			cout << *i << ' '; 
		cout << endl;
	};
};

void GraphND1::write1(ofstream &of) const {
	for (long j=0; j<gra.size();j++)
		for (AgentIDSet::const_iterator i=gra[j].begin();\
			i!=gra[j].end();i++)
			of << j << '\t' << *i << '\n';
};

void GraphND1::write2(ofstream &of) const {
	for (long j=0; j<gra.size();j++) {
		of << j;
		for (AgentIDSet::const_iterator i=gra[j].begin();\
			i!=gra[j].end();i++)
			of << '\t' << *i; 
		of << '\n';
	};
};
 
// Read the graph info from a file.
void GraphND1::read1(std::ifstream &ifile) {
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
	do {
		if(ifile.peek()!='#' && ifile >> ori >> des)
			this->add_edge(ori,des);
	} while (ifile.getline(tmpstr, MAX_CHARS, '\n'));
};

void GraphND1::read2(std::ifstream &ifile) {

};
