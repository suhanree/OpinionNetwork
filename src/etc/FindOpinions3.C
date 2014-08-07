// 
// 	Filename : FindOpinions3.C
//
//	Author : Suhan Ree
//	Date   : 01-10-2011

// This C++ program is used to find the number of opinion values from 
// cluster summary file (for periodic & non-periodic opinions).
//
// Format of the cluster summary file is as follows.
// <cluster id> <agent id> <opinion>

// Usage : FindOpinions3 <threshold> <cluster summary filename> <output file name> <opinion_topology>
//	topology: 1 (non-periodic), 2 (periodic)

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

// A function to find the absolutedifference between two opinions when opinions are linear(1) or circular(2).
double find_op_diff(double a, double b, short topology) {
	double diff=a-b;
	if (topology==2) { // when circular.
		if (diff>=0.5) diff=1.0-diff;
		else if (diff<0.0)
			if (diff>-0.5) diff=-diff;
			else diff=1.0+diff;
		return diff;
	};
	// when linear.
	if (diff<0) diff=-diff;
	return diff;
};

int main(int argc, char **argv) {
	
	// Command line input test.
	if (argc!=5) {
		cerr << " Usage: FindOpinions3 <threshold> ";
		cerr << "<cluster summary filename> <output file name> <opinon_topology>\n";
		exit(1);
	};

	double thres=atof(argv[1]);
	short topology=atoi(argv[4]);
	long a, b;
	double c;
	
	ifstream ifile(argv[2],ios::in);
	ofstream ofile(argv[3],ios::out);

	vector<double> ops;	// Storing all opinions values
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
			if (find_op_diff(values[j],ops[i],topology)<thres) {
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
	
for (long i=0;i<ops.size();i++) cout << "ops[" << i << "]=" << ops[i] << endl;
for (long i=0;i<values.size();i++) cout << "values[" << i << "]=" << values[i] << endl;
for (long i=0;i<numbers.size();i++) cout << "numbers[" << i << "]=" << numbers[i] << endl;
	long num0, num10, num20, num50, num100;
	long size=values.size();
	num0=num10=num20=num50=num100=size;
	for (int i=0;i<size;i++) {
		ofile << numbers[i] << '\t' << values[i] << endl;
		if (numbers[i]<100) {
			num100--;
			if (numbers[i]<50) {
				num50--;
				if (numbers[i]<20) {
					num20--;
					if (numbers[i]<10) num10--;
				};
			};
		};
	};

	cout << num0 << '\t' << num10 << '\t' << num20 << '\t' << num50 << '\t' << num100 << endl;
	ifile.close();
	ofile.close();

	return 0;
};
