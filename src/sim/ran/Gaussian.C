// 
// 	Filename : 	Gaussian.C 
//
//	Author : Suhan Ree
//	Date   : 11-20-2002

// This is the random number generator with Gaussian distribution.
// Used the Box-Muller method (Ref. Numerical Recipes in C++, gasdev).

#include "Gaussian.h"
#include "Random3.h"
#include <cmath>

// Constructor.
Gaussian::Gaussian(unsigned long seed, const double ave, const double var) 
	: ran(seed), average(ave), variance(var), set(false), gset(0.0) {};
	
// Drawing a number with the Gausssian distribution.
double Gaussian::draw() {	
	double fac,rsq,v1,v2;
	
	if (!set) {
		do {
			v1=-1.0+double(ran.draw())/(double(ran.rand_max())+1)*2;
			v2=-1.0+double(ran.draw())/(double(ran.rand_max())+1)*2;
			rsq=v1*v1+v2*v2;
		} while (rsq >= 1.0 || rsq==0.0);
		fac=sqrt(-2.0*log(rsq)/rsq*variance);
		gset=v1*fac+average;
		set=true;
		return v2*fac+average;
	}
	else {
		set=false;
		return gset;
	};
};
