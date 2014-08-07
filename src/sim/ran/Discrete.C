// 
// 	Filename : 	Discrete.C 
//
//	Author : Suhan Ree
//	Date   : 11-21-2002

// This is the random number generator with a discrete distribution.
// Using two methods : rejection method, cumulative distribution.

#include "Discrete.h"
#include "Random3.h"
#include <cmath>
#include <vector>
#include <iostream>

using std::cout;
using std::endl;
using std::vector;

// Constructor.
Discrete::Discrete(const vector<double> &pr, const unsigned long s)
	: ran(s), prob(pr) {
	size=prob.size();
	normalize();	// Normalize the probability distribution.
	max=prob[0];
	for (int i=1;i<size;i++) if (max<prob[i]) max=prob[i];
};

// Normalization.
void Discrete::normalize() {
	int i;
	double sum=0;

	for (i=0;i<size;i++) sum+=prob[i];
	for (i=0;i<size;i++) prob[i]/=sum;
};

// Drawing a number with the rejection method with the constant comparison fn.
long Discrete::draw() {	
	int i;
	double y;
	
	do {
		i=int(double(ran.draw())*size/(double(ran.rand_max())+1));
		y=double(ran.draw())*max/(double(ran.rand_max())+1);
	} while (y>=prob[i]);
	return i;
};

void Discrete::print() {
	for (int i=0;i<size;i++) cout << prob[i] << '\n';
	cout << endl;
};

// Constructor.
Discrete_c::Discrete_c(const vector<double> &pr, const unsigned long s)
	: Discrete(pr,s), cumu(pr) {
	cumu[0]=0;
	for (int i=1;i<pr.size();i++) {
		cumu[i]=0.0;
		for (int j=0; j<i; j++) cumu[i]+=pr[j];
	};
	// Normalize.
	for (int i=0;i<pr.size();i++) cumu[i]/=(cumu[pr.size()-1]+pr[pr.size()-1]); 
};
	
	
// Drawing a number with the cumulative distribution.
long Discrete_c::draw() {	
	int min=0, max=size;
	int div2=size/2;
	
	// Draw a number between 0 and 1.
	double y=double(ran.draw())/(double(ran.rand_max())+1);
	// Find the bin.
	while (min!=div2) {
		if (cumu[div2]<y) min=div2;
		else 	max=div2;
		div2=min+(max-min)/2;
	};
	return min;
};

void Discrete_c::print() {
	for (int i=0;i<cumu.size();i++) cout << cumu[i] << '\n';
	cout << endl;
};

