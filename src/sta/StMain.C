// 
// 	Filename : sStWMain.C
//
//	Author : Suhan Ree
//	Date   : 10-16-2003

#include "Utilities.h"
#include "Types.h"
#include "Errors.h"
#include "DiGraph1.h"
#include "Graph.h"
#include "Input.h"
#include "InputParam.h"
#include "Output.h"
#include "Point.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <list>
#include <set>
#include <map>

using namespace std;

int main(int argc, char **argv) {

	// Command line input test.
	if (argc!=2) {
		cerr << " Usage: Stat <input filename>\n";
		exit(1);
	};
	// Input filename in a string.
	string infile(argv[1]);

   try {
	//===============================================================
	//=================(Input Parameters)============================
	long nagents;

	long i_time;
	long f_time;
	long time_interval;
	
	long i_k;
	long f_k;
	long k_interval;

	long num_bin=10;

	bool if_graph=true;
	int format=1;
	string in_file_graph;
	string out_file_graph;

	bool if_agent=true;
	string in_file_agent;
	string out_file_agent;

	//===============================================================
	//==============(Reading Input Parameters)=======================
	cout << "1, Reading the input parameters..." << endl;
	InputParam in1(infile);
	in1.read();
	// in1.print_key_val();
	if (!in1.get("nagents",nagents,cerr)) {
		cerr << "# No parameter given: nagents \n";
		exit(1);
	};
	if (!in1.get("i_time",i_time,cerr)) {
		cerr << "# No parameter given: i_time \n";
		exit(1);
	};
	if (!in1.get("f_time",f_time,cerr)) {
		cerr << "# No parameter given: f_time \n";
		exit(1);
	};
	if (!in1.get("time_interval",time_interval,cerr)) {
		cerr << "# No parameter given: time_interval \n";
		exit(1);
	};
	if (!in1.get("i_k",i_k,cerr)) {
		cerr << "# No parameter given: i_k \n";
		exit(1);
	};
	if (!in1.get("f_k",f_k,cerr)) {
		cerr << "# No parameter given: f_k \n";
		exit(1);
	};
	if (!in1.get("k_interval",k_interval,cerr)) {
		cerr << "# No parameter given: k_interval \n";
		exit(1);
	};
	if (!in1.get("num_bin",num_bin,cerr)) {
		cerr << "# No parameter given: num_bin \n";
		cerr << "  Default value, 10, will be used.\n";
	};
	if (!in1.get("if_graph",if_graph,cerr)) {
		cerr << "# No parameter given: if_graph \n";
		cerr << "  Default value, true, will be used.\n";
	};
	if (!in1.get("format",format,cerr)) {
		cerr << "# No parameter given: format.\n";
		cerr << "  Default value 1 will be used.\n";
	};
	if (!in1.get("in_file_graph",in_file_graph,cerr)) {
		cerr << "# No parameter given: in_file_graph \n";
		exit(1);
	};
	if (!in1.get("out_file_graph",out_file_graph,cerr)) {
		cerr << "# No parameter given: out_file_graph \n";
		exit(1);
	};
	if (!in1.get("if_agent",if_agent,cerr)) {
		cerr << "# No parameter given: if_agent \n";
		cerr << "  Default value, true, will be used.\n";
	};
	if (!in1.get("in_file_agent",in_file_agent,cerr)) {
		cerr << "# No parameter given: in_file_agent \n";
		exit(1);
	};
	if (!in1.get("out_file_agent",out_file_agent,cerr)) {
		cerr << "# No parameter given: out_file_agent \n";
		exit(1);
	};

	// close the input parameter file.
	in1.close();

	// Checking values of basic input parameters
	// Util::error_check2(nagents,i_time,f_time,time_interval,
	// 	i_k, f_k, k_interval,format);

	cout << "\tNumber of agents: " << nagents << endl;
	cout << "\tFind degree statistics from " << i_k << " to ";
	cout << f_k << " with interval " << k_interval << '.' << endl;
	//==============================================================
	//=============(Setting Up : Initialization)====================
	cout << "2, Finding the statistics..." << endl;
   if (if_graph) {
	cout << "\tFind the degree statistics from " << i_k << " to ";
	cout << f_k << " with interval " << k_interval << '.' << endl;
	cout << "\tReading the file, " << in_file_graph << ", and writing ";
	cout << "the degree statistics to the file, " << out_file_graph << '.' << endl;

	Input in2(in_file_graph);
	Output out1(out_file_graph);

	DiGraph1 ag(nagents);
	
	// For each time step.
	for (long t=i_time;t<=f_time;t+=time_interval) {
		char ch;
		long time;
		// Skip the graphs with different times.
		while(true) {
			in2.read(ch);
			in2.read(time);
			if (ch=='T' && time==t) break;
			in2.read(ch); // Reading the '\n'.
			if (!in2.read_lines(nagents)) {
				Error::Bad_Input_File badfile(in_file_graph);
				throw badfile;
			};
		};
		// Read the graph.
		in2.read_graph2(ag);

		// Initialize the stat map.
		long total_k=(f_k-i_k)/k_interval+1;
		map<long,long> stat;
		for (long i=0;i<total_k;i++) stat[i_k+k_interval*i]=0;

		// Find the statistics.
		for (AgentID i=0;i<nagents;i++) {
			long k=ag.find_in_deg(i);
			if (stat.find(k)!=stat.end()) stat[k]++;
		};
	
		// Write the info to the output file.
		for (map<long,long>::const_iterator i=stat.begin();\
			i!=stat.end();i++) {
			out1.write(t);
			out1.write('\t');
			out1.write(i->first);
			out1.write('\t');
			out1.write(i->second);
			out1.write('\n');
		};
		cout << "\tT=" << t << '.' << endl;
	};

	// when total_t==1, print the summary of the graph.
	if (((f_time-i_time)/time_interval+1)==1) ag.print_summary();
   };

   if (if_agent) {

	cout << endl;
	cout << "\t=============================================================" << endl;
	cout << "\tFind the statistics of opinions";
	cout << " with interval " << 1.0/num_bin << '.' << endl;
	cout << "\tReading the file, " << in_file_agent << ", and writing ";
	cout << "the the statistics to the file, " << out_file_agent << '.' << endl;

	Input in3(in_file_agent);
	Output out2(out_file_agent);

	vector<long> stat2(num_bin);	// Count the value for each bin.
	vector<double> init_value(num_bin); // Initial value for each bin.
	
	// Initialize the initial value for the bin.
	for (long i=0;i<num_bin;i++)
		init_value[i]=double(i)/num_bin;

	// For each time step.
	for (long t=i_time;t<=f_time;t+=time_interval) {
		// Initialize the stat2.
		for (long i=0;i<num_bin;i++)
			stat2[i]=0;

		long time, id, ix, iy;
		double op, gu;
		long cnt=0;

		do {
			if(!in3.read(time)) {
				Error::Bad_Input_File badfile(in_file_agent);
				throw badfile;
			};
			in3.read(id);
			in3.read(ix);
			in3.read(iy);
			in3.read(op);
			in3.read(gu);
			if (time==t) {
				stat2[long(op*num_bin)]++;
				cnt++;
			};
		} while (cnt<nagents);

		// Write the info to the output file.
		for (long i=0;i<num_bin;i++) {
			out2.write(t);
			out2.write('\t');
			out2.write(init_value[i]);
			out2.write('\t');
			out2.write(stat2[i]);
			out2.write('\n');
		};
		cout << "\tT=" << t << '.' << endl;
	};
   };

   }
   catch (Error::Bad_Input_File badfile) {
	if (badfile.filename.size()!=0) 
   		cerr << "# Bad input file: " << badfile.filename << ".\n";
	else
   		cerr << "# Bad input file.\n";
		
	exit(1);
   };

	cout << "   Done." << endl;
	cout << "3, End of program.\n";

	return 0;
};
