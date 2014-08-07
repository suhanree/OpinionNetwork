// 
// 	Filename : RWRule.h
//
//	Author : Suhan Ree
//	Date   : 09-19-2003

// This file contains classes that define rules for finding dependencies
// between agents (DepRule) and updating each agent (UpdateRule).

// Diagram for the concept is as follows.
//	
//				DepRule
//	A group of	     ------------->	Graph
//	Agent(RWalker)'s     <-------------
//				UpdateRule

#ifndef RWRULE_H
#define RWRULE_H

#include <map>
#include <vector>
#include "Agent.h"
#include "RWState.h"
#include "Graph.h"
#include "GraphND1.h"
#include "Random2.h"
#include "Utilities.h"
#include "Point.h"
#include "RWTypes.h"
#include "RWUtil.h"

// A class defining the dependence rule
// for an abstract dependence, the acquaintance.
// When two agent get closer than (or equal to) "int_range", 
// they get acquainted. (using directional graph).
class RWDepAG {
   public :
	// Constructor.
	RWDepAG(double thres): ag_threshold(thres) {};
	
	// Function that updates the graph using all agents     
	// From ag1 to ag2 (for convenience, we use two graphs).
	void update_graph(AgentMap & amap, const Graph &ag1, \
		Graph &ag2, const Graph &sg);
	void update_graph(AgentVec & avec, const Graph &ag1, \
		Graph &ag2, const Graph &sg);

   protected :
   	double ag_threshold;

   protected :
	RWDepAG() {}; // Hiding the default constructor.
	
};

// A class that defines AG dynamics (using bidirectional graph).
class RWDepAG2 : public RWDepAG {
   public :
	// Constructor.
	RWDepAG2(double thres, unsigned long rs, double ratio): RWDepAG(thres), rng(rs), rewiring_ratio(ratio) {};
	
	// Function that updates the graph using all agents     
	// From ag1 to ag2 (for convenience, we use two graphs).
	void update_graph(AgentMap & amap, const Graph &ag1, \
		Graph &ag2, const Graph &sg);
	void update_graph(AgentVec & avec, const Graph &ag1, \
		Graph &ag2, const Graph &sg);

   protected :
	double rewiring_ratio;
   	Random4 rng;

   private :
	RWDepAG2() {}; // Hiding the default constructor.
};

// A class defining the dependence rule for the space dynamics.
// All agents closer than "int_range" will affect the next state.
class RWDepSG {
   public :
	// Constructor.
	RWDepSG(long d, int nt, const AgentVec &avec);
	
	// Function that updates the graph using all agents     
	void update_graph(AgentMap & amap, const Graph &ag, \
		const Graph &sg1, Graph &sg2);
	void update_graph(AgentVec & avec, const Graph &ag, \
		const Graph &sg1, Graph &sg2);

	// Show the distance.
	short get_int_range() const {
		return int_range;
	};
	// Set the distance.
	void set_int_range(long d) {
		int_range=d;
	};
	
	// print neighbors
	void print_neighbor_states() const {
		Util::print_state(neighbor_states);
	};

	// Print the occupancy information.
	void print_occupancy() const;

   private :
	// Update the occupancy for new postitions.
	void update_occupancy(const AgentMap &amap);
	void update_occupancy(const AgentVec &avec);

	// Find the neighboring agents based on a given position (including myself).
	void find_neighbors(const Point &p);

   	// A function that finds the index from the Point.
	long find_index(const Point &p) {
		return p.x+p.y*Point::get_xsize();
	};

   private :
	// Distance limit that affects other agents.
	long int_range;
	int neighbor_type;
	// Set of neighboring states.
	PointSet neighbor_states;
	// Set of neighbors.
	AgentIDSet neighbors;
	// A vector that contains the occupancy information of the state space.
	// This should be updated whenever an agent changes its state.
	vector<AgentIDSet> occupancy;

   private :
   	RWDepSG() {}; // Hiding default constructor.
};

// A class for the update rule.
class RWUpdate {
   public :
	// Constructor.
	RWUpdate(long speed, int nt, bool sg, long nagents, double thres, PointSet & excluded2);
	RWUpdate(PointSet rel, bool sg, long nagents, double thres, PointSet & excluded2)\
		: rel_trans(rel), sg_effect(sg), ops(nagents), op_threshold(thres), excluded(excluded2) {};

