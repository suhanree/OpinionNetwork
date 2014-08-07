// 
// 	Filename : Graph.C
//
//	Author : Suhan Ree
//	Date   : 10-15-2003

#include "Types.h"
#include "Graph.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>

using namespace std;

// Write and print the basic information about the graph.
void Graph::write_summary(ofstream &of) const {
	long vsize=this->show_vertex_size();
	long esize=this->show_edge_size();
	of << vsize << '\t' << esize << '\t';
	of << 2*double(esize)/vsize << '\n';
};

void Graph::print_summary() const {
	long vsize=this->show_vertex_size();
	long esize=this->show_edge_size();
	cout << "Number of vertices: " << vsize << endl;
	cout << "Number of edges: " << esize << endl;
	cout << "Average degree: " << 2*double(esize)/vsize << endl;
};
	
// Assignment function.
void Graph1::copy(const Graph &gr) {
	this->clear();
	this->new_graph_without_edge(gr.show_vertex_size());
	nedges=gr.show_edge_size();
	for (AgentID i=0;i<nvertices;i++) {
		AgentIDSet deps;
		gr.find_in_dep(i,deps);
		gra[i]=deps;
	};
};

// Clear and make a new graph with N vertices with no edges.
void Graph1::new_graph_without_edge(long n) {
	this->clear();
	AgentIDSet aset;
	for (AgentID i=0;i<n;i++) gra.push_back(aset);
	nvertices=n;
	nedges=0;
};

// Find the set of vertices.
void Graph1::find_vertices(AgentIDSet &vertexset) const {
	vertexset.clear();
	for (long i=0; i<gra.size(); i++) vertexset.insert(i);
};
		     
// Clearing all vetices and edges.
void Graph1::clear() {
	for (long i=0; i<gra.size();i++) gra[i].clear();
	gra.clear();
	nvertices=0;
	nedges=0;
};
	
// Clearing all edges only.
void Graph1::clear_edges() {
	for (long i=0; i<gra.size();i++) gra[i].clear();
	nedges=0;
};

// Find the clusters of the graph.
// (Returns the number of clusters.)
long Graph1::find_clusters(vector<AgentIDSet> &clusters) const {
	AgentIDSet searched;	// Set of agents that are already searched.
	AgentIDSet deps1, deps2;	// Set of agents in a layer.
	AgentIDSet temp_set1, temp_set2;	// Temporary sets.

	for (AgentID id=0;id<nvertices;id++) { // Since the vertices are fixed.
		if (searched.find(id)==searched.end()) {
			temp_set1.insert(id); // Set of agents in this cluster.
			deps1=temp_set1;
			bool all;	// true if all agents of the cluster are found.
			do {
				all=true;
				// Find all dependent agents of agents in deps1
				// and insert them in deps2.
				for (AgentIDSet::const_iterator i=deps1.begin();\
					i!=deps1.end();i++)
					if (searched.insert(*i).second && find_dep(*i,temp_set2)!=0)
						for (AgentIDSet::const_iterator j=temp_set2.begin();\
							j!=temp_set2.end();j++) {
							deps2.insert(*j);
							// Find if all dependent agents are 
							// already in the cluster.
							if (temp_set1.insert(*j).second)
								all=false;
						};
				deps1=deps2;
				deps2.clear();
			} while (!all);
			clusters.push_back(temp_set1);
			temp_set1.clear();
		};
	};
	return clusters.size();
};
	
