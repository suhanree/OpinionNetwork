// 
// 	Filename : RWIn.C
//
//	Author : Suhan Ree
//	Date   : 08-25-2003

#include "RWIn.h"

#include <string>
#include <map>
#include "RWIn.h"
#include "Input.h"
#include "Agent.h"
#include "RWState.h"
#include "RWTypes.h"
#include "Errors.h"

#ifndef MAX_CHARS
#define MAX_CHARS 1000
#endif
									   
// Read the RWAgent info from the file.
void RWIn::read_all_agents(AgentMap &amap) {
	amap.clear();
	AgentID id;
	RWState st;
	long nagents=amap.size();
	char tmpstr[MAX_CHARS+1];
	long line=1;
	do {
		// This only gives each agent its state.
		// The random seed will be still needed,
		// so the set_seed function should be used.
		if(ifile.peek()!='#' && read(id)) {
			if(!st.read(ifile)) {
				Error::Bad_Input_Value er(this->get_filename(),line);
				throw er;
			};
			amap[id].update_state(st);
		};
		line++;
	} while (ifile.getline(tmpstr, MAX_CHARS, '\n'));
	if (line-2!=nagents) {
		Error::Bad_Input_File er(this->get_filename(), "Check the number of agents!");
		throw er;
	};
};

void RWIn::read_all_agents(AgentVec &avec) {
	AgentID id;
	RWState st;
	long nagents=avec.size();
	char tmpstr[MAX_CHARS+1];
	long line=1;
	do {
		// This only gives each agent its state.
		// The random seed will be still needed,
		// so the set_seed function should be used.
		if(ifile.peek()!='#' && read(id)) {
			if(!st.read(ifile)) {
				Error::Bad_Input_Value er(this->get_filename(),line);
				throw er;
			};
			if (id<nagents) avec[id].update_state(st);
		};
		line++;
	} while (ifile.getline(tmpstr, MAX_CHARS, '\n'));
	if (line-2!=nagents) {
		Error::Bad_Input_File er(this->get_filename(), "Check the number of agents!");
		throw er;
	};
};
