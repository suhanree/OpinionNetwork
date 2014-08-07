// 
// 	Filename : Random1.C 
//
//	Author : Suhan Ree
//	Date   : 06-11-2004

#include "Random1.h"
#include "Errors.h"
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long Random1::draw() {
	randx=randx*1103515245+12345;
	return abs(randx);
};

long Random1::ndraw(const vector<double> &pdf) {
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

long Random1::ndraw(const vector<long> &pdf) {
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
pair<double,double>  Random1::gaussian_draw(double ave, double sd) {
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
    
long Random1L::max_ran=400000000;

long Random1L::draw() {
	if (++rn_cnt>max_ran) {
		Error::MAX_RN_REACHED m;
		throw m;
	};
	randx=randx*1103515245+12345;
	return abs(randx);
};

long Random1L::ndraw(const vector<double> &pdf) {
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

long Random1L::ndraw(const vector<long> &pdf) {
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
pair<double,double>  Random1L::gaussian_draw(double ave, double sd) {
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
