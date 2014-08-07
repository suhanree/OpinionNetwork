// 
// 	Filename : RWRule.C
//
//	Author : Suhan Ree
//	Date   : 06-24-2004

#include <set>
#include <map>
#include <cmath>
#include "RWRule.h"
#include "RWUtil.h"
#include "RWErrors.h"
#include "Agent.h"
#include "Point.h"
#include "RWState.h"
#include "Graph.h"
#include "Random2.h"
#include "RWTypes.h"
#include "Utilities.h"

// Function that updates the graph using all agents     
void RWDepAG::update_graph(AgentMap &amap, const Graph &ag1, \
	Graph &ag2, const Graph &sg) {
	ag2.copy(ag1);
	AgentIDSet idset_in_sg,idset_out_ag;

	// For each agent,
	for (AgentMap::iterator i=amap.begin();i!=amap.end();i++) {

		// Find all agents pointing to me (using SG).
		long num_dep=sg.find_in_dep(i->first,idset_in_sg);
		if (num_dep<1) continue; // No sg-dependant agent, so continue.

		// Find all agents pointed by me (using AG).
		// It was assumed that I can only change the destination of my own edge.
		long num_dep2=ag1.find_out_dep(i->first,idset_out_ag);
		if (num_dep2<1) continue; // No edge to change, so continue. 

		// For all sg-dependant agents and ag-dependent agents,
		// find the opinions, and store the info into two vectors.
		AgentID closest_id=*(idset_in_sg.begin());
		AgentID farthest_id=*(idset_out_ag.begin());
		double closest_diff=0.5; // To make the initial diff. farther than any value.
		double farthest_diff=0.0; // To make the initial diff. closer than any value.
		double diff;
		double my_op=(i->second).get_state().get_op();

		for (AgentIDSet::const_iterator j=idset_in_sg.begin();j!=idset_in_sg.end();\
			j++)
			if ((diff=Util::find_op_diff(amap[*j].get_state().get_op(),my_op,RWState::get_op_topology()))<closest_diff) {
				closest_diff=diff;
				closest_id=*j;
			};
		for (AgentIDSet::const_iterator j=idset_out_ag.begin();j!=idset_out_ag.end();\
			j++)
			if ((diff=Util::find_op_diff(amap[*j].get_state().get_op(),my_op,RWState::get_op_topology()))>farthest_diff) {
				farthest_diff=diff;
				farthest_id=*j;
			};
		if (farthest_diff>ag_threshold && farthest_diff>closest_diff && \
			(idset_out_ag.find(closest_id)==idset_out_ag.end()))
			// Add an edge to the closest, and remove the edge to the farthest.
			if (ag2.add_edge(i->first,closest_id))	
				ag2.remove_edge(i->first,farthest_id);
	};
};

void RWDepAG::update_graph(AgentVec & avec, const Graph &ag1, \
	Graph &ag2, const Graph &sg) {
	ag2.copy(ag1);
	AgentIDSet idset_in_sg, idset_out_ag;
	long nagents=avec.size();

	// For each agent,
	for (AgentID i=0;i<nagents;i++) {

		// Find all agents pointing to me (using SG).
		long num_dep=sg.find_in_dep(i,idset_in_sg);
		if (num_dep<1) continue; // No sg-dependant agent, so continue.

		// Find all agents pointed by me (using AG).
		// It was assumed that I can only change the destination of my own edge.
		long num_dep2=ag1.find_out_dep(i,idset_out_ag);
		if (num_dep2<1) continue; // No edge to change, so continue. 

		// For all sg-dependant agents and ag-dependent agents,
		// find the opinions, and store the info into two vectors.
		AgentID closest_id=*(idset_in_sg.begin());
		AgentID farthest_id=*(idset_out_ag.begin());
		double closest_diff=1.0; // To make the initial diff. farther than any value.
		double farthest_diff=0.0; // To make the initial diff. closer than any value.
		double diff;
		double my_op=avec[i].get_state().get_op();

		for (AgentIDSet::const_iterator j=idset_in_sg.begin();j!=idset_in_sg.end();\
			j++)
			if ((diff=Util::find_op_diff(avec[*j].get_state().get_op(),my_op,RWState::get_op_topology()))<closest_diff) {
				closest_diff=diff;
				closest_id=*j;
			};
		for (AgentIDSet::const_iterator j=idset_out_ag.begin();j!=idset_out_ag.end();\
			j++)
			if ((diff=Util::find_op_diff(avec[*j].get_state().get_op(),my_op,RWState::get_op_topology()))>farthest_diff) {
				farthest_diff=diff;
				farthest_id=*j;
			};
		if (farthest_diff>ag_threshold && farthest_diff>closest_diff && \
			(idset_out_ag.find(closest_id)==idset_out_ag.end()))
			// Add an edge to the closest, and remove the edge to the farthest.
			if (ag2.add_edge(i,closest_id))	
				ag2.remove_edge(i,farthest_id);
	};
};

