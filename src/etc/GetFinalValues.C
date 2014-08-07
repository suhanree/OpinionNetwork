#include <iostream>
#include <queue>
#include <fstream>
#include <cstdlib>
#include <cmath>

using namespace std;

int main(int argc, char **argv) {
	// Command line input test.
	if (argc!=3) {
		cerr << " Usage: GetFinalValues <number of agents> <input filename>\n";
		exit(1);
	};

	int nagent=atoi(argv[1]);
	ifstream ifile(argv[2],ios::in);
	if (!ifile) {
		cerr << "No Input file named, " << argv[2] << endl;
		exit(1);
	};

	queue<double> myqueue;
	
	long a, b, c, d;
	double e, f;

	while (ifile >> a >> b >> c >> d >> e >> f) {
		myqueue.push(e);
		if (myqueue.size()>nagent) myqueue.pop();
	};

	int nhalf=nagent/2;
	int nbin=nhalf*2;

	vector<int> count(nbin);
	vector<double> centered(nbin);

	for (int i=0;i<nbin;i++) {
		count[i]=0;
		centered[i]=0;
	};

	vector<double> phi(nagent), phi2(nagent);
	for (int i=0;i<nagent;i++) {
		if (!myqueue.empty()) {
			phi[i]=myqueue.front();
			count[int(phi[i]*nbin)]++;
			myqueue.pop();
		}
		else {
			cerr << "Check the number of agents.\n";
			exit(1);
		};
	};
	if (!myqueue.empty()) {
		cerr << "Check the number of agents.\n";
		exit(1);
	};

	int max_i=nhalf,max=0;
	for (int i=0;i<nbin;i++)
		if (count[i]>max) {max=count[i];max_i=i;};
	for (int i=0;i<nbin;i++)
		centered[(i-(max_i-nhalf)+nbin)%nbin]=count[i]*double(nbin)/nagent;

//cout << max_i << endl;
//for (int i=0;i<nbin;i++)
//cout << count[i] << endl;
//for (int i=0;i<nbin;i++)
//cout << centered[i] << endl;
	
	// Method 1: using the pdf. 
	double ave, simga_sq, sum1=0, sum2=0;
	double delta=1/double(nbin);
	double phi_b;
	for (int i=0;i<nbin;i++) {
		phi_b=delta/2+i*delta;
		sum1+=centered[i]*phi_b*delta;
		sum2+=centered[i]*phi_b*phi_b*delta;
	};

	// Method 2: from individual values
	double phi_s=(max_i+0.5)*delta;
	for (int i=0;i<nagent;i++) {
		double diff=phi[i]-phi_s;
		if (diff>0.5) phi2[i]=diff-1;
		else if (diff>-0.5) phi2[i]=diff;
		else phi2[i]=diff+1;
//cout << phi2[i] << endl;
	};
	double s1=0, s2=0;
	for (int i=0;i<nagent;i++) {
		s1+=phi2[i];
		s2+=phi2[i]*phi2[i];
	};
	s1/=nagent;
	s2/=nagent;
//cout << s1 << endl;
//cout << s2 << endl;
//cout << s2-s1*s1 << endl;
	cout << sqrt((sum2-sum1*sum1)*12) << '\t' << (s2-s1*s1>1.0e-12 ? sqrt((s2-s1*s1)*12) : 0) << endl;
		
	return 0;
};