/*

// Assignment function.
void Graph2::copy(const Graph &gr) {
	this->clear();
	this->new_graph_without_edge(gr.show_vertex_size());
	nedges=gr.show_edge_size();
	for (AgentID i=0;i<nvertices;i++) {
		AgentIDMap deps;
		gr.find_in_dep(i,deps);
		gra[i]=deps;
	};
};

// Clear and make a new graph with N vertices with no edges.
void Graph2::new_graph_without_edge(long n) {
	this->clear();
	AgentIDMap amap;
	for (AgentID i=0;i<n;i++) gra.push_back(amap);
	nvertices=n;
	nedges=0;
};

// Find the set of vertices.
void Graph2::find_vertices(AgentIDSet &vertexset) const {
	vertexset.clear();
	for (long i=0; i<gra.size(); i++) vertexset.insert(i);
};

// Clearing all vetices and edges.
void Graph2::clear() {
	for (long i=0; i<gra.size();i++) gra[i].clear();
	gra.clear();
	nvertices=0;
	nedges=0;
};

// Clearing all edges only.
void Graph2::clear_edges() {
	for (long i=0; i<gra.size();i++) gra[i].clear();
	nedges=0;
};

// Find the clusters of the graph.
// (Returns the number of clusters.)
long Graph2::find_clusters(vector<AgentIDSet> &clusters) const {
	return 1;
};

// Assignment function.
void Graph3::copy(const Graph &gr) {
	this->clear();
	AgentIDSet vertexset;
	gr.find_vertices(vertexset);
	nvertices=gr.show_vertex_size();
	nedges=gr.show_edge_size();
	for (AgentIDSet::const_iterator i=vertexset.begin();i!=vertexset.end();i++) {
		AgentIDSet deps;
		gr.find_in_dep(*i,deps);
		gra[*i]=deps;
	};
};

// Clear and make a new graph with N vertices with no edges.
void Graph3::new_graph_without_edge(long n) {
	this->clear();
	AgentIDSet aset;
	for (AgentID i=0;i<n;i++) gra[i]=aset;
	nedges=n;
	nvertices=n;
	nedges=0;
};

// Find the set of vertices.
void Graph3::find_vertices(AgentIDSet &vertexset) const {
	vertexset.clear();
	for (map<AgentID,AgentIDSet>::const_iterator i=gra.begin(); i!=gra.end();\
		i++) 
		vertexset.insert(i->first);
};

// Clearing all vetices and edges.
void Graph3::clear() {
	for (map<AgentID,AgentIDSet>::iterator i=gra.begin(); i!=gra.end();\
		i++) 
		(i->second).clear();
	gra.clear();
	nvertices=0;
	nedges=0;
};

// Clearing all edges only.
void Graph3::clear_edges() {
	for (map<AgentID,AgentIDSet>::iterator i=gra.begin(); i!=gra.end();\
		i++) 
		(i->second).clear();
	nedges=0;
};

// Find the clusters of the graph.
// (Returns the number of clusters.)
long Graph3::find_clusters(vector<AgentIDSet> &clusters) const {
	return 1;
};

// Assignment function.
void Graph4::copy(const Graph &gr) {
	this->clear();
	AgentIDSet vertexset;
	gr.find_vertices(vertexset);
	nvertices=gr.show_vertex_size();
	nedges=gr.show_edge_size();
	for (AgentIDSet::const_iterator i=vertexset.begin();i!=vertexset.end();i++) {
		AgentIDMap deps;
		gr.find_in_dep(*i,deps);
		gra[*i]=deps;
	};
};

// Clear and make a new graph with N vertices with no edges.
void Graph4::new_graph_without_edge(long n) {
	this->clear();
	AgentIDMap amap;
	for (AgentID i=0;i<n;i++) gra[i]=amap;
	nvertices=n;
	nedges=0;
};

// Find the set of vertices.
void Graph4::find_vertices(AgentIDSet &vertexset) const {
	vertexset.clear();
	for (map<AgentID,AgentIDMap>::const_iterator i=gra.begin(); i!=gra.end();\
		i++) 
		vertexset.insert(i->first);
};

// Clearing all vetices and edges.
void Graph4::clear() {
	for (map<AgentID,AgentIDMap>::iterator i=gra.begin(); i!=gra.end();\
		i++) 
		(i->second).clear();
	gra.clear();
	nvertices=0;
	nedges=0;
};

// Clearing all edges only.
void Graph4::clear_edges() {
	for (map<AgentID,AgentIDMap>::iterator i=gra.begin(); i!=gra.end();\
		i++) 
		(i->second).clear();
	nedges=0;
};

// Find the clusters of the graph.
// (Returns the number of clusters.)
long Graph4::find_clusters(vector<AgentIDSet> &clusters) const {
	return 1;
};

*/