// RWDepAG2 (using bidirectional graphs)
void RWDepAG2::update_graph(AgentMap &amap, const Graph &ag1, \
	Graph &ag2, const Graph &sg) { // undefined yet.
	ag2.copy(ag1);
};

void RWDepAG2::update_graph(AgentVec & avec, const Graph &ag1, \
	Graph &ag2, const Graph &sg) {
	ag2.copy(ag1);
	AgentIDSet idset_in_sg, idset_out_ag;
	long nagents=avec.size();

	long count=0;
	if (rewiring_ratio<double(1)/nagents) return;	// if rewiring_ratio*nagents<1, do nothing.
	do { // repeat picking an agent randomly for nagents*rewiring_ratio times.
		// For a randomly-picked agent,
		AgentID i=rng.ndraw(0,nagents-1);
	
		// Find all agents pointing to me (using SG).
		long num_dep=sg.find_in_dep(i,idset_in_sg);
		if (num_dep<1) continue; // No sg-dependant agent, so return.
	
		// Find all agents pointed by me (using AG).
		// It was assumed that I can only change the destination of my own edge.
		long num_dep2=ag2.find_out_dep(i,idset_out_ag);
		if (num_dep2<1) continue; // No edge to change, so return. 
	
		// For all sg-dependant agents and ag-dependent agents,
		// find the opinions, and store the info into two vectors.
		AgentID closest_id=*(idset_in_sg.begin());
		AgentID farthest_id=*(idset_out_ag.begin());
		double closest_diff=1.0; // To make the initial diff. farther than any value.
		double farthest_diff=0.0; // To make the initial diff. closer than any value.
		double diff;
		double my_op=avec[i].get_state().get_op();
	
		for (AgentIDSet::const_iterator j=idset_in_sg.begin();j!=idset_in_sg.end();\
			j++)
			if ((diff=Util::find_op_diff(avec[*j].get_state().get_op(),my_op,RWState::get_op_topology()))<closest_diff) {
				closest_diff=diff;
				closest_id=*j;
			};
		for (AgentIDSet::const_iterator j=idset_out_ag.begin();j!=idset_out_ag.end();\
			j++)
			if ((diff=Util::find_op_diff(avec[*j].get_state().get_op(),my_op,RWState::get_op_topology()))>farthest_diff) {
				farthest_diff=diff;
				farthest_id=*j;
			};
		if (farthest_diff>ag_threshold && farthest_diff>closest_diff && \
			(idset_out_ag.find(closest_id)==idset_out_ag.end()))
			// Add an edge to the closest, and remove the edge to the farthest.
			if (ag2.add_edge(i,closest_id))	{
				ag2.remove_edge(i,farthest_id);
			};
	} while (++count<=nagents*rewiring_ratio);
};
     
// RWDepSG Constructor
RWDepSG::RWDepSG(long d, int nt, const AgentVec &avec): int_range(d), neighbor_type(nt) {
	if (neighbor_type<0 || neighbor_type>5 || neighbor_type==2 || neighbor_type==4) {
		Error::NeighborTypeError err("Check neighbor_type_sg.");
		throw err;
	};
	Util::find_rel_neighbors(int_range,neighbor_type,neighbor_states);
	long state_size=Point::get_xsize()*Point::get_ysize();
	occupancy.resize(state_size);
	long size=avec.size();
	for (AgentID id=0;id<size;id++) {
		long i=find_index(avec[id].get_state().get_pos());
		occupancy[i].insert(id);
	};
};

