// 
// 	Filename : RWtypes.h
//
//	Author : Suhan Ree
//	Date   : 08-25-2003

#ifndef RWTYPES_H
#define RWTYPES_H

// typedef's for the RW project.
#include <vector>
#include <valarray>
#include <set>
#include <map>
#include "Types.h"
#include "Point.h"
#include "RWState.h"
#include "Agent.h"
#include "DiGraph1.h"
#include "DiGraph5.h"
#include "GraphND1.h"

// Agents for RW.
typedef RAgent<RWState> RWAgent;

// Type of agents.
typedef int AgentType;

// A class that defines the "less than" function for the RWAgent.
class RWAgentLessThan {
public :
	inline bool operator() (const RWAgent & a1, const RWAgent & a2) {
		return (a1.get_state().get_pos().x == a2.get_state().get_pos().y ? \
			a1.get_state().get_pos().x < a2.get_state().get_pos().x : \
			a1.get_state().get_pos().y < a2.get_state().get_pos().y);
	};
};

// Vector of agents.
typedef std::vector<RWAgent> AgentVec;

// Set of agents.
typedef std::set<RWAgent,RWAgentLessThan> AgentSet;

// Map of agents.
typedef std::map<AgentID,RWAgent> AgentMap;

// Vector of agent types.
typedef std::vector<AgentType> AgentTypeVec;
// Map of agent types.
typedef std::map<AgentID,AgentType> AgentTypeMap; 

// Type for graphs (for AG, it depends on update_method)
typedef GraphND1 Sgraph;

#endif
