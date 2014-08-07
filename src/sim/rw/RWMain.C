// 
// 	Filename : RWMain.C
//
//	Author : Suhan Ree
//	Date   : 09-23-2003

#include "RWMain.h"
#include "Random1.h"
#include "Random2.h"
#include "Discrete.h"
#include "Utilities.h"
#include "Types.h"
#include "GraphND1.h"
#include "DiGraph1.h"
#include "Graph.h"
#include "Agent.h"
#include "Input.h"
#include "InputParam.h"
#include "Output.h"
#include "Clock.h"
#include "Errors.h"
#include "Point.h"
#include "RWState.h"
#include "RWRule.h"
#include "RWIn.h"
#include "RWOut.h"
#include "RWUtil.h"
#include "RWTypes.h"
#include "RWErrors.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <list>
#include <set>
#include <map>


int main(int argc, char **argv) {

	using namespace std;

	
	// Command line input test.
	if (argc!=2) {
		cerr << " Usage: RWSim <input filename>\n";
		exit(1);
	};
	// Input filename in a string.
	string infile(argv[1]);

	//===============================================================
	//=================(Input Parameters)============================
	AgentID nagents;
	long xsize;
	long ysize;
	long geometry=1;
	string in_excluded_file;
	PointSet excluded;
	double ag_threshold;
	double op_threshold=0.5;
	short opinion_topology=2;
	short op_init_method=1;
	double gullibility;
	double standard_dev=0.1;
	long int_range=0;
	int neighbor_type_sg=0;
	long agent_max_speed=1;
	int neighbor_type_movement=1;
	long update_method=1;
	long total_time;

	unsigned long rseed1=1;
	unsigned long rseed2=1;
	long max_rn=1000;
	int convergence_method=1;
	long convergence_check_period=10;
	long convergence_out_period=10;

	bool if_snapshot_out=false;
	string out_snapshot_file;
	long out_snapshot_interval=1;

	bool if_ag_snapshot_out=false;
	string out_ag_snapshot_file;
	int out_ag_snapshot_method=0;
	long out_ag_snapshot_interval=1;

	bool if_sg_snapshot_out=false;
	string out_sg_snapshot_file;
	int out_sg_snapshot_method=0;
	long out_sg_snapshot_interval=1;

	bool if_agent_out=false;
	AgentID agent_id;
	string out_agent_file;
	long out_agent_interval=1;

	bool if_summary_out=false;
	string out_summary_file;

	bool if_network_stat_out=false;
	long out_network_stat_time=-1;
	bool if_components_out=false;
	string out_components_file;

	bool if_agraph_in=false;
	string in_agraph_file;
	short in_agraph_file_format=1;
	short in_agraph_method=0;
	long num_edges;
	double wiring_prob;

	bool if_agents_in=false;
	string in_agents_file;

	//===============================================================
	//==============(Reading Input Parameters)=======================
	cout << "1, Reading the input parameters..." << endl;
	InputParam in1(infile);
	in1.read();
	// in1.print_key_val();
	if (!in1.get("nagents",nagents,cerr)) {
		cerr << "# No parameter given: nagents \n";
		cerr << endl;
		exit(1);
	};
	if (!in1.get("xsize",xsize,cerr)) {
		cerr << "# No parameter given: xsize \n";
		exit(1);
	};
	if (!in1.get("ysize",ysize,cerr)) {
		cerr << "# No parameter given: ysize \n";
		exit(1);
	};
	if (!in1.get("geometry",geometry,cerr)) {
		cerr << "# No parameter given: geometry.";
		cerr << " Default value 1 (regular) will be used.\n";
	};
	if (geometry==2 && \
		!in1.get("in_excluded_file",in_excluded_file,cerr)) {
		cerr << "# No parameter given: in_excluded_file \n";
		exit(1);
	};
	if (!in1.get("gullibility",gullibility,cerr)) {
		cerr << "# No parameter given: gullibility \n";
		exit(1);
	};
	if (gullibility<-epsilon && !in1.get("standard_dev",standard_dev,cerr)) {
		cerr << "# No parameter given: standard_dev \n";
		exit(1);
	};
	if (!in1.get("ag_threshold",ag_threshold,cerr)) {
		ag_threshold=1.0/nagents;
		cerr << "# No parameter given: ag_threshold";
		cerr << ". Default value, 1/nagents=" << ag_threshold;
		cerr << ",  will be used.\n";
	};
	if (!in1.get("op_threshold",op_threshold,cerr)) {
		cerr << "# No parameter given: op_threshold";
		cerr << ". Default value, 0.5" << op_threshold;
		cerr << ",  will be used.\n";
	};
	//if (!in1.get("sg_effect",sg_effect,cerr)) {
	//	cerr << "# No parameter given: sg_effect";
	//	cerr << ". Default value, false, will be used.\n";
	//};
	if (!in1.get("opinion_topology",opinion_topology,cerr)) {
		cerr << "# No parameter given: opinion_topology";
		cerr << ". Default value 2 (circular) will be used.\n";
	};
	if (!in1.get("op_init_method",op_init_method,cerr)) {
		cerr << "# No parameter given: op_init_method";
		cerr << ". Default value 1 (random) will be used.\n";
	};
	if (!in1.get("neighbor_type_sg",neighbor_type_sg,cerr)) {
		cerr << "# No parameter given: neighbor_type_sg";
		cerr << ". Default value 0 (no SG effect) will be used.\n";
	};
	if (!in1.get("int_range",int_range,cerr)) {
		cerr << "# No parameter given: int_range";
		cerr << ". Default value 0 will be used.\n";
	};
	if (!in1.get("agent_max_speed",agent_max_speed,cerr)) {
		cerr << "# No parameter given: agent_max_speed";
		cerr << ". Default value 1 will be used.\n";
	};
	if (!in1.get("neighbor_type_movement",neighbor_type_movement,cerr)) {
		cerr << "# No parameter given: neighbor_type_movement";
		cerr << ". Default value 1 (von Neumann+center) will be used.\n";
	};
	if (!in1.get("update_method",update_method,cerr)) {
		cerr << "# No parameter given: update_method";
		cerr << ". Default value 2 (new) will be used.\n";
	};
	if (!in1.get("total_time",total_time,cerr)) {
		cerr << "# No parameter given: total_time \n";
		exit(1);
	};
	double drseed1, drseed2, dmax=2147483647;
	if (!in1.get("rseed1",drseed1,cerr)) {
		cerr << "# No parameter given: rseed1";
		cerr << ". Default value, " << rseed1 << ", will be used.\n";
	}
	else {
		if (drseed1 < 0) drseed1=-drseed1;
		rseed1=(unsigned long) (drseed1-dmax*((unsigned long) (drseed1/dmax))+0.5);
	};
	if (!in1.get("rseed2",drseed2,cerr)) {
		cerr << "# No parameter given: rseed2";
		cerr << ". Default value, " << rseed2 << ", will be used.\n";
	}
	else {
		if (drseed2 < 0) drseed2=-drseed2;
		rseed2=(unsigned long) (drseed2-dmax*((unsigned long) (drseed2/dmax))+0.5);
	};
	if (!in1.get("max_rn",max_rn,cerr)) {
		cerr << "# No parameter given: max_rn";
		cerr << ". Default value, " << max_rn << ", will be used.\n";
	};
	if (!in1.get("convergence_method",convergence_method,cerr)) {
		cerr << "# No parameter given: convergence_method";
		cerr << ". Default value, 1, will be used.\n";
	};
	if (convergence_method && !in1.get("convergence_check_period",convergence_check_period,cerr)) {
		convergence_check_period=xsize*ysize;
		cerr << "# No parameter given: convergence_check_period.\n";
		cerr << "  Default value, xsize*ysize=" << convergence_check_period;
		cerr << ", will be used.\n";
	};
	if (convergence_method>3 && !in1.get("convergence_out_period",convergence_out_period,cerr)) {
		convergence_out_period=convergence_check_period;
		cerr << "# No parameter given: convergence_out_period.\n";
		cerr << "  Default value, convergence_out_period, " << convergence_check_period;
		cerr << ", will be used.\n";
	};
	if (!in1.get("if_snapshot_out",if_snapshot_out,cerr)) {
		cerr << "# No parameter given: if_snapshot_out";
		cerr << ". Default value, false, will be used.\n";
	};
	if (if_snapshot_out && \
		!in1.get("out_snapshot_file",out_snapshot_file,cerr)) {
		cerr << "# No parameter given: out_snapshot_file \n";
		exit(1);
	};
	if (if_snapshot_out && !in1.get("out_snapshot_interval", \
		out_snapshot_interval,cerr)) {
		cerr << "# No parameter given: out_snapshot_interval";
		cerr << ". Default value 1 will be used.\n";
	};
	if (!in1.get("if_ag_snapshot_out",if_ag_snapshot_out,cerr)) {
		cerr << "# No parameter given: if_ag_snapshot_out";
		cerr << ". Default value, false, will be used.\n";
	};
	if (if_ag_snapshot_out && !in1.get("out_ag_snapshot_file",\
		out_ag_snapshot_file,cerr)) {
		cerr << "# No parameter given: out_ag_snapshot_file \n";
		exit(1);
	};
	if (if_ag_snapshot_out && !in1.get("out_ag_snapshot_method",\
		out_ag_snapshot_method,cerr)) {
		cerr << "# No parameter given: out_ag_snapshot_method";
		cerr << ". Default value 0 will be used.\n";
	};
	if (if_ag_snapshot_out && !in1.get("out_ag_snapshot_interval",\
		out_ag_snapshot_interval,cerr)) {
		cerr << "# No parameter given: out_ag_snapshot_interval";
		cerr << ". Default value 1 will be used.\n";
	};
	if (!in1.get("if_sg_snapshot_out",if_sg_snapshot_out,cerr)) {
		cerr << "# No parameter given: if_sg_snapshot_out";
		cerr << ". Default value, false, will be used.\n";
	};
	if (if_sg_snapshot_out && !in1.get("out_sg_snapshot_file",\
		out_sg_snapshot_file,cerr)) {
		cerr << "# No parameter given: out_sg_snapshot_file \n";
		exit(1);
	};
	if (if_sg_snapshot_out && !in1.get("out_sg_snapshot_method",\
		out_sg_snapshot_method,cerr)) {
		cerr << "# No parameter given: out_sg_snapshot_method";
		cerr << ". Default value 0 will be used.\n";
	};
	if (if_sg_snapshot_out && !in1.get("out_sg_snapshot_interval",\
		out_sg_snapshot_interval,cerr)) {
		cerr << "# No parameter given: out_sg_snapshot_interval";
		cerr << ". Default value 1 will be used.\n";
	};
	if (!in1.get("if_agent_out",if_agent_out,cerr)) {
		cerr << "# No parameter given: if_agent_out";
		cerr << ". Default value, false, will be used.\n";
	};
	if (if_agent_out && !in1.get("agent_id",agent_id,cerr)) {
		cerr << "# No parameter given: agent_id \n";
		exit(1);
	};
	if (if_agent_out && !in1.get("out_agent_file",out_agent_file,cerr)) {
		cerr << "# No parameter given: out_agent_file \n";
		exit(1);
	};
	if (if_agent_out && !in1.get("out_agent_interval",\
		out_agent_interval,cerr)) {
		cerr << "# No parameter given: out_agent_interval";
		cerr << ". Default value 1 will be used.\n";
	};
	if (!in1.get("if_summary_out",if_summary_out,cerr)) {
		cerr << "# No parameter given: if_summary_out";
		cerr << ". Default value, false, will be used.\n";
	};
	if (if_summary_out && !in1.get("out_summary_file",\
		out_summary_file,cerr)) {
		cerr << "# No parameter given: out_summary_file \n";
		exit(1);
	};
	if (if_summary_out && !in1.get("if_network_stat_out",if_network_stat_out,cerr)) {
		cerr << "# No parameter given: if_network_stat_out";
		cerr << ". Default value, false, will be used.\n";
	};
	if (if_summary_out && if_network_stat_out && !in1.get("out_network_stat_time",\
		out_network_stat_time,cerr)) {
		cerr << "# No parameter given: out_network_stat_time";
		cerr << ". Default value, -1, will be used.\n";
	};
	if (if_summary_out && if_network_stat_out && !in1.get("if_components_out",if_components_out,cerr)) {
		cerr << "# No parameter given: if_components_out";
		cerr << ". Default value, false, will be used.\n";
	};
	if (if_summary_out && if_network_stat_out && if_components_out && !in1.get("out_components_file",\
		out_components_file,cerr)) {
		cerr << "# No parameter given: out_components_file \n";
		exit(1);
	};
	if (!in1.get("if_agraph_in",if_agraph_in,cerr)) {
		if_agraph_in=false;
		cerr << "# No parameter given: in_agraph_in.";
		cerr << "  Default value, false, will be used.\n";
	};
	if (if_agraph_in) {
		if (in1.get("in_agraph_file",in_agraph_file,cerr)) {
			if (!Util::if_file(in_agraph_file)) {
				cerr << "# File, " << in_agraph_file << ", doesn't exist.";
				cerr << "  AG will be created randomly.\n";
				if_agraph_in=false;
			};
		}
		else {
			cerr << "# No parameter given: in_agraph_file.";
			cerr << "  AG will be created randomly.\n";
			if_agraph_in=false;
		};
	};
	if (if_agraph_in && !in1.get("in_agraph_file_format",in_agraph_file_format,cerr)) {
		cerr << "# No parameter given: in_agraph_file_format.";
		cerr << "  Default value, 1, will be used.\n";
	};
	if (!if_agraph_in && !in1.get("num_edges",num_edges,cerr)) {
		cerr << "# No parameter given: num_edges \n";
		exit(1);
	};
	if (!in1.get("wiring_prob",wiring_prob,cerr) && ((!if_agraph_in && num_edges<0) || update_method>=3)) {
		cerr << "# No parameter given: wiring_prob \n";
		exit(1);
	};
	if (!if_agraph_in && !in1.get("in_agraph_method",in_agraph_method,cerr)) {
		cerr << "# No parameter given: in_agraph_method \n";
		exit(1);
	};
	if (!in1.get("if_agents_in",if_agents_in,cerr)) {
		if_agents_in=false;
		cerr << "# No parameter given: in_agents_in.";
		cerr << "  Default value, false, will be used.\n";
	};
	if (if_agents_in) {
		if (in1.get("in_agents_file",in_agents_file,cerr)) {
			if (!Util::if_file(in_agents_file)) {
				cerr << "# File, " << in_agents_file << ", doesn't exist.";
				cerr << "  Agents will be created randomly.\n";
				if_agents_in=false;
			};
		}
		else {
			cerr << "# No parameter given: in_agents_file.";
			cerr << "  Agents will be created randomly.\n";
			if_agents_in=false;
		};
	};
	
	// close the input parameter file.
	in1.close();

	// Checking values of basic input parameters
	Util::error_check(nagents,xsize,ysize,gullibility,standard_dev,\
		ag_threshold, op_threshold,opinion_topology,op_init_method,neighbor_type_sg,agent_max_speed,\
		(!if_agraph_in && num_edges<0 ? wiring_prob : 0.5),total_time,\
		(if_agraph_in ? 0 : num_edges),rseed1,rseed2,max_rn);

	cout << "\tNumber of agents: " << nagents << endl;

	// Assigning the size of the grid.
	if (geometry==0) { // special case of 1d ring.
		xsize=nagents;
		ysize=1;
		gullibility=1;
		neighbor_type_sg=1;
		agent_max_speed=0;
		neighbor_type_movement=1;
		cout << "\tSpecial case of 1D ring with no agent movement." << endl;
	};
	Point::set_size(xsize,ysize); 
	cout << "\tGrid size: " << Point::get_xsize() << " and " << Point::get_ysize() << endl;
	if (geometry==2) {
		std::ifstream ifile;
		ifile.open(in_excluded_file.c_str(),ios::in);
		if (!ifile) {
			cerr << "# Error: Input file, " << in_excluded_file;
			cerr << ", doesn't exist.\n";
			exit(1);
		};
		long x, y;
		while (ifile >> x >> y && x>=0 && x<xsize && y>=0 && y<ysize) excluded.insert(Point(x,y));
		ifile.close();
		cout << "\t(Total of " << excluded.size() << " points will be excluded.)" << endl;
	};


	bool sg_effect=false;
	if (neighbor_type_sg>0) sg_effect=true;
	if (sg_effect) {
		cout << "\tSG effect on opinion values is on with the ";
		cout << "threshold, " << op_threshold << endl;
		cout << "\tInteraction range for agents: " << int_range << ", neighbor type: ";
		cout << neighbor_type_sg << endl;
	};
	cout << "\tNum of steps an agent can move in a timestep: "\
		<< agent_max_speed << ", movement type: ";
	cout << neighbor_type_movement << endl;
	cout << "\tUpdate_method: " << update_method << endl;
	// Assigning the maximum number of random numbers for RWAgent.
	RWAgent::set_max_ran(max_rn);
	cout << "\tMax num of random numbers each agent can use: " << max_rn << endl;
	cout << "\tRandom seed for agents, rseed1: " << rseed1 << endl;
	if (!if_agraph_in) 
		cout << "\tRandom seed for the whole system, rseed2: " \
		<< rseed2 << endl;
	cout << "   Done." << endl; 
	//==============================================================
	//=============(Setting Up : Initialization)====================
	cout << "2, Initializing state variables and AG..." << endl;
   try {
	// Dynamical values for the simulations (AG, SG, Agents)
	// Each entity has one more copy for effective computations.
	// Graph (AG, abstract) directional or bidirectional
	GraphND1 ag1b(nagents), ag2b(nagents);
	DiGraph1 ag1d(nagents), ag2d(nagents);
	Graph1 *pag1=&ag1d, *pag2=&ag2d;
	if (update_method>=3) {
		pag1=&ag1b;
		pag2=&ag2b;
	};
	Graph1 &ag1=*pag1, &ag2=*pag2;

	// Graph (SG, state induced) bidirectional
	Sgraph sg1(nagents), sg2(nagents), cg(nagents); // cg: for AG+SG 
	// all RWAgent's (using vector)
	AgentVec avec1(nagents), avec2(nagents); 

	cout << "\tCreated AG(graph), SG(graph), and agents vector for ";
	cout << nagents << " agents."<< endl;
	
	// Set the topology of the opinion space.
	RWState::set_op_topology(opinion_topology);
	cout << "\tThe topology of the opinion space is ";
	if (opinion_topology==1) 
		cout << "linear."<< endl;
	else 
		cout << "circular."<< endl;

	// Reading inputs from files or randomly.
	// AG and Agents need initialization.
	// AG initialization.
	if (if_agraph_in) {
		Input in2(in_agraph_file);
		switch (in_agraph_file_format) {
		   case 1:
			in2.read_graph(ag1);
			if (nagents != ag1.show_vertex_size()) {
				cerr << "# Check the number of vertices in file, ";
				cerr << in_agraph_file << '\n';
				exit(1);
			};
			break;
		   case 2:
			in2.read_graph2(ag1);
			break;
		   default:
			cerr << "# Check the parameter: in_agraph_file_format. ";
			cerr << "The value should be either 1 or 2. ";
			exit(1);
		};
		cout << "\tInitialized AG(graph) from the file, " << in_agraph_file << endl;
	}
	else
		switch (in_agraph_method) {
		   case 0:
			if (num_edges>0) {
				if (geometry==0) 
					Util::initialize_graph0(ag1,num_edges,int_range,rseed2); //special case of 1d ring
				else
					Util::initialize_graph(ag1,num_edges,rseed2);
				cout << "\tInitialized AG(graph) randomly with ";
				cout << num_edges << " edges." << endl;
			}
			else if (num_edges==0) { // Do nothing
				cout << "\tAG(graph) doesn't exist because there is no";
				cout << " edge." << endl;
			}
			else {
				Util::initialize_graph(ag1,wiring_prob,rseed2);
				cout << "\tInitialized AG(graph) randomly with ";
				cout << "probability " << wiring_prob << '.' << endl;
			};
			break;
		   case 1:
			Util::initialize_graph2(ag1,rseed2);
			cout << "\tInitialized AG(graph) (having one edge per vertex)";
			cout << " randomly." << endl;
			break;
		   default:
		   	break;
		};
	bool if_ag_update=true;
	if (ag_threshold<-1.0e-10 || ag_threshold>(opinion_topology==1?0.9999:0.4999)) if_ag_update=false;
	// Copying ag1 to ag2 when ag doesn't need updating.
	if (!if_ag_update) ag2.copy(ag1);	

	// Agents initialization.
	if (geometry==0) max_rn=1; // Special case of 1d ring: no agent movement.
	Util::initialize_agents_seed(avec1,rseed1,max_rn);
	cout << "\tRandom seeds for all agents are initialized." << endl;
	if (if_agents_in) {
		RWIn in3(in_agents_file); // agents initial conditions
		//in3.read_all_agents(avec1,occupancy);
		in3.read_all_agents(avec1);
		if (nagents != avec1.size()) {
			cerr << "# Check the number of agents in file, ";
			cerr << in_agents_file << '\n';
			exit(1);
		};
		if (gullibility>0 || gullibility<1+epsilon) // change gullibility for all agents to the given value.
			Util::change_g(avec1, gullibility);
			
		cout << "\tInitialized " << nagents;
		cout << " agents from the file, " << in_agents_file << endl;
	}
	else {
		Util::initialize_agents_state(avec1,op_init_method,gullibility,standard_dev,geometry,excluded);
		cout << "\tInitialized " << nagents << " agents ";
		cout << "randomly with the ";
		if (gullibility<-epsilon) 
			cout << "gullibilities with gaussian distribution.\n" \
				<< "\t\tThe average is " << -gullibility \
				<< " and the standard deviation is " << standard_dev \
				<< ' ';
		else if (gullibility>1.0+epsilon)
			cout << "uniformly random gullibilities ";
		else
			cout << "gullibility, " << gullibility << ' ';
		if (op_init_method==1) cout << "(random opinions)." << endl;
		else cout << "(regular opinions)." << endl;
	};
	
	cout << "   Done." << endl;

	//===============================================================
	//=============(Simultion: Time Evolution)=======================
	
	cout << "3, Simulation starting..." << endl;

	// clock class object.
	Clock cl(0);

	// Classes that defines how to update dependences, AG and SG.
	RWDepAG ag_rule(ag_threshold);
	RWDepAG2 ag_rule2(ag_threshold, rseed2+1,wiring_prob);
	RWDepSG sg_rule(int_range,neighbor_type_sg,avec1);

	// Class that defines how to update the agents.
	RWUpdate avec_rule1(agent_max_speed,neighbor_type_movement,sg_effect,nagents,op_threshold,excluded); // divided by size
	RWUpdate2 avec_rule2(agent_max_speed,neighbor_type_movement,sg_effect,nagents,op_threshold,excluded); // divided by (1+size), plain averaging
	RWUpdate3 avec_rule3(agent_max_speed,neighbor_type_movement,sg_effect,nagents,op_threshold,excluded); // divided by (1+size), sine-like averaging

	// Finding SG from avec and ag (and previous SG not needed).
	sg_rule.update_graph(avec1,ag1,sg2,sg1);

	// Will print the time information with the interval given below.
	const long print_interval=(total_time/100>0 ? total_time/100 : 1);

	// Initializing output files if necessary.
	// A string named "RWOut::noout" will be used when there will be no outputs.
	RWOut agents_out(if_snapshot_out ? out_snapshot_file : RWOut::noout);
	RWOut agents_out_p(if_snapshot_out && convergence_method>3 ? out_snapshot_file+'p' : RWOut::noout); //Additional information on period
	RWOut ag_out(if_ag_snapshot_out ? out_ag_snapshot_file : RWOut::noout);
	RWOut sg_out(if_sg_snapshot_out ? out_sg_snapshot_file : RWOut::noout);
	RWOut one_agent_out(if_agent_out ? out_agent_file : RWOut::noout);
	RWOut summary_out(if_summary_out ? out_summary_file : RWOut::noout);
	
	// Will be used for convergence check.
	long conv_time=-1;

	// References to keep track of the final ag and avec written to the file.
	Graph1 &final_ag=ag1;
	Sgraph &final_sg=sg1;
	AgentVec &final_avec=avec1;

	// Time evolution (alternate between 1 and 2 variables)
	// We have two copies (1 and 2) for each vairable.
	// When time is even, copy 1 will evolve into copy 2, and
	// when time is odd, copy 2 will evolve into copy 1.
	do {
		long current_time=cl.get();
		// First check if the time is even or odd.
		bool odd=current_time%2;
		// If odd, 2->1, if even, 1->2.
		Graph1 &bef_ag=(odd ? ag2 : ag1);
		Graph1 &aft_ag=(odd ? ag1 : ag2);
		AgentVec &bef_avec=(odd ? avec2 : avec1);
		AgentVec &aft_avec=(odd ? avec1 : avec2);
		Sgraph &bef_sg=(odd ? sg2 : sg1);
		Sgraph &aft_sg=(odd ? sg1 : sg2);

		// Keep track of the final avec and final ag for the summary.
		final_avec=bef_avec;
		final_ag=bef_ag;
		final_sg=bef_sg;

		// Printing the time info after every print_interval.
		cl.print(print_interval);
		
		// Writing outputs to files if necessary (writing if time=0).
		if(if_snapshot_out && ((current_time==0 || current_time==total_time) || (out_snapshot_interval \
			&& cl.interval(out_snapshot_interval)))) {
			agents_out.write_all_agents(bef_avec,cl.get());
		};
		if(if_ag_snapshot_out && ((current_time==0 || current_time==total_time) || (out_ag_snapshot_interval \
			&& cl.interval(out_ag_snapshot_interval)))) {
			ag_out.write("T\t");
			ag_out.write(cl.get()); // writing the current time
			ag_out.write('\n');
			switch (out_ag_snapshot_method) {
				case 1:
					ag_out.write_graph1(bef_ag);
					break;
				case 2:
					ag_out.write_graph2(bef_ag);
					break;
				default:
					ag_out.write_graph1(bef_ag);
					break;
			};
		};
		if(if_sg_snapshot_out && ((current_time==0 || current_time==total_time) || (out_sg_snapshot_interval \
			&& cl.interval(out_sg_snapshot_interval)))) {
			sg_out.write("T\t");
			sg_out.write(cl.get()); // writing the current time
			sg_out.write('\n');
			switch (out_sg_snapshot_method) {
				case 1:
					sg_out.write_graph1(bef_sg);
					break;
				case 2:
					sg_out.write_graph2(bef_sg);
					break;
				default:
					sg_out.write_graph1(bef_sg);
					break;
			};
		};
		if(if_agent_out && ((current_time==0 || current_time==total_time) || (out_agent_interval \
			&& cl.interval(out_agent_interval)))) {
			one_agent_out.write_agent(agent_id,bef_avec,bef_ag,bef_sg,cl.get());
		};
		if (if_network_stat_out && current_time==out_network_stat_time) {
			Util::combine_graphs(cg,bef_sg,bef_ag);
		};

		// Updating AG, avec, and SG. (the order is important!)
		// 1, AG update : bef_avec, bef_ag (, bef_sg) -> aft_ag.
		//	(RNG part of bef_avec will be also changed) 
		// 2, avec update : bef_avec (, bef_ag, bef_sg) -> aft_avec.
		//	(RNG part of bef_avec will be also changed 
		//	and copied to aft_avec, from here on, aft_avec should be
		//	used for the RNG) 
		// 3, SG update : aft_avec (, bef_ag, bef_sg) -> aft_sg.
		//	(RNG part of aft_avec will be also changed) 
		//	(But in RW problem, RNG is not used.)
		switch (update_method) {
		   case 1:
			if (if_ag_update) ag_rule.update_graph(bef_avec,bef_ag,aft_ag,bef_sg);
			avec_rule1.update_agents(bef_avec,aft_avec,bef_ag,bef_sg);
		   	break;
		   case 2:
			if (if_ag_update) ag_rule.update_graph(bef_avec,bef_ag,aft_ag,bef_sg);
			avec_rule2.update_agents(bef_avec,aft_avec,bef_ag,bef_sg);
		   	break;
		   case 3:
			if (if_ag_update) ag_rule2.update_graph(bef_avec,bef_ag,aft_ag,bef_sg);
			avec_rule1.update_agents(bef_avec,aft_avec,bef_ag,bef_sg);
		   	break;
		   case 4:
			if (if_ag_update) ag_rule2.update_graph(bef_avec,bef_ag,aft_ag,bef_sg);
			avec_rule2.update_agents(bef_avec,aft_avec,bef_ag,bef_sg);
		   	break;
		   case 5:
			if (if_ag_update) ag_rule2.update_graph(bef_avec,bef_ag,aft_ag,bef_sg);
			avec_rule3.update_agents(bef_avec,aft_avec,bef_ag,bef_sg);
		   	break;
		   case 6:
			if (if_ag_update) ag_rule2.update_graph(bef_avec,bef_ag,aft_ag,bef_sg);
			avec_rule3.update_agents2(bef_avec,aft_avec,bef_ag,bef_sg);
		   	break;
		};
		if (neighbor_type_sg>0) sg_rule.update_graph(aft_avec,bef_ag,bef_sg,aft_sg);

		// Check the convergence of opinions.
		// If it is found to be the same for "convergence_check_period" times,
		// we will assume it is converged.
		if(convergence_method && convergence_check_period) {
			if(Util::check_convergence(bef_avec,aft_avec,bef_ag,aft_ag,convergence_method))
				conv_time++;
			else
				conv_time=0;
		};
		// Writing the period info to a separate file.
		if(convergence_method>3 && if_snapshot_out && convergence_out_period && cl.get()%convergence_out_period==0) {
			int meshsize=50;
			double per=abs(meshsize*Util::find_av_diff(bef_avec,opinion_topology,meshsize));
			agents_out_p.write(cl.get());
			agents_out_p.write('\t');
			agents_out_p.write(per);
			agents_out_p.write('\t');
			agents_out_p.write(int(per+0.5));
			agents_out_p.write('\n');
		};
	} while((convergence_check_period!=0 ? conv_time<convergence_check_period : true) && cl.tick()<=total_time);

	long final_time;
	if (conv_time==convergence_check_period) {
		final_time=cl.get();
		cout << "   Converged. ";
	}
	else {
		final_time=total_time;
		cout << "   Done. ";
	};

	// Writing outputs to files for the final time if necessary.
	if(final_time!=total_time) {
		if(if_snapshot_out) {
			agents_out.write_all_agents(final_avec,final_time);
			if (convergence_method>3) {
				int meshsize=50;
				double per=abs(meshsize*Util::find_av_diff(final_avec,opinion_topology,meshsize));
				agents_out_p.write(final_time);
				agents_out_p.write('\t');
				agents_out_p.write(per);
				agents_out_p.write('\t');
				agents_out_p.write(int(per+0.5));
				agents_out_p.write('\n');
			};
		};
		if(if_ag_snapshot_out) {
			ag_out.write("T\t");
			ag_out.write(final_time); // writing the current time
			ag_out.write('\n');
			switch (out_ag_snapshot_method) {
				case 1:
					ag_out.write_graph1(final_ag);
					break;
				case 2:
					ag_out.write_graph2(final_ag);
					break;
				default:
					ag_out.write_graph1(final_ag);
					break;
			};
		};
		if(if_sg_snapshot_out) {
			sg_out.write("T\t");
			sg_out.write(final_time); // writing the current time
			sg_out.write('\n');
			switch (out_sg_snapshot_method) {
				case 1:
					sg_out.write_graph1(final_sg);
					break;
				case 2:
					sg_out.write_graph2(final_sg);
					break;
				default:
					sg_out.write_graph1(final_sg);
					break;
			};
		};
	};
	if (if_network_stat_out && (out_network_stat_time<0 || out_network_stat_time>final_time)) {
		Util::combine_graphs(cg,final_sg,final_ag);
		out_network_stat_time=final_time;
	};
	if (geometry==0 && int_range==0) 
		Util::combine_graphs(cg,final_sg,final_ag);

	cout << "The time has evolved from 0 to " << final_time;
	cout << " (timestep)." << endl;

	// Closing all output files if necessary.
	if (if_snapshot_out) {
		agents_out.close();
		agents_out_p.close();
	};
	if (if_ag_snapshot_out) ag_out.close();
	if (if_sg_snapshot_out) sg_out.close();
	if (if_agent_out) one_agent_out.close();

	// Writing the summary : in this case, the components info for ag.
	bool converged=!(final_time==total_time);
	long ngroups=1;
	double op_spread, op_spread2;
	vector<AgentIDSet> components;
	long ncomponents=1;
	AgentVec biggest_component;
	int biggest=0;
	long biggest_size=nagents;

	// for the special case of 1d ring (geometry==0)
	if (geometry==0) {
		int num_bins=100;
		if (int_range==0) {
			ncomponents=cg.find_clusters(components);
			if (ncomponents>1) {
				biggest_size=0;
				for (int i=0;i<components.size();i++) {
					if (components[i].size()>biggest_size) {
						biggest=i;
						biggest_size=components[i].size();
					};
				};
				for (AgentIDSet::const_iterator i=components[biggest].begin();i!=components[biggest].end();i++)
					biggest_component.push_back(final_avec[*i]);
				op_spread=Util::find_opinionspread(biggest_component,num_bins);
//cout << op_spread << endl;
				op_spread2=Util::find_opinionspread2(biggest_component);
			}
			else {
				op_spread=Util::find_opinionspread(final_avec,num_bins);
				op_spread2=Util::find_opinionspread2(final_avec);
			};
		}
		else {
			op_spread=Util::find_opinionspread(final_avec,num_bins);
			op_spread2=Util::find_opinionspread2(final_avec);
		};
	};
	double ave_diff=0;
	vector<multiset<double> > opiniongroups(ngroups);
	if (converged) {
		double op_resolution=(op_threshold>0.1 ? 0.1 : op_threshold);
		if (final_ag.show_edge_size()==nagents*(nagents-1)/2)  // for the full graph only
			op_resolution=1/(double) nagents;
		ngroups=Util::find_opiniongroups(final_avec,opiniongroups,\
			opinion_topology,op_resolution);
	};


	if(if_summary_out) {
		summary_out.write("nagents\t");
		summary_out.write(final_avec.size());
		summary_out.write('\n');
		summary_out.write("edges\t");
		summary_out.write(final_ag.show_edge_size());
		summary_out.write('\n');
		summary_out.write("time\t");
		summary_out.write(final_time-(conv_time==-1 ? 0 : conv_time));
		summary_out.write('\n');
		if (convergence_method<4 && convergence_method>0) {
			summary_out.write("converged\t");
			summary_out.write(converged ? ngroups : 0);
			if (geometry==0) {
				summary_out.write('\t');
				summary_out.write(op_spread);
				summary_out.write('\t');
				summary_out.write(op_spread2);
				summary_out.write('\t');
				summary_out.write(ncomponents);
				summary_out.write('\t');
				summary_out.write(ncomponents==1?nagents:biggest_component.size());
				if (int_range==0 && ncomponents>1 && if_snapshot_out) {
					out_components_file=out_snapshot_file+"c";
					RWOut components_out(out_components_file);
					// components_out.write(biggest_size);
					// components_out.write('\n');
					for (AgentIDSet::const_iterator j=components[biggest].begin();\
						j!=components[biggest].end();j++) {
						components_out.write(*j);
						components_out.write('\t');
						components_out.write(final_avec[*j].get_state().get_op());
						components_out.write('\n');
					};
					components_out.close();
				};
			};
			summary_out.write('\n');
			if (converged || opinion_topology==1) {
				for (int i=0;i<ngroups;i++) {
					summary_out.write("opinions\t");
					double sum=0;
					for (set<double>::const_iterator j=opiniongroups[i].begin();\
						j!=opiniongroups[i].end();j++) {
						sum+=*j;
					};
					summary_out.write(sum/opiniongroups[i].size());
					summary_out.write('\t');
					summary_out.write(opiniongroups[i].size());
					summary_out.write('\n');
				};
			};
		}
		else if (convergence_method>3) {
			summary_out.write("converged\t0\n");
			summary_out.write("simulations to observe specific transitions\n");
		}
		else if (convergence_method==0) {
			ngroups=Util::find_opiniongroups(final_avec,opiniongroups,\
				opinion_topology,0.02);
			summary_out.write("ngroups\t");
			summary_out.write(ngroups);
			summary_out.write('\n');
		
		};

		if (num_edges==0 && geometry==0) {
			long meshsize=50;
			double diff_x=Util::find_av_diff(final_avec,opinion_topology,meshsize);
			summary_out.write("av_diff_x\t");
			if (diff_x>99) {// not converged x-direction
				summary_out.write("0\t-1\n");
			}
			else {
				summary_out.write(diff_x);
				summary_out.write('\t');
				summary_out.write(int(meshsize*(diff_x>0?diff_x:-diff_x)+0.5));
				summary_out.write('\n');
			};
		};
		if ((!converged || convergence_method>3) && geometry)  {
			summary_out.write("av_diff_x\t");
			double width_x=Util::find_op_width(final_avec,opinion_topology,1);
			double width_y=Util::find_op_width(final_avec,opinion_topology,2);
			long meshsize=50;
			// diff_x and diff_y will be 100, only when opinion widths of more than
			//	half meshes are greater than 0.5 (making the results not useful)
			double diff_x=Util::find_av_diff(final_avec,opinion_topology,meshsize);
			double diff_y=Util::find_av_diff(final_avec,opinion_topology,meshsize,2);
			if (diff_x>99 || xsize==1) {// not converged x-direction
				summary_out.write("0\t-1\n");
			}
			else {
				summary_out.write(diff_x);
				summary_out.write('\t');
				summary_out.write(int(meshsize*(diff_x>0?diff_x:-diff_x)+0.5));
				summary_out.write('\n');
			};
			summary_out.write("av_diff_y\t");
			if (diff_y>99 || ysize==1) {// not converged y-direction
				summary_out.write("0\t-1\n");
			}
			else {
				summary_out.write(diff_y);
				summary_out.write('\t');
				summary_out.write(int(meshsize*(diff_y>0?diff_y:-diff_y)+0.5));
				summary_out.write('\n');
			};
			summary_out.write("av_diff_p\t");
			if (width_x>op_threshold && width_y>op_threshold) { // periodic fractionally
				double diff_p=Util::find_av_diff_p(final_avec,opinion_topology,meshsize,op_threshold);
				if (diff_p<-1) {
					summary_out.write("0\t-1\n");
				}
				else {
					summary_out.write(diff_p);
					summary_out.write('\t');
					summary_out.write(int((meshsize)*(diff_p>0?diff_p:-diff_p)+0.5));
					summary_out.write('\n');
				};
			}
			else {
				summary_out.write("0\t-1\n");
			};
		};
		if (if_network_stat_out) {
			summary_out.write("network_stat_time\t");
			summary_out.write(out_network_stat_time);
			summary_out.write('\n');
			summary_out.write("ncomponents\t");
			summary_out.write(ncomponents);
			summary_out.write('\n');
			summary_out.write("clustering_coeff\t");
			summary_out.write(Util::find_clustering_coeff(cg));
			summary_out.write('\n');
			summary_out.write("mean_distance\t");
			summary_out.write(Util::find_mean_distance(cg));
			summary_out.write('\n');
			if (if_components_out) {
				RWOut components_out(if_components_out ? out_components_file : RWOut::noout);
				for (long i=0;i<ncomponents;i++) {
					long componentsize=components[i].size();
					components_out.write(i);
					components_out.write('\t');
					components_out.write(componentsize);
					components_out.write('\n');
					double sum=0.0;
					for (AgentIDSet::const_iterator j=components[i].begin();\
						j!=components[i].end();j++) {
						sum+=final_avec[*j].get_state().get_op();
						components_out.write(*j);
						components_out.write('\t');
						components_out.write(final_avec[*j].get_state().get_op());
						components_out.write('\n');
					};
					//sum/=componentsize;
					//network_stat_out.write(sum);
					//network_stat_out.write('\n');
				};
				components_out.close();
			};
		};
		summary_out.close();
	};

	cout << "4, End of program.\n";

   }
   catch (Error::MAX_RN_REACHED m) {
	cerr << "# Error: maximum number of random numbers for each agent reached.\n" ;
	return 1;
   }
   catch (Error::TOO_MANY_RN_NEEDED m) {
	cerr << "# Error: maximum number of random numbers for a RNG reached.\n" ;
	cerr << "         The number should be less than 20% of the period of RNG.\n" ;
	return 1;
   }
   catch (Error::Bad_Input_File m) {
	cerr << "# Error: Bad input file, " << m.filename << ".\n" ;
	cerr << "         " << m.message << '\n';
	return 1;
   }
   catch (Error::Bad_Input_Value m) {
	cerr << "# Error: Bad input value at line " << m.line << " in the input file, ";
	cerr << m.filename << ".\n" ;
	return 1;
   }
   catch (Error::NeighborTypeError err) {
	cerr << "# Error: " << err.message << '\n';
	return 1;
   };
   	
	return 0;
};
