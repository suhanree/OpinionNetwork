// 
// 	Filename : RWOut.C
//
//	Author : Suhan Ree
//	Date   : 08-25-2003

#include "RWOut.h"
#include "RWTypes.h"
#include "Types.h"
#include "Graph.h"
#include "GraphND1.h"
#include <fstream>
#include <map>
 
// Initializing the static value.
std::string RWOut::noout="noout";

// Write the information about an agent.
void RWOut::write_agent(AgentID id, const AgentMap &amap, const Graph1 & ag, const Sgraph &sg, long time) {
	if (time>=0) ofile << time << '\t';
	ofile << id << '\t';
	AgentMap::const_iterator i=amap.find(id);
	if (i!=amap.end()) i->second.write(ofile);
};

void RWOut::write_agent(AgentID id, const AgentVec &avec, const Graph1 & ag, const Sgraph &sg, long time) {
	if (time>=0) ofile << time << '\t';
	long nagents=avec.size();
	if (id>=0 && id<nagents) {
		if (time>=0) ofile << time << '\t';
		ofile << id << '\t';
		avec[id].write(ofile);
		AgentIDSet dep_ag, dep_sg;
		ag.find_in_dep(id,dep_ag);
		sg.find_in_dep(id,dep_sg);
		ofile << "   AG:";
		for (AgentIDSet::const_iterator i=dep_ag.begin();i!=dep_ag.end();i++)
			ofile << '\t' << *i << '(' << avec[*i].get_state().get_op() << ')';
		ofile << "\n   SG:";
		for (AgentIDSet::const_iterator i=dep_sg.begin();i!=dep_sg.end();i++)
			ofile << '\t' << *i << '(' << avec[*i].get_state().get_op() << ')';
		ofile << '\n';
	};
};

// Write the information about given agents.
void RWOut::write_all_agents(const AgentMap &amap, long time) {
	if (time<0) return;
	for (AgentMap::const_iterator i=amap.begin(); i!=amap.end();i++) {
		ofile << time << '\t';
		ofile << i->first << '\t';
		i->second.write(ofile);
	};
};

void RWOut::write_all_agents(const AgentVec &avec, long time) {
	if (time<0) return;
	for (AgentID i=0;i<avec.size();i++) {
		ofile << time << '\t';
		ofile << i << '\t';
		avec[i].write(ofile);
	};

};

