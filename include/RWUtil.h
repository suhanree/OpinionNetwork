// 
// 	Filename : RWUtil.h
//
//	Author : Suhan Ree
//	Date   : 09-19-2003
//
//	Includes utility functions.

#ifndef RWUTIL_H
#define RWUTIL_H

#include "Graph.h"
#include "Types.h"
#include "RWState.h"
#include "RWTypes.h"
#include <cstdlib>
#include <vector>
#include <string>
#include <set>

namespace Util {

// Calculate the distance between 2 Point2DInt's.
double distance_2DInt(const Point2DInt &p1, const Point2DInt &p2);
double distance_2DInt(const Point2DIntTorus &p1, const Point2DIntTorus &p2);

// Find the relative neighbors given a distance for a Point2DIntTorus.
void find_rel_neighbors(long d, int neighbor_type, PointSet &pset);

// Print the set of class Point2DIntTorus.
void print_state(const PointSet &s);
     
// Print the set of class RWAgent.
void print_agent(const AgentSet &s);

// Print the vector of class RWAgent.
void print_agent(const AgentVec &avec);

// Print the set of class RWAgent from ID's.
void print_agent(const AgentIDSet &s, const AgentMap &m);

// Print the map of RWAgent.
void print_agent(const AgentMap &m);

// Print the information about all agents graphically.
// This function should be used for (xsize, ysize < 30~40).
void print_agent_screen(const AgentVec &avec);

// checking the basic input parameters.
void error_check(long nagents, long xsize, long ysize, double gullibility,\
	double standard_dev, double ag_threshold, double op_threshold,\
	short opinion_topology, short op_init_method,\
	int neighborhood_type_sg, long agent_max_speed, double wiring_prob, long total_time,\
	long num_edges, unsigned long rseed1, unsigned long rseed2, \
	long max_rn);
    
// Initializing a graph. 
// (It is assumed that the vertices have been already added and that there is no self-pointing edge.)
// 	with num_edges : number of edges are given.
//	with wiring_prob : wiring probability for every possible edge is given.
void initialize_graph(Graph &gr, long num_edges, unsigned long rseed);
void initialize_graph(Graph &gr, double wiring_prob, unsigned long rseed);

// Special case of 1-d ring (op_init_method=0).
void initialize_graph0(Graph &gr, long num_edges, int int_range, unsigned long rseed);

// Each agent originates an edge with randomly choosing destination.
void initialize_graph2(Graph &gr, unsigned long rseed);

// Checking positions of agents from a file to find out if some positions are the same.
bool check_agents_pos(AgentVec &avec);

// Initializing states of agents.
// when 0=<gu<=1, gullibility is fixed; gu>1, uniformly random; 
// when -1<gu<0, gaussian with average -gu and standard deviation given.
// When op_init_method=1, opinions are random, when op_init_method=2, opinions are regularly placed.
void initialize_agents_state(AgentVec &avec, short op_init_method, double gullibility, double sd, \
	long geometry, PointSet &excluded);

// Initializing random seed for all agents.
void initialize_agents_seed(AgentVec &avec, unsigned long rseed, long max_rn);

// A function to check the convergence of the system.
//	when convergence_method=1, using the opinions of all agents.
//	when convergence_method=2, using the cluster number of AG.
//	when convergence_method=3, using both.
bool check_convergence(const AgentVec &avec1, const AgentVec &avec2, \
	const Graph1 &ag1, const Graph1 &ag2, int convergence_method);

// A function to find the absolute difference between two opinions when opinions are linear(1) or circular(2).
double find_op_diff(double a, double b, short topology);
// A function to find the difference between two opinions when opinions are linear(1) or circular(2).
double find_op_diff2(double a, double b, short topology);

// Finding groups of opinions based on opinions only
long find_opiniongroups(const AgentVec &final_vec, std::vector<std::multiset<double> > & opiniongroups,\
	short topology, double thres);

// Finding the spread of opinions based on opinions only (using standard deviation from the uniform distribution).
double find_opinionspread(const AgentVec &final_vec, int num_bins);
double find_opinionspread2(const AgentVec &final_vec);

// Find the average diff of opinions between consecutive locations (location-wise)
//	xory=1: x, xory=2: y direction
double find_av_diff(const AgentVec &final_vec, short topology, long meshsize, short xory=1);

// Find the maximum min-max width of p at each x or y.
double find_op_width(const AgentVec &final_vec, short topology, short xory=1);

// Find the average diff of x-location between consecutive opinions
double find_av_diff_p(const AgentVec &final_vec, short topology, long meshsize, double op_thres);

// Change the g value for the given value
void change_g(AgentVec &avec, double gullibility);

}; // End of the namespace.

#endif
