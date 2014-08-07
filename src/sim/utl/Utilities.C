// 
// 	Filename : Utilities.C
//
//	Author : Suhan Ree
//	Date   : 11-28-2002
//
//	Includes utility functions.

#include <iostream>
#include "Utilities.h"

using namespace std;

// Print the vector of class long.
void Util::print_vector(const vector<long> &v) {
	for (vector<long>::const_iterator i=v.begin();i!=v.end();i++)
		cout << *i << ' ';
	cout << endl;
};

void Util::print_vector(const vector<double> &v) {
	for (vector<double>::const_iterator i=v.begin();i!=v.end();i++)
		cout << *i << ' ';
	cout << endl;
};

// Print the list of class long.
void Util::print_list(const list<long> &li) {
	for (std::list<long>::const_iterator i=li.begin();i!=li.end();i++)
		cout << *i << ' ';
	cout << endl;
};

// Print the set of class long
void Util::print_set(const set<long> &s) {
	for (set<long>::const_iterator i=s.begin();i!=s.end();i++)
		cout << *i << ' ';
	cout << endl;
};

// Print the set of class long
void Util::print_set(const set<double> &s) {
	for (set<double>::const_iterator i=s.begin();i!=s.end();i++)
		cout << *i << ' ';
	cout << endl;
};

// Print the map of class long and double.
void Util::print_map(const map<long,double> &m) {
	for (map<long,double>::const_iterator i=m.begin();i!=m.end();i++)
		cout << i->first << ' ' << i->second << endl;
};

// Check if a file exists.
bool Util::if_file(std::string &filename) {
	struct stat file_info;
	return (!stat(filename.c_str(),&file_info));
};

// Combine two graphs (if ag is directed, change it to undirected)
void Util::combine_graphs(GraphND1 &cg, const GraphND1 &sg, const Graph &ag) {
	cg.copy(sg);
	AgentIDSet deps;
	for (AgentID id=0;id<ag.show_vertex_size();id++) {
		ag.find_in_dep(id,deps);
		for (AgentIDSet::const_iterator i=deps.begin();i!=deps.end();i++) {
			cg.add_edge(id,*i);
		};
	};
};
// Find the clustering coefficient for an undirected graph.
double Util::find_clustering_coeff(const GraphND1 &cg) {
	long nagents=cg.show_vertex_size();
	double sum=0;
	for (long id=0;id<nagents;id++) {
		AgentIDSet deps;	// Finding neighbors.
		long degree=cg.find_dep(id,deps);
		long connections;
		if (degree>1) {
			connections=0;
			for (AgentIDSet::const_iterator i=deps.begin();i!=deps.end();i++) {
				AgentIDSet deps2;
				cg.find_dep(*i,deps2);
				for (AgentIDSet::const_iterator j=deps2.begin();j!=deps2.end();j++) {
					// double counting avoided.
					if (*j>*i && deps.find(*j)!=deps.end())
						connections++;
				};
			};
//cout << id << '\t' << degree << '\t' << double(connections)*2.0/(degree*(degree-1)) << endl;
			sum+=double(connections)*2.0/(degree*(degree-1));
		};

	};
	return sum/nagents;
};
// Find the mean distance for an undirected graph.
double Util::find_mean_distance(const GraphND1 &cg, double sample_percentage) {
	long nagents=cg.show_vertex_size();
	long npaths=0;	// Number of paths counted.
	long sum=0;
	long num_try=long((sample_percentage/100)*nagents);
	if (num_try==0) num_try=1;	// num_try should not be zero.
	if (num_try>nagents) num_try=nagents;	// num_try should not be bigger than nagents.

	vector<AgentID> nodes(nagents);
	for (long id=0;id<nagents;id++) 
	  	nodes[id]=id;
	random_shuffle(nodes.begin(),nodes.end());
	for (long i=0; i<num_try; i++) {
		AgentIDSet deps1, deps2;	// Set of agents in a layer.
		AgentIDSet temp_set;	// Temporary set
		AgentIDSet found;	// store the ID's for which the path is already found.

		deps1.insert(nodes[i]); // First layer with the starting node only.
		found.insert(nodes[i]);

		long temp_dist=1;
		while(true) {
			// Find all dependent agents of agents in deps1
			// and insert them in deps2 if not already found.
			for (AgentIDSet::const_iterator j=deps1.begin();\
				j!=deps1.end();j++) {
				if (cg.find_dep(*j,temp_set)!=0) {
//cout << *j << ":"; print_set(temp_set);
					for (AgentIDSet::const_iterator k=temp_set.begin();\
						k!=temp_set.end();k++) {
						if (found.insert(*k).second) {
							deps2.insert(*k);
							npaths++;
							sum+=temp_dist;
//cout << nodes[i] << '\t' << *k << '\t' << temp_dist << endl;
						};
					};
				};
			};
			if (deps2.size()==0) break; // All paths reachable by id has been found
			deps1=deps2;
			deps2.clear();
			temp_dist++;
		};

	};

	if (npaths==0) return 0;
	return double(sum)/npaths;
};
