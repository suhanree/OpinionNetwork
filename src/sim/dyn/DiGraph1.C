// 
// 	Filename : DiGraph1.C
//
//	Author : Suhan Ree
//	Date   : 10-15-2003

#include "Errors.h"
#include "Types.h"
#include "DiGraph1.h"
#include "Utilities.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstdlib>

using namespace std;

const long MAX_CHARS=1000;

//Remove a given edge. Returns 0 if it doesn't exist.
int DiGraph1::remove_edge(AgentID v1, AgentID v2) {
	if (v1<0 || v2<0 || v1>=gra.size() || v2>=gra.size())
		return 0;
	else {
		if (!gra[v2].erase(v1)) return 0;
		if (!gra_out[v1].erase(v2)) return 0;
		nedges--;
		return 1;
	};
};
	
// Add a given edge. 
// Returns -1 if it has a non-existing vertex, 0 if the edge
// already exists, 1 if successful.
int DiGraph1::add_edge(AgentID v1, AgentID v2, EdgeStrength str) {
	if (v1==v2 || v1<0 || v2<0 || v1>=gra.size() || v2>=gra.size())
		return -1;
	else {
		if((gra[v2].insert(v1)).second && (gra_out[v1].insert(v2)).second) {
			nedges++;
			return 1;
		}
		else
			return 0;
	};
};

// Find the vertices that affect a given vertex. (Return the number
// 	of vertices or -1 if the vertex doesn't belong to the graph.)
long DiGraph1::find_dep(AgentID v, AgentIDMap &deps) const {
	// This is meaningless for directional graphs, but we can define
	// it as below.
	if (v<0 || v>=gra.size()) return -1;
	else {
		find_in_dep(v,deps);
		for(AgentIDSet::const_iterator i=gra_out[v].begin(); \
			i!=gra_out[v].end();i++) 
			deps[*i]=1; // Weight is 1 for all edges here.
		return deps.size();
	};
};

long DiGraph1::find_dep(AgentID v, AgentIDSet &deps) const {
	// This is meaningless for directional graphs, but we can define
	// it as below.
	if (v<0 || v>=gra.size()) return -1;
	else {
		find_in_dep(v,deps);
		for(AgentIDSet::const_iterator i=gra_out[v].begin(); \
			i!=gra_out[v].end();i++) 
			deps.insert(*i); // Weight is 1 for all edges here.
		return deps.size();
	};
};

long DiGraph1::find_in_dep(AgentID v, AgentIDMap &deps) const {
	deps.clear();
	if (v<0 || v>=gra.size()) return -1;
	else {
		for(AgentIDSet::const_iterator i=gra[v].begin(); \
			i!=gra[v].end();i++) 
			deps[*i]=1; // Weight is 1 for all edges here.
		return gra[v].size();
	};
};

long DiGraph1::find_in_dep(AgentID v, AgentIDSet &deps) const {
	if (v<0 || v>=gra.size()) return -1;
	else {
		deps=gra[v];
		return gra[v].size();
	};
};

long DiGraph1::find_out_dep(AgentID v, AgentIDMap &deps) const {
	deps.clear();
	if (v<0 || v>=gra.size()) return -1;
	else {
		for(AgentIDSet::const_iterator i=gra_out[v].begin(); \
			i!=gra_out[v].end();i++) 
			deps[*i]=1; // Weight is 1 for all edges here.
		return gra_out[v].size();
	};
};

long DiGraph1::find_out_dep(AgentID v, AgentIDSet &deps) const {
	if (v<0 || v>=gra_out.size()) return -1;
	else {
		deps=gra_out[v];
		return gra_out[v].size();
	};
};

// Find degree information.
// Find the number of degrees for a given vertex.
long DiGraph1::find_degree(AgentID v) const {
	if (v<0 || v >= gra.size()) return -1;
	else {
		set<AgentID> deps;
		for (set<AgentID>::const_iterator i=gra_out[v].begin();\
			i!=gra_out[v].end();i++)
			deps.insert(*i);
		for (set<AgentID>::const_iterator i=gra[v].begin();\
			i!=gra[v].end();i++)
			deps.insert(*i);
		return deps.size();
	};
};
long DiGraph1::find_in_deg(AgentID v) const {
	if (v<0 || v >= gra.size()) return -1;
	else return gra[v].size();
};
long DiGraph1::find_out_deg(AgentID v) const {
	if (v<0 || v >= gra.size()) return -1;
	else
		return gra_out[v].size();
};

// Assignment function.
void DiGraph1::copy(const Graph &gr) {
	this->clear_edges();
	for (AgentID i=0;i<nvertices;i++) {
		gr.find_in_dep(i,gra[i]);
		gr.find_out_dep(i,gra_out[i]);
	};
	nedges=gr.show_edge_size();
	nvertices=gr.show_vertex_size();
};

// Clear and make a new graph with N vertices with no edges.
void DiGraph1::new_graph_without_edge(long n) {
	this->clear();
	AgentIDSet aset;
	for (AgentID i=0;i<n;i++) {
		gra.push_back(aset);
		gra_out.push_back(aset);
	};
	nvertices=n;
	nedges=0;
};

// Clearing all vetices and edges.
void DiGraph1::clear() {
	for (long i=0; i<gra.size();i++) {
		gra[i].clear();
		gra_out[i].clear();
	};
	gra.clear();
	gra_out.clear();
	nvertices=0;
	nedges=0;
};
	
// Clearing all edges only.
void DiGraph1::clear_edges() {
	for (long i=0; i<gra.size();i++) {
		gra[i].clear();
		gra_out[i].clear();
	};
	nedges=0;
};

// Print the graph showing all vertices and edges.
void DiGraph1::print() const {
	long size=gra.size();
	cout << "=== vertices ===\n";
	cout << "There are " << size << " vertices";
	if (size) cout << ", from 0 to " << size-1;
	cout << ".\n";
	cout << "=== edges ===\n";
	cout << "There are " << show_edge_size() << " out-directional edges.\n";
	for (long j=0; j<gra.size();j++) {
		AgentIDSet idset;
		this->find_out_dep(j,idset);
		cout << j << ": ";
		for (AgentIDSet::const_iterator i=idset.begin();\
			i!=idset.end();i++)
			cout << *i << ' '; 
		cout << endl;
	};
};

void DiGraph1::write1(ofstream &of) const {
	for (long j=0; j<gra.size();j++) {
		AgentIDSet idset;
		this->find_out_dep(j,idset);
		for (AgentIDSet::const_iterator i=idset.begin();\
			i!=idset.end();i++)
			of << j << '\t' << *i << '\n';
	};
};

void DiGraph1::write2(ofstream &of) const {
	for (long j=0; j<gra.size();j++) {
		of << j;
		for (AgentIDSet::const_iterator i=gra[j].begin();\
			i!=gra[j].end();i++)
			of << '\t' << *i; 
		of << '\n';
	};
};

// Read the graph info from a file.
void DiGraph1::read1(std::ifstream &ifile) {
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

void DiGraph1::read2(std::ifstream &ifile) {
	// Assume that the # of agents are already fixed.
	long nagents=this->show_vertex_size();
	// Erase and make graph with no edges.
	this->new_graph_without_edge(nagents);
	// Add edges.
	AgentID ori, des;
	for (AgentID i=0;i<nagents;i++) {
		ifile >> des;
		if (i!=des) {
			Error::Bad_Input_File badfile;
			throw badfile;
		};
		while (ifile.peek()!='\n') {
			if(ifile >> ori) this->add_edge(ori,des);
		};
	};
};