// Function that updates the graph using all agents     
void RWDepSG::update_graph(AgentMap & amap, const Graph &ag, \
	const Graph &sg1, Graph &sg2) {
	update_occupancy(amap); // occupancy should be updated based on new amap.
	sg2.clear_edges();
	long num=amap.size(); // # of agents.
	Point current;
	for (AgentMap::const_iterator i=amap.begin();i!=amap.end();i++) {
		current=(i->second).get_state().get_pos();
		// Find the neighboring agents (within int_range)
		find_neighbors(current);
		// Add edges for all neighbors found.
		for (AgentIDSet::const_iterator j=neighbors.begin(); \
			j!=neighbors.end();j++)
			sg2.add_edge(*j,i->first);
	};
};

void RWDepSG::update_graph(AgentVec & avec, const Graph &ag, \
	const Graph &sg1, Graph &sg2) {
	update_occupancy(avec); // occupancy should be updated based on new avec.
	sg2.clear_edges();
	long num=avec.size(); // # of agents.
	Point current;
	for (AgentID id=0;id<num;id++) {
		current=avec[id].get_state().get_pos();
		// Find the neighboring agents (within int_range)
		find_neighbors(current);
		// Add edges for all neighbors found.
		for (AgentIDSet::const_iterator i=neighbors.begin(); \
			i!=neighbors.end();i++)
			sg2.add_edge(*i,id);
	};
};

// Update the occupancy.
void RWDepSG::update_occupancy(const AgentMap &amap) {
	// Delete the occupancy information first.
	long state_size=occupancy.size();
	for (long i=0;i<state_size;i++)
		occupancy[i].clear();
	// Then, re-find the occupancy information from amap.
	long size=amap.size();
	for (AgentMap::const_iterator i=amap.begin();i!=amap.end();i++)
		occupancy[find_index((i->second).get_state().get_pos())].insert(i->first);
};

void RWDepSG::update_occupancy(const AgentVec &avec) {
	// Delete the occupancy information first.
	long state_size=occupancy.size();
	for (long i=0;i<state_size;i++)
		occupancy[i].clear();
	// Then, re-find the occupancy information from avec.
	long size=avec.size();
	for (AgentID id=0;id<size;id++)
		occupancy[find_index(avec[id].get_state().get_pos())].insert(id);
};

// Find the neighboring agents based on a given state.
void RWDepSG::find_neighbors(const Point &p) {
	neighbors.clear();
	long index;
	for (PointSet::const_iterator i=neighbor_states.begin(); \
		i!=neighbor_states.end();i++) {
		Point p1=p+(*i);
		if (p1.if_inside()) {
			index=find_index(p+(*i));
			for (AgentIDSet::const_iterator j=occupancy[index].begin();\
				j!=occupancy[index].end();j++) 
				neighbors.insert(*j);
		};
	};
};

// Print the occupancy information.
void RWDepSG::print_occupancy() const {
	long size=occupancy.size();
	long xsize=Point::get_xsize();
	for (long i=0;i<size;i++) {
		cout << '(' << i%xsize << ',' << i/xsize << "): ";
		Util::print_set(occupancy[i]);
	};
}; 

//Constructor for the RWUpdate class/
RWUpdate::RWUpdate(long speed, int nt, bool sg, long nagents, double thres, PointSet &excluded2) \
	: agent_max_speed(speed), neighbor_type(nt), sg_effect(sg), ops(nagents), op_threshold(thres), excluded(excluded2) {
	if (neighbor_type<1 || neighbor_type>4) {
		Error::NeighborTypeError err("Check neighbor_type_movement.");
		throw err;
	};
	Util::find_rel_neighbors(agent_max_speed,neighbor_type,rel_trans);
};

// Update the all agents and write them to "amap2".
void RWUpdate::update_agents(AgentMap & amap1, AgentMap &amap2, \
		const Graph &ag, const Graph &sg) {
	// Assumes that agents are not created nor removed during the simulation.
	for (AgentMap::const_iterator i=amap1.begin();i!=amap1.end();i++) {
		// Find the possible transition points.
		find_possible_trans(i->first,amap1,ag,sg);
		// Roll the dice to find the next position, find the new opinion,
		// and assign the new state.
		amap2[i->first].update(next_state(i->first,amap1,ag,sg), \
			(i->second).get_rng());
	};	
};

