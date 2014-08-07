// 
// 	Filename : RWState.C
//
//	Author : Suhan Ree
//	Date   : 06-04-2004
//
//	For the RW2 problem: each agent has an opinion (0<x<1) and gullibility (0<=g<=1).

#include "RWState.h"

using namespace std;

// Initializing the opinion topology (static variable).
short RWState::opinion_topology=1;

// outstream operator overloading for RWState.
ostream & operator<<(ostream &s, const RWState &st) {
	return s << '(' << st.get_pos().x << ',' << st.get_pos().y << ")\t" \
		<< st.get_op() << '\t' << st.get_gu();
};

