// 
// 	Filename : 	Random2.h 
//
//	Author : Suhan Ree
//	Date   : 06-11-2004

#ifndef RANDOM2_H
#define RANDOM2_H

#include "Random.h"
#include <vector>
#include <utility>

//
// A derived class for the random number generator class.
// Using Park and Miller with Schrage's algorithm. (RAN0 in NR)
// It would be adequate for less than 10^8 random numbers. 
// (portable).
//

class Random2 : public Random {
   public :
	// Constructor.
   	Random2(unsigned long s=0) : Random(s) {};	

	// Destructor.
   	~Random2() {};	

	// Maximum value converted to double.
	double rand_max() {return 2.147483646e+9;};	

	// Period of the generator.
	double period() {return 2.147483646e+9;}

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

	// assignment operator for Random2
	Random2 & operator=(const Random2 &rng) {
		randx=rng.show_seed();
		return *this;
	};
};

// Class of RNG that has the limit for the number of random numbers used.
class Random2L : public Random2 {
   public :
	// Constructor.
   	Random2L(unsigned long s=0) : Random2(s), rn_cnt(0) {};	
	// Destructor.
   	~Random2L() {};	
	
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
	long show_cnt() const {
		return rn_cnt;
	};

	// Set the rn_cnt.
	void set_cnt(long cnt) {
		rn_cnt=cnt;
	};

	// Get the maximum number of random numbers one agent can use.
	static long get_max_ran() {
		return max_ran;
	};

	// Set the maximum number of random numbers one agent can use.
	static void set_max_ran(long m) {
		max_ran=m;
	};

	// assignment operator for Random2L
	Random2L & operator=(const Random2 &rng) {
		randx=rng.show_seed();
		return *this;
	};

	Random2L & operator=(const Random2L &rng) {
		randx=rng.show_seed();
		rn_cnt=rng.show_cnt();
		return *this;
	};

   private :
	long rn_cnt;
	static long max_ran;
};

#endif