// Update the all agents and write them to "avec2".
void RWUpdate::update_agents(AgentVec & avec1, AgentVec &avec2, \
	const Graph &ag, const Graph &sg) {
	// Assumes that agents are not created nor removed during the simulation.
	for (AgentID id=0;id<avec1.size();id++) {
		// Find the possible transition points.
		find_possible_trans(id,avec1,ag,sg);
		// Roll the dice to find the next position, find the new opinion,
		// and assign the new state.
		RWState st=next_state(id,avec1,ag,sg);
		avec2[id].update(st,avec1[id].get_rng());
	};	
};
	
// Find the next state of an agent.
RWState RWUpdate::next_state(AgentID id, AgentMap & amap, \
		const Graph &ag, const Graph &sg) {
	RWState st(amap[id].get_state());
	double op(amap[id].get_state().get_op());
	double gu(amap[id].get_state().get_gu());
	long x,y;

	// Update the opinion of an agent.
	AgentIDSet deps_ag_in, deps_ag_out, deps_sg;
	long dep_out_size=ag.find_out_deg(id);

	long i=0;
	if (ag.find_in_dep(id,deps_ag_in)>0)
		for (AgentIDSet::const_iterator j=deps_ag_in.begin();j!=deps_ag_in.end();j++)
			ops[i++]=amap[*j].get_state().get_op();

	if (sg_effect && sg.find_dep(id,deps_sg)>0) {
		//ag.find_out_dep(id,deps_ag_out);
		//for (AgentIDSet::const_iterator j=deps_sg.begin();\
		//	j!=deps_sg.end();j++)
		//	if (deps_ag_out.find(*j)==deps_ag_out.end())
		//		deps_out_size++;
		for (AgentIDSet::const_iterator j=deps_sg.begin();j!=deps_sg.end();j++) {
			double opinion=amap[*j].get_state().get_op();
			if ((Util::find_op_diff(opinion,op,RWState::get_op_topology()) < op_threshold) \
				&& deps_ag_in.find(*j)==deps_ag_in.end())
				ops[i++]=opinion;
		};
	};

	if (i>0) {
		double movement=find_op_movement(op,i);
		op+=gu*movement/(1.0+dep_out_size);
		while (op>1.0) op--;
		while (op<0.0) op++;
		st.update_op(op);
	};
	
	// Update the position of an agent.
	long size=transitions.size();
	if (size==0)
		return st;
	else if (size==1) {
		x=(*(transitions.begin())).x;
		y=(*(transitions.begin())).y;
		st.update_pos(x,y);
		return st;
	}
	else {
		PointVec pvec(size);
		int i=0;
		for (PointSet::const_iterator j=transitions.begin();\
			j!=transitions.end();j++,i++)
			pvec[i]=*j;
		// Assuming the equal probability for all possible transitions.
		int draw=amap[id].ndraw(0,size-1);
		x=pvec[draw].x;
		y=pvec[draw].y;
		st.update_pos(x,y);
		return st;
	};
};

RWState RWUpdate::next_state(AgentID id, AgentVec & avec, \
	const Graph &ag, const Graph &sg) {
	RWState st(avec[id].get_state());
	double op(avec[id].get_state().get_op());
	double gu(avec[id].get_state().get_gu());
	long x,y;

	// Update the opinion of an agent.
	AgentIDSet deps_ag_in, deps_ag_out, deps_sg;
	long dep_out_size=ag.find_out_deg(id);

	long i=0;
	if (ag.find_in_dep(id,deps_ag_in)>0)
		for (AgentIDSet::const_iterator j=deps_ag_in.begin();j!=deps_ag_in.end();j++)
			ops[i++]=avec[*j].get_state().get_op();

	if (sg_effect && sg.find_dep(id,deps_sg)>0) {
		//ag.find_out_dep(id,deps_ag_out);
		//for (AgentIDSet::const_iterator j=deps_sg.begin();\
		//	j!=deps_sg.end();j++)
		//	if (deps_ag_out.find(*j)==deps_ag_out.end())
		//		deps_out_size++;
		for (AgentIDSet::const_iterator j=deps_sg.begin();j!=deps_sg.end();j++) {
			double opinion=avec[*j].get_state().get_op();
			if ((Util::find_op_diff(opinion,op,RWState::get_op_topology()) < op_threshold) \
				&& deps_ag_in.find(*j)==deps_ag_in.end())
				ops[i++]=opinion;
		};
	};
	if (i>0) {
		double movement=find_op_movement(op,i);
		op+=gu*movement/(1.0+dep_out_size);
		while (op>1.0) op--;
		while (op<0.0) op++;
		st.update_op(op);
	};
	// Update the position of an agent.
	long size=transitions.size();
	if (size==0)
		return st;
	else if (size==1) {
		x=(*(transitions.begin())).x;
		y=(*(transitions.begin())).y;
		st.update_pos(x,y);
		return st;
	}
	else {
		PointVec pvec(size);
		int i=0;
		for (PointSet::const_iterator j=transitions.begin();\
			j!=transitions.end();j++,i++)
			pvec[i]=*j;
		// Assuming the equal probability for all possible transitions.
		int draw=avec[id].ndraw(0,size-1);
		x=pvec[draw].x;
		y=pvec[draw].y;
		st.update_pos(x,y);
		return st;
	};
};

