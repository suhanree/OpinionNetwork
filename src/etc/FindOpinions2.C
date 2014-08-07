// 
// 	Filename : FindOpinions2.C
//
//	Author : Suhan Ree
//	Date   : 07-06-2004

// This C++ program is used to find the number of opinion values from 
// cluster summary file (for non-periodic opinions).
//
// Format of the cluster summary file is as follows.
// <cluster id> <agent id> <opinion>

// Usage : FindOpinions2 <threshold> <cluster summary filename> <output file name>

#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int argc, char **argv) {
	
	// Command line input test.
	if (argc!=4) {
		cerr << " Usage: FindOpinions2 <threshold> ";
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
