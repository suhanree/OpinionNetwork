// 
// 	Filename : Random4.C 
//
//	Author : Suhan Ree
//	Date   : 06-11-2004

#include "Random4.h"
#include "Errors.h"
#include <vector>
#include <cmath>

using namespace std;

// Constants for the generator.
static const unsigned long m1=2147483563, m2=2147483399;
static const unsigned long a1=40014, a2=40692;
static const unsigned long q1=53668, q2=52774;
static const unsigned long r1=12211, r2=3791;
// Number of shuffling bins.
static const long nb=32;

// Constructor.
Random4::Random4(unsigned long s)
		: Random(s), randx2(s), v(nb) {
	if (randx==0ul) randx=1ul;
	randx2=randx;
	for (int i=nb+7;i>=0;i--) {
		unsigned long t1, t2;
		t1=a1*(randx%q1);
		t2=r1*(randx/q1);
		randx=(t1>=t2 ? t1-t2 : m1-t2+t1);
		if (i<nb) v[i]=randx;
	};
	y=v[0];
};
	
// Provides a seed.
void Random4::seed(const unsigned long &s) {
	randx=s;
	if (randx==0ul) randx=1ul;
	randx2=randx;
	for (int i=nb+7;i>=0;i--) {
		unsigned long t1, t2;
		t1=a1*(randx%q1);
		t2=r1*(randx/q1);
		randx=(t1>=t2 ? t1-t2 : m1-t2+t1);
		if (i<nb) v[i]=randx;
	};
	y=v[0];
};	

// Draw function.
long Random4::draw() {
	unsigned long t1, t2;
	int i;
	t1=a1*(randx%q1);
	t2=r1*(randx/q1);
	randx=(t1>=t2 ? t1-t2 : m1-t2+t1);
	t1=a2*(randx2%q2);
	t2=r2*(randx2/q2);
	randx2=(t1>=t2 ? t1-t2 : m2-t2+t1);
	// Produces a number in the range 0 to nb-1.
	i=y/((m1-1)/nb +1);	
	y=(v[i]>randx2 ? v[i]-randx2 : m1-1-(randx2-v[i]));
	v[i]=randx;
	return y;
};

long Random4::ndraw(const vector<double> &pdf) {
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

long Random4::ndraw(const vector<long> &pdf) {
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
pair<double,double>  Random4::gaussian_draw(double ave, double sd) {
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

// assignment operator for Random4
Random4 & Random4::operator=(const Random4 &rng) {
	randx=rng.show_seed();
	randx2=rng.show_seed2();
	rng.get_v(v);
	y=rng.get_y();
	return *this;
};
	
double Random4L::max_ran=2.0e+18;

long Random4L::draw() {
	if (++rn_cnt>max_ran) {
		Error::MAX_RN_REACHED m;
		throw m;
	};
	unsigned long t1, t2;
	int i;
	t1=a1*(randx%q1);
	t2=r1*(randx/q1);
	randx=(t1>=t2 ? t1-t2 : m1-t2+t1);
	t1=a2*(randx2%q2);
	t2=r2*(randx2/q2);
	randx2=(t1>=t2 ? t1-t2 : m2-t2+t1);
	// Produces a number in the range 0 to nb-1.
	i=y/((m1-1)/nb +1);
	y=(v[i]>randx2 ? v[i]-randx2 : m1-1-(randx2-v[i]));
	v[i]=randx;
	return y;
};

long Random4L::ndraw(const vector<double> &pdf) {
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

long Random4L::ndraw(const vector<long> &pdf) {
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

// assignment operator for Random4
Random4L & Random4L::operator=(const Random4 &rng) {
	randx=rng.show_seed();
	randx2=rng.show_seed2();
	rng.get_v(v);
	y=rng.get_y();
	return *this;
};

Random4L & Random4L::operator=(const Random4L &rng) {
	randx=rng.show_seed();
	randx2=rng.show_seed2();
	rng.get_v(v);
	y=rng.get_y();
	rn_cnt=rng.show_cnt();
	return *this;
};

// Draw a double with the gaussian dist. with average and standard deviation.
pair<double,double>  Random4L::gaussian_draw(double ave, double sd) {
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