// Find possible transition points.
void RWUpdate::find_possible_trans(AgentID id, AgentMap & amap, \
	const Graph &ag, const Graph &sg) {
	transitions.clear();
	// Find possible transition points from the state.
	for (PointSet::const_iterator i=rel_trans.begin();\
		i!=rel_trans.end();i++) {
		Point p=amap[id].get_state().get_pos()+*i;
		if (p.if_inside())
			if (excluded.size()==0 || excluded.find(p)==excluded.end())
				transitions.insert(p);
	};
};
				
void RWUpdate::find_possible_trans(AgentID id, AgentVec & avec, \
	const Graph &ag, const Graph &sg) {
	transitions.clear();
	// Find possible transition points from the state.
	for (PointSet::const_iterator i=rel_trans.begin();\
		i!=rel_trans.end();i++) {
		Point p=avec[id].get_state().get_pos()+*i;
		if (p.if_inside())
			if (excluded.size()==0 || excluded.find(p)==excluded.end())
				transitions.insert(p);
	};
};

// A function to find the movement of an opinion by other opinions.
double RWUpdate::find_op_movement(double myop, long size) {
	double temp1, temp2=0.0;
	for (long i=0;i<size;i++) {
		temp1=ops[i]-myop;
		if (RWState::get_op_topology()==2) {
			if (temp1>0.5) temp2+=temp1-1.0;
			else if (temp1>-0.5) temp2+=temp1;
			else
				temp2+=temp1+1.0;
		}
		else {
			temp2+=temp1;
		};
	};
	return temp2/size;
};

// Update the all agents and write them to "amap2".
void RWUpdate2::update_agents(AgentMap & amap1, AgentMap &amap2, \
		const Graph &ag, const Graph &sg) {
	// Assumes that agents are not created nor removed during the simulation.
	for (AgentMap::const_iterator i=amap1.begin();i!=amap1.end();i++) {
		// Find the possible transition points.
		find_possible_trans(i->first,amap1,ag,sg);
		// Roll the dice to find the next position, find the new opinion,
		// and assign the new state.
		amap2[i->first].update(next_state(i->first,amap1,ag,sg), \
			(i->second).get_rng());
	};	
};

// Update the all agents and write them to "avec2".
void RWUpdate2::update_agents(AgentVec & avec1, AgentVec &avec2, \
	const Graph &ag, const Graph &sg) {
	// Assumes that agents are not created nor removed during the simulation.
	for (AgentID id=0;id<avec1.size();id++) {
		// Find the possible transition points.
		find_possible_trans(id,avec1,ag,sg);
		// Roll the dice to find the next position, find the new opinion,
		// and assign the new state.
		RWState st=next_state(id,avec1,ag,sg);
		avec2[id].update(st,avec1[id].get_rng());
	};	
};
	
