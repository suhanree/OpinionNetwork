// 
// 	Filename : 	Gaussian.h 
//
//	Author : Suhan Ree
//	Date   : 11-20-2002

// This is the random number generator with Gaussian distribution.
// Used the Box-Muller method (Ref. Numerical Recipes in C++, gasdev).
// It would be better to use with the generator "Random3" because it
// doesn't have the sequential correlation problem.

// Usage : 	int s=100;    // Seed = 100
//		Gaussian g(s);	// Instantiation when ave=0,var=1.
//				// Or in general, g(s, ave, var).
//		for (int i=0; i<10000; i++) g.draw();

#ifndef GAUSSIAN_H
#define GAUSSIAN_H

#include "Random3.h"

//
// A class for the random number generator with the Gaussian.
//	(It contains the Random3 class as a data member.)
class Gaussian {
   public :
	// Constructor.
	Gaussian(unsigned long seed=1, const double ave=0.0, const double var=1.0);	
	// Destructor.
	~Gaussian() {};	
	
	// Drawing a number with the Gausssian distribution.
	double draw();	

   private :
	double average;
	double variance;

	Random3 ran;
	bool set;	// Temporary variable for the member functions.
	double gset;	// Temporary variable for the member functions.

};

#endif
