// 
// 	Filename : FindOpinions.C
//
//	Author : Suhan Ree
//	Date   : 06-25-2004

// This C++ program is used to find the number of opinion values from 
// cluster summary file.
//
// Format of the cluster summary file is as follows.
// <cluster id> <agent id> <opinion>

// Usage : FindOpinions <threshold> <cluster summary filename> <output file name>

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int argc, char **argv) {
	
	// Command line input test.
	if (argc!=4) {
		cerr << " Usage: FindOpinions <threshold> ";
		cerr << "<cluster summary filename> <output file name>\n";
		exit(1);
	};

	double thres=atof(argv[1]);
	long a, b;
	double c;
	
	ifstream ifile(argv[2],ios::in);
	ofstream ofile(argv[3],ios::out);

	vector<double> ops;
	vector<double> values;
	vector<int> numbers;
	int index;

	if (!ifile) {
		cerr << "No Input file named, " << argv[2] << endl;
		exit(1);
	};

	while (ifile >> a >> b >> c) {
		ops.push_back(c);
	};


	for (long i=0;i<ops.size();i++) {
		int oldvalue=0;
		for (long j=0;j<values.size();j++)
			if (abs(values[j]-ops[i])<thres) {
				oldvalue++;
				numbers[j]++;
			};
		if (!oldvalue) {
			values.push_back(ops[i]);
			numbers.push_back(1);
		}
		else if (oldvalue>1) {
			cout << "Not Converged Yet." << endl;
			ifile.close();
			ofile.close();
			return 0;
		};
	};
	
	cout << values.size() << endl;
	for (int i=0;i<values.size();i++) ofile << values[i] << '\t' << numbers[i] << endl;

	ifile.close();
	ofile.close();

	return 0;
};