// Find the next state of an agent.
RWState RWUpdate2::next_state(AgentID id, AgentMap & amap, \
		const Graph &ag, const Graph &sg) {
	RWState st(amap[id].get_state());
	double op(amap[id].get_state().get_op());
	double gu(amap[id].get_state().get_gu());
	long x,y;

	// Update the opinion of an agent.
	AgentIDSet deps_ag_in, deps_ag_out, deps_sg;
	long dep_out_size=ag.find_out_deg(id);

	long i=0;
	if (ag.find_in_dep(id,deps_ag_in)>0)
		for (AgentIDSet::const_iterator j=deps_ag_in.begin();j!=deps_ag_in.end();j++)
			ops[i++]=amap[*j].get_state().get_op();

	if (sg_effect && sg.find_dep(id,deps_sg)>0) {
		//ag.find_out_dep(id,deps_ag_out);
		//for (AgentIDSet::const_iterator j=deps_sg.begin();\
		//	j!=deps_sg.end();j++)
		//	if (deps_ag_out.find(*j)==deps_ag_out.end())
		//		deps_out_size++;
		for (AgentIDSet::const_iterator j=deps_sg.begin();j!=deps_sg.end();j++) {
			double opinion=amap[*j].get_state().get_op();
			if ((Util::find_op_diff(opinion,op,RWState::get_op_topology()) < op_threshold) \
				&& deps_ag_in.find(*j)==deps_ag_in.end())
				ops[i++]=opinion;
		};
	};

	if (i>0) {
		double movement=find_op_movement(op,i);
		op+=gu*movement/(1.0+dep_out_size);
		while (op>1.0) op--;
		while (op<0.0) op++;
		st.update_op(op);
	};
	
	// Update the position of an agent.
	long size=transitions.size();
	if (size==0)
		return st;
	else if (size==1) {
		x=(*(transitions.begin())).x;
		y=(*(transitions.begin())).y;
		st.update_pos(x,y);
		return st;
	}
	else {
		PointVec pvec(size);
		int i=0;
		for (PointSet::const_iterator j=transitions.begin();\
			j!=transitions.end();j++,i++)
			pvec[i]=*j;
		// Assuming the equal probability for all possible transitions.
		int draw=amap[id].ndraw(0,size-1);
		x=pvec[draw].x;
		y=pvec[draw].y;
		st.update_pos(x,y);
		return st;
	};
};

RWState RWUpdate2::next_state(AgentID id, AgentVec & avec, \
	const Graph &ag, const Graph &sg) {
	RWState st(avec[id].get_state());
	double op(avec[id].get_state().get_op());
	double gu(avec[id].get_state().get_gu());
	long x,y;

	// Update the opinion of an agent.
	AgentIDSet deps_ag_in, deps_ag_out, deps_sg;
	long dep_out_size=ag.find_out_deg(id);

	long i=0;
	if (ag.find_in_dep(id,deps_ag_in)>0)
		for (AgentIDSet::const_iterator j=deps_ag_in.begin();j!=deps_ag_in.end();j++) {
			double opinion=avec[*j].get_state().get_op();
			if (Util::find_op_diff(opinion,op,RWState::get_op_topology()) < op_threshold)
				ops[i++]=opinion;
		};

	if (sg_effect && sg.find_dep(id,deps_sg)>0) {
		//ag.find_out_dep(id,deps_ag_out);
		//for (AgentIDSet::const_iterator j=deps_sg.begin();\
		//	j!=deps_sg.end();j++)
		//	if (deps_ag_out.find(*j)==deps_ag_out.end())
		//		deps_out_size++;
		for (AgentIDSet::const_iterator j=deps_sg.begin();j!=deps_sg.end();j++) {
			double opinion=avec[*j].get_state().get_op();
			if ((Util::find_op_diff(opinion,op,RWState::get_op_topology()) < op_threshold) \
				&& deps_ag_in.find(*j)==deps_ag_in.end())
				ops[i++]=opinion;
		};
	};

	if (i>0) {
		double movement=find_op_movement(op,i);
		//op+=gu*movement/(1.0+dep_out_size);
		op+=gu*movement;
		while (op>1.0) op--;
		while (op<0.0) op++;
		st.update_op(op);
	};
	// Update the position of an agent.
	long size=transitions.size();
	if (size==0)
		return st;
	else if (size==1) {
		x=(*(transitions.begin())).x;
		y=(*(transitions.begin())).y;
		st.update_pos(x,y);
		return st;
	}
	else {
		PointVec pvec(size);
		int i=0;
		for (PointSet::const_iterator j=transitions.begin();\
			j!=transitions.end();j++,i++)
			pvec[i]=*j;
		// Assuming the equal probability for all possible transitions.
		int draw=avec[id].ndraw(0,size-1);
		x=pvec[draw].x;
		y=pvec[draw].y;
		st.update_pos(x,y);
		return st;
	};
};