	// Update the all agents and write them.
	void update_agents(AgentMap & amap1, AgentMap &amap2, \
		const Graph &ag, const Graph &sg);
	void update_agents(AgentVec & avec1, AgentVec &avec2, \
		const Graph &ag, const Graph &sg);
	
	// Print the current transition points.
	void print_transitions() {
		Util::print_state(transitions);
	};
	// Print the relative neighboring points.
	void print_rel_trans() {
		Util::print_state(rel_trans);
	};

   protected :
	// Find the next state for an agent.
	RWState next_state(AgentID id, AgentMap & amap, \
		const Graph &ag, const Graph &sg);
	RWState next_state(AgentID id, AgentVec & avec, \
		const Graph &ag, const Graph &sg);
	
	// Find possible transition points for an agent.
	void find_possible_trans(AgentID id, AgentMap & amap, \
		const Graph &ag, const Graph &sg);
	void find_possible_trans(AgentID id, AgentVec & avec, \
		const Graph &ag, const Graph &sg);

	// A function to find the movement of an opinion by other opinions.
	double find_op_movement(double myop, long size);

	// Find the probability distribution for the all possible transitions.
	//	void find_prob_dist();

	// Distance that that an agent can move at once.
	long agent_max_speed;
	int neighbor_type;

	// Set of relative transition points (represented by relative positions)
	PointSet rel_trans;
	
	// Set of points (not relative) that can be used for transition.
	PointSet transitions; 

	// Set of opinions (used as a temporary storage).
	std::valarray<double> ops;
	
	// SG effect is on or off.
	bool sg_effect;

	// Threshold for opinion interactions. For example, if the difference between
	// agent i and j (related via SG) is bigger than this
	// value, the opinion is not affected by each other.
	double op_threshold;

	// Set of points that are excluded from the geometry
	PointSet excluded;

   protected :
   	RWUpdate() {}; // Hiding the default constructor.
};

// A class for the update rule. (plain averaging)
class RWUpdate2 : public RWUpdate {
   public :
	// Constructor.
	RWUpdate2(long speed, int nt,  bool sg, long nagents, double thres, PointSet excluded) \
		: RWUpdate(speed,nt,sg,nagents,thres,excluded) {};
	RWUpdate2(PointSet rel, bool sg, long nagents, double thres, PointSet excluded) \
		: RWUpdate(rel, sg, nagents, thres,excluded) {};

	// Update the all agents and write them.
	void update_agents(AgentMap & amap1, AgentMap &amap2, \
		const Graph &ag, const Graph &sg);
	void update_agents(AgentVec & avec1, AgentVec &avec2, \
		const Graph &ag, const Graph &sg);
	
	// Find the next state for an agent.
	RWState next_state(AgentID id, AgentMap & amap, \
		const Graph &ag, const Graph &sg);
	RWState next_state(AgentID id, AgentVec & avec, \
		const Graph &ag, const Graph &sg);
	
	// A function to find the movement of an opinion by other opinions.
	double find_op_movement(double myop, long size);

   protected :
   	RWUpdate2() {}; // Hiding the default constructor.
};

// A class for the update rule. (Kuromata-like: update_agents, Kuromata: update_agents2
class RWUpdate3 : public RWUpdate2 {
   public :
	// Constructor.
	RWUpdate3(long speed, int nt,  bool sg, long nagents, double thres, PointSet excluded) \
		: RWUpdate2(speed,nt,sg,nagents,thres,excluded) {};
	RWUpdate3(PointSet rel, bool sg, long nagents, double thres, PointSet excluded) \
		: RWUpdate2(rel, sg, nagents, thres,excluded) {};

	// Update the all agents and write them.
	void update_agents(AgentVec & avec1, AgentVec &avec2, \
		const Graph &ag, const Graph &sg);
	void update_agents2(AgentVec & avec1, AgentVec &avec2, \
		const Graph &ag, const Graph &sg);
	
	// Find the next state for an agent.
	RWState next_state(AgentID id, AgentVec & avec, \
		const Graph &ag, const Graph &sg);
	RWState next_state2(AgentID id, AgentVec & avec, \
		const Graph &ag, const Graph &sg);
	
	// A function to find the movement of an opinion by other opinions.
	double find_op_movement(double myop, long size);
	double find_op_movement2(double myop, long size);

   protected :
   	RWUpdate3() {}; // Hiding the default constructor.
};

#endif
