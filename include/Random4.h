// 
// 	Filename : 	Random4.h 
//
//	Author : Suhan Ree
//	Date   : 06-11-2004

#ifndef RANDOM4_H
#define RANDOM4_H

#include "Random.h"
#include <vector>
#include <valarray>
#include <utility>

//
// A derived class for the random number generator class.
// Using L'Ecuyer's algorithm. (RAN2 in NR)
// The period is about 2x10^18.
//

class Random4 : public Random {
   public :
	// Constructor.
   	Random4(unsigned long s=0);

	// Destructor.
   	~Random4() {};	
	
	// Provides a seed. (v and randx2 have to be changed too)
	void seed(const unsigned long &s);	

	// Maximum value converted to double.
	double rand_max() {return 2.147483562e+9;};	

	// Period of the generator (approximate value).
	double period() {return 2.0e+18;}

	// Drawing a long number between 1 and rand_max().
	long draw();	

	// Draw a long number between nmin and nmax.
	long ndraw(long nmin, long nmax) {
		return nmin+long((double(nmax)-nmin+1)*draw()/(rand_max()+1.0));
	};

	// Draw a long number using the given PDF represented by a vector.
	long ndraw(const std::vector<double> &pdf);
	long ndraw(const std::vector<long> &pdf);

	// Draw a double between fmin(default=0) and fmax(default=1)
	double fdraw(double fmin=0.0, double fmax=1.0) {
		return fmin+(fmax-fmin)*draw()/rand_max();
	};

	// Draw a double with the gaussian dist. with average and standard deviation.
	// Returns two values as a pair of doubles.
	std::pair<double,double> gaussian_draw(double ave=0.0, double sd=1.0);

	// operator version of 'draw()' function
	long operator() () {return draw();};

	// assignment operator for Random3
	Random4 & operator=(const Random4 &rng);

	// Show values of data members.
	unsigned long show_seed2() const {
		return randx2;
	};

	void get_v(std::valarray<unsigned long> &v1) const {
		v1=v;
	};

	unsigned long get_y() const {
		return y;
	};

   protected :
   	unsigned long randx2;	// The second seed.
	std::valarray<unsigned long> v;
	unsigned long y;
};

// Class of RNG that has the limit for the number of random numbers used.
class Random4L : public Random4 {
   public :
	// Constructor.
   	Random4L(unsigned long s=0) : Random4(s), rn_cnt(0) {};	
	// Destructor.
   	~Random4L() {};	
	
	// Drawing a long number between 0 and rand_max().
	long draw();	

	// Draw a long number between nmin and nmax.
	long ndraw(long nmin, long nmax) {
		return nmin+long((double(nmax)-nmin+1)*draw()/(rand_max()+1.0));
	};

	// Draw a long number using the given PDF represented by a vector.
	long ndraw(const std::vector<double> &pdf);
	long ndraw(const std::vector<long> &pdf);

	// Draw a double between fmin(default=0) and fmax(default=1)
	double fdraw(double fmin=0.0, double fmax=1.0) {
		return fmin+(fmax-fmin)*draw()/rand_max();
	};

	// Draw a double with the gaussian dist. with average and standard deviation.
	// Returns two values as a pair of doubles.
	std::pair<double,double> gaussian_draw(double ave=0.0, double sd=1.0);

	// operator version of 'draw()' function
	long operator() () {return draw();};

	// Show the rn_cnt.
	double show_cnt() const {
		return rn_cnt;
	};

	// Set the rn_cnt.
	void set_cnt(double cnt) {
		rn_cnt=cnt;
	};

	// Get the maximum number of random numbers one agent can use.
	static double get_max_ran() {
		return max_ran;
	};

	// Set the maximum number of random numbers one agent can use.
	static void set_max_ran(double m) {
		max_ran=m;
	};

	// assignment operator for Random4L
	Random4L & operator=(const Random4 &rng);
	Random4L & operator=(const Random4L &rng);

   private :
	double rn_cnt;
	static double max_ran;
};

#endif