// A function to find the movement of an opinion by other opinions.
double RWUpdate2::find_op_movement(double myop, long size) {
	double temp1, temp2=0.0;
	for (long i=0;i<size;i++) {
		temp1=ops[i]-myop;
		if (RWState::get_op_topology()==2) {
			if (temp1>0.5) temp2+=temp1-1.0;
			else if (temp1>-0.5) temp2+=temp1;
			else
				temp2+=temp1+1.0;
		}
		else {
			temp2+=temp1;
		};
	};
	if (temp2<1e-15 && temp2>-1e-15) return 0;
	return temp2/(1+size);
};

// Update the all agents and write them to "avec2".
void RWUpdate3::update_agents(AgentVec & avec1, AgentVec &avec2, \
	const Graph &ag, const Graph &sg) {
	// Assumes that agents are not created nor removed during the simulation.
	for (AgentID id=0;id<avec1.size();id++) {
		// Find the possible transition points.
		find_possible_trans(id,avec1,ag,sg);
		// Roll the dice to find the next position, find the new opinion,
		// and assign the new state.
		RWState st=next_state(id,avec1,ag,sg);
		avec2[id].update(st,avec1[id].get_rng());
	};	
};
	
// Find the next state of an agent.
RWState RWUpdate3::next_state(AgentID id, AgentVec & avec, \
	const Graph &ag, const Graph &sg) {
	RWState st(avec[id].get_state());
	double op(avec[id].get_state().get_op());
	double gu(avec[id].get_state().get_gu());
	long x,y;

	// Update the opinion of an agent.
	AgentIDSet deps_ag_in, deps_ag_out, deps_sg;
	long dep_out_size=ag.find_out_deg(id);

	long i=0;
	if (ag.find_in_dep(id,deps_ag_in)>0)
		for (AgentIDSet::const_iterator j=deps_ag_in.begin();j!=deps_ag_in.end();j++) {
			double opinion=avec[*j].get_state().get_op();
			if (Util::find_op_diff(opinion,op,RWState::get_op_topology()) < op_threshold)
				ops[i++]=opinion;
		};

	if (sg_effect && sg.find_dep(id,deps_sg)>0) {
		//ag.find_out_dep(id,deps_ag_out);
		//for (AgentIDSet::const_iterator j=deps_sg.begin();\
		//	j!=deps_sg.end();j++)
		//	if (deps_ag_out.find(*j)==deps_ag_out.end())
		//		deps_out_size++;
		for (AgentIDSet::const_iterator j=deps_sg.begin();j!=deps_sg.end();j++) {
			double opinion=avec[*j].get_state().get_op();
			if ((Util::find_op_diff(opinion,op,RWState::get_op_topology()) < op_threshold) \
				&& deps_ag_in.find(*j)==deps_ag_in.end())
				ops[i++]=opinion;
		};
	};

	if (i>0) {
		double movement=find_op_movement(op,i);
		//op+=gu*movement/(1.0+dep_out_size);
		op+=gu*movement;
		while (op>1.0) op--;
		while (op<0.0) op++;
		st.update_op(op);
	};
	// Update the position of an agent.
	long size=transitions.size();
	if (size==0)
		return st;
	else if (size==1) {
		x=(*(transitions.begin())).x;
		y=(*(transitions.begin())).y;
		st.update_pos(x,y);
		return st;
	}
	else {
		PointVec pvec(size);
		int i=0;
		for (PointSet::const_iterator j=transitions.begin();\
			j!=transitions.end();j++,i++)
			pvec[i]=*j;
		// Assuming the equal probability for all possible transitions.
		int draw=avec[id].ndraw(0,size-1);
		x=pvec[draw].x;
		y=pvec[draw].y;
		st.update_pos(x,y);
		return st;
	};
};

