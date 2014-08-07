// 
// 	Filename : Random2.C 
//
//	Author : Suhan Ree
//	Date   : 06-11-2004

#include "Random2.h"
#include "Errors.h"
#include <vector>
#include <cmath>

using namespace std;

// Constants for the generator.
static const unsigned long a=16807, m=2147483647;
static const unsigned long r=2836, q=127773;
static const unsigned long mask=123459876;

long Random2::draw() {
	unsigned long t1, t2;

	// Exclusive OR with mask to make it work when the seed is 0.
	// But when the seed is exactly the mask value (very unlikely),
	// the generator produces the same number every time...
	randx^=mask;	
	t1=a*(randx%q);
	t2=r*(randx/q);
	
	randx=(t1>=t2 ? t1-t2 : m-t2+t1);
	randx^=mask;	
	return long(randx);
};

long Random2::ndraw(const vector<double> &pdf) {
	long size=pdf.size();
	if (size<=1) return 0; // Trivial cases.
	vector<double> cdf(size);
	cdf[0]=0;
	for (long i=1;i<size;i++) {
		cdf[i]=0.0;
		for (long j=0; j<i; j++) cdf[i]+=pdf[j];
	};
	// Normalize.
	for (long i=1;i<size;i++) cdf[i]/=(cdf[size-1]+pdf[size-1]); 
	// Drawing a number with the cumulative distribution.
	long min=0, max=size;
	long div2=size/2;
	// Find the right bin. (fdraw() will give a double between 0 and 1)
	double y=fdraw();
	while (min!=div2) {
		if(cdf[div2]<y) min=div2;
		else 	max=div2;
		div2=min+(max-min)/2;
	};
	return min;
};

long Random2::ndraw(const vector<long> &pdf) {
	long size=pdf.size();
	if (size<=1) return 0; // Trivial cases.
	vector<double>  cdf(size);
	cdf[0]=0;
	for (long i=1;i<size;i++) {
		cdf[i]=0.0;
		for (long j=0; j<i; j++) cdf[i]+=pdf[j];
	};
	// Normalize.
	for (long i=1;i<size;i++) cdf[i]/=(cdf[size-1]+pdf[size-1]); 
	// Drawing a number with the cumulative distribution.
	long min=0, max=size;
	long div2=size/2;
	// Find the right bin. (fdraw() will give a double between 0 and 1)
	double y=fdraw();
	while (min!=div2) {
		if(cdf[div2]<y) min=div2;
		else 	max=div2;
		div2=min+(max-min)/2;
	};
	return min;
};

// Draw a double with the gaussian dist. with average and standard deviation.
pair<double,double>  Random2::gaussian_draw(double ave, double sd) {
	double fac,rsq,v1,v2;
	do {
		v1=fdraw(-1.0,1.0);
		v2=fdraw(-1.0,1.0);
		rsq=v1*v1+v2*v2;
	} while (rsq >= 1.0 || rsq==0.0);
	fac=sd*sqrt(-2.0*log(rsq)/rsq);
	pair<double,double> temp(v1*fac+ave,v2*fac+ave);
	return temp;
};

long Random2L::max_ran=400000000;

long Random2L::draw() {
	if (++rn_cnt>max_ran) {
		Error::MAX_RN_REACHED m;
		throw m;
	};

	unsigned long t1, t2;

	// Exclusive OR with mask to make it work when the seed is 0.
	// But when the seed is exactly the mask value (very unlikely),
	// the generator produces the same number every time...
	randx^=mask;	
	t1=a*(randx%q);
	t2=r*(randx/q);
	
	randx=(t1>=t2 ? t1-t2 : m-t2+t1);
	randx^=mask;	
	return long(randx);
};

long Random2L::ndraw(const vector<double> &pdf) {
	long size=pdf.size();
	if (size<=1) return 0; // Trivial cases.
	vector<double> cdf(size);
	cdf[0]=0;
	for (long i=1;i<size;i++) {
		cdf[i]=0.0;
		for (long j=0; j<i; j++) cdf[i]+=pdf[j];
	};
	// Normalize.
	for (long i=1;i<size;i++) cdf[i]/=(cdf[size-1]+pdf[size-1]); 
	// Drawing a number with the cumulative distribution.
	long min=0, max=size;
	long div2=size/2;
	// Find the right bin. (fdraw() will give a double between 0 and 1)
	double y=fdraw();
	while (min!=div2) {
		if(cdf[div2]<y) min=div2;
		else 	max=div2;
		div2=min+(max-min)/2;
	};
	return min;
};

long Random2L::ndraw(const vector<long> &pdf) {
	long size=pdf.size();
	if (size<=1) return 0; // Trivial cases.
	vector<double>  cdf(size);
	cdf[0]=0;
	for (long i=1;i<size;i++) {
		cdf[i]=0.0;
		for (long j=0; j<i; j++) cdf[i]+=pdf[j];
	};
	// Normalize.
	for (long i=1;i<size;i++) cdf[i]/=(cdf[size-1]+pdf[size-1]); 
	// Drawing a number with the cumulative distribution.
	long min=0, max=size;
	long div2=size/2;
	// Find the right bin. (fdraw() will give a double between 0 and 1)
	double y=fdraw();
	while (min!=div2) {
		if(cdf[div2]<y) min=div2;
		else 	max=div2;
		div2=min+(max-min)/2;
	};
	return min;
};

// Draw a double with the gaussian dist. with average and standard deviation.
pair<double,double>  Random2L::gaussian_draw(double ave, double sd) {
	double fac,rsq,v1,v2;
	do {
		v1=fdraw(-1.0,1.0);
		v2=fdraw(-1.0,1.0);
		rsq=v1*v1+v2*v2;
	} while (rsq >= 1.0 || rsq==0.0);
	fac=sd*sqrt(-2.0*log(rsq)/rsq);
	pair<double,double> temp(v1*fac+ave,v2*fac+ave);
	return temp;
};
