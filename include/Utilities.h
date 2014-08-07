// 
// 	Filename : Utilities.h
//
//	Author : Suhan Ree
//	Date   : 11-28-2002
//
//	Includes utility functions.

#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <list>
#include <set>
#include <map>
#include <string>
#include <sys/stat.h>

#include "Point.h"
#include "Types.h"
#include "GraphND1.h"
#include "DiGraph1.h"

namespace Util {

// Print the vector of class long.
void print_vector(const std::vector<long> &v);
void print_vector(const std::vector<double> &v);

// Print the list of class long.
void print_list(const std::list<long> &li);

// Print the set of class long.
void print_set(const std::set<long> &s);
     
// Print the set of class long.
void print_set(const std::set<double> &s);
     
// Print the map of class long and double.
void print_map(const std::map<long,double> &m);

// Check if a file exists.
bool if_file(std::string &filename);

// Combine two graphs (if ag is directed, then change it to undirected)
void combine_graphs(GraphND1 &cg, const GraphND1 &sg, const Graph &ag);
// Find the clustering coefficient for an undirected graph.
double find_clustering_coeff(const GraphND1 &cg);
// Find the mean distance for an undirected graph.
double find_mean_distance(const GraphND1 &cg, double sample_percentage=100);
}; // End of the namespace.

#endif
