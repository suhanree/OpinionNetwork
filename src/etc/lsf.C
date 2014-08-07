#include <iostream>
#include <fstream>
#include <gsl/gsl_fit.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int argc, char **argv) {
	if (argc!=4) {
		cerr << "Usage: " << argv[0] << " <g> <E> <output filename>" << endl;
		exit(1);
	};
	vector<double> x,y;
	double xtemp, ytemp;
	string ifilename("tdist_g");

	ifilename=ifilename+argv[1]+"_e"+argv[2]+"_log";

	ifstream ifile(ifilename.c_str(),ios::in);
	ofstream ofile(argv[3],ios::out|ios::app);

	while (ifile >> xtemp >> ytemp) {
		x.push_back(xtemp);
		y.push_back(ytemp);
	};
	
	const int size=x.size();
	double x1[size], y1[size];

	for (int i=0;i<size;i++) {
		x1[i]=x[i];
		y1[i]=y[i];
	};

	double cov0,cov1,cov2,sumsq,c0,c1;
	const int stride=1;

	gsl_fit_linear(x1,stride,y1,stride,size,&c0,&c1,&cov0,&cov1,&cov2,&sumsq);

	ofile << argv[2] << '\t' << abs(c1) << endl;

	return 0;
};
