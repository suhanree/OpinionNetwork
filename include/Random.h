// 
// 	Filename : 	Random.h 
//
//	Author : Suhan Ree
//	Date   : 11-01-2002

// The random number generators, inherited from this base class,
// are basically using
// the linear congruential method of Park and Miller with Schrage's
// algorithm, and Bays and Durham's shuffling algorithm.
// (Ref. Numerical Recipes in C++).

// Obtained the idea of this structure of the classes from
// "C++ Complete handbook" by Straustrub.

#ifndef RANDOM_H
#define RANDOM_H

//
// A base class for the random number generator class.
//
class Random {
   public :
	// Constructor.
	Random(unsigned long s=1) : randx(s) {};	
	// Destructor.
	~Random() {};	
	// Show the seed.
	unsigned long show_seed() const {return randx;};	

	// Provides a seed.
	void seed(const unsigned long &s) {randx=s;};	

   protected :
	// A seed for the random number generator (faster when randx is used
	// directly in "draw" functions -> protected).
	unsigned long randx;	
};

#endif
