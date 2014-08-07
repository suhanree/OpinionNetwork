// 
// 	Filename : 	Random3.h 
//
//	Author : Suhan Ree
//	Date   : 06-11-2004

#ifndef RANDOM3_H
#define RANDOM3_H

#include "Random.h"
#include <vector>
#include <valarray>
#include <utility>

//
// A derived class for the random number generator class.
// Using Bays and Durham's algorithm. (RAN1 in NR)
// Unlike the method used in "Random2", the problem of 
// the sequential correlation is solved.
// Still, it would be adequate for less than 10^8 random numbers. 
// If more random numbers are needed, use "Random4".
//

class Random3 : public Random {
   public :
	// Constructor.
   	Random3(unsigned long s=0);

	// Destructor.
   	~Random3() {};	

	// Provides a seed. (v has to be changed too)
	void seed(const unsigned long &s);	

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

	// assignment operator for Random3
	Random3 & operator=(const Random3 &rng);

	// Show values of data members.
	void get_v(std::valarray<unsigned long> &v1) const {
		v1=v;
	};

	unsigned long get_y() const {
		return y;
	};

   protected :
	std::valarray<unsigned long> v;
	unsigned long y;
};

// Class of RNG that has the limit for the number of random numbers used.
class Random3L : public Random3 {
   public :
	// Constructor.
   	Random3L(unsigned long s=0) : Random3(s), rn_cnt(0) {};	
	// Destructor.
   	~Random3L() {};	
	
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

	// assignment operator for Random3L
	Random3L & operator=(const Random3 &rng);
	Random3L & operator=(const Random3L &rng);

   private :
	long rn_cnt;
	static long max_ran;
};

#endif
