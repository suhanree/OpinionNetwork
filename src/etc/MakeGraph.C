// 
// 	Filename : MakeGraph.C
//
//	Author : Suhan Ree
//	Date   : 07-02-2004

// This C++ program is used to generate the regular graph
// with N nodes and 2*E*N links, with each node originating 2*E directional
// links. All nodes are numbered from 0 to N-1, and destinations of
// links from i-th node are i-E, i-E+1, ..., i-1, i+1, ..., i+E-1, i+E
// (if the above destination is either less than 0 or greater than N-1,
// add N or subtract N).
//
// Format of the output file is as follows.
// <des> <ori1> <ori2> .....

// Usage : MakeGraph <nagents> <# of all edges> <output filename>
//		# of all edges should be a multiple of 2*N.

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {
	
	// Command line input test.
	if (argc!=4) {
		cerr << " Usage: MakeGraph <nagents> <number of edges> <output filename>\n";
		exit(1);
	};
	// Input filename in a string.
	string infile(argv[3]);

	// Numbers
	long nagents=atoi(argv[1]), nedges=atoi(argv[2]);
	
	if (nedges %(2*nagents)!=0 || nedges > nagents*(nagents-1)) {
		cerr << "Bad number of edges.\n";
		exit(1);
	};

	long ori;
	long ea=nedges/(2*nagents);

	ofstream of(argv[3],ios::out);

	for (long i=0;i<nagents;i++) {
		of << i;
		for (long j=-ea+i;j<=ea+i;j++) {
			if (j<0) 
				ori=j+nagents;
			else if (j>nagents-1) 
				ori=j-nagents;
			else
				ori=j;
			if (j!=i) of << '\t' << ori;
		};
		of << '\n';
	};

	of.close();

	return 0;
};