// A function to find the movement of an opinion by other opinions.
double RWUpdate3::find_op_movement(double myop, long size) {
	double temp1, temp2=0.0;
	for (long i=0;i<size;i++) {
		temp1=ops[i]-myop;
		if (RWState::get_op_topology()==2) {
			if (temp1>0.75) temp2+=temp1-1.0;
			else if (temp1>0.25) temp2+=0.5-temp1;
			else if (temp1>-0.25) temp2+=temp1;
			else if (temp1>-0.75) temp2+=-0.5-temp1;
			else
				temp2+=temp1+1.0;
		}
		else {
			temp2+=temp1;
		};
	};
	if (temp2<1e-15 && temp2>-1e-15) return 0;
	else return temp2/(1+size);
};

// Update the all agents and write them to "avec2".
void RWUpdate3::update_agents2(AgentVec & avec1, AgentVec &avec2, \
	const Graph &ag, const Graph &sg) {
	// Assumes that agents are not created nor removed during the simulation.
	for (AgentID id=0;id<avec1.size();id++) {
		// Find the possible transition points.
		find_possible_trans(id,avec1,ag,sg);
		// Roll the dice to find the next position, find the new opinion,
		// and assign the new state.
		RWState st=next_state2(id,avec1,ag,sg);
		avec2[id].update(st,avec1[id].get_rng());
	};	
};
	
// Find the next state of an agent.
RWState RWUpdate3::next_state2(AgentID id, AgentVec & avec, \
	const Graph &ag, const Graph &sg) {
	RWState st(avec[id].get_state());
	double op(avec[id].get_state().get_op());
	double gu(avec[id].get_state().get_gu());
	long x,y;

	// Update the opinion of an agent.
	AgentIDSet deps_ag_in, deps_ag_out, deps_sg;
	long dep_out_size=ag.find_out_deg(id);

	long i=0;
	if (ag.find_in_dep(id,deps_ag_in)>0)
		for (AgentIDSet::const_iterator j=deps_ag_in.begin();j!=deps_ag_in.end();j++) {
			double opinion=avec[*j].get_state().get_op();
			if (Util::find_op_diff(opinion,op,RWState::get_op_topology()) < op_threshold)
				ops[i++]=opinion;
		};

	if (sg_effect && sg.find_dep(id,deps_sg)>0) {
		//ag.find_out_dep(id,deps_ag_out);
		//for (AgentIDSet::const_iterator j=deps_sg.begin();\
		//	j!=deps_sg.end();j++)
		//	if (deps_ag_out.find(*j)==deps_ag_out.end())
		//		deps_out_size++;
		for (AgentIDSet::const_iterator j=deps_sg.begin();j!=deps_sg.end();j++) {
			double opinion=avec[*j].get_state().get_op();
			if ((Util::find_op_diff(opinion,op,RWState::get_op_topology()) < op_threshold) \
				&& deps_ag_in.find(*j)==deps_ag_in.end())
				ops[i++]=opinion;
		};
	};

	if (i>0) {
		double movement=find_op_movement2(op,i);
		//op+=gu*movement/(1.0+dep_out_size);
		op+=gu*movement;
		while (op>1.0) op--;
		while (op<0.0) op++;
		st.update_op(op);
	};
	// Update the position of an agent.
	long size=transitions.size();
	if (size==0)
		return st;
	else if (size==1) {
		x=(*(transitions.begin())).x;
		y=(*(transitions.begin())).y;
		st.update_pos(x,y);
		return st;
	}
	else {
		PointVec pvec(size);
		int i=0;
		for (PointSet::const_iterator j=transitions.begin();\
			j!=transitions.end();j++,i++)
			pvec[i]=*j;
		// Assuming the equal probability for all possible transitions.
		int draw=avec[id].ndraw(0,size-1);
		x=pvec[draw].x;
		y=pvec[draw].y;
		st.update_pos(x,y);
		return st;
	};
};

// A function to find the movement of an opinion by other opinions.
double RWUpdate3::find_op_movement2(double myop, long size) {
	double temp1, temp2=0.0;
	const double pi=4.0*atan(1.0);
	for (long i=0;i<size;i++) {
		temp1=ops[i]-myop;
		temp2+=sin(2*pi*temp1)/(2*pi);
//cout << ops[i] << '\t' << myop << '\t' << 2*pi*temp1 << '\t' << temp2 << endl;
//cout << temp2/(1+size) << endl;
	};
	if (temp2<1e-15 && temp2>-1e-15) return 0;
	else return temp2/(1+size);
};
