// 
// 	Filename : 	Discrete.h 
//
//	Author : Suhan Ree
//	Date   : 11-20-2002

// This is the random number generator with a discrete distribution.
// Using the two methods : rejection method and 
//			   cumulative dist.
// It uses the generator "Random3" because it
// doesn't have the sequential correlation problem.

// Usage : 	vector<double> prob(100); // p. d. f. with 100 bins.
//		initialize(prob); 	// Initialize the p.d.f 
//		int s=100;    // Seed = 100
//		Discrete d(prob,s);	// Instantiation, d(prob) is OK.
//		for (int i=0; i<10000; i++) d.draw(); // Draw using
//						// the rejection method.
// OR
//		Discrete_c d(prob,s);	// Instantiation, d(prob) is OK.
//		for (int i=0; i<10000; i++) d.draw(); // Draw using
//						// the cumulative d.f.
// When deciding which method is better, it depends on the problem.
// The rejection method is better when the size of the prob is big and 
// the value of the probabilities are almost the same (which makes the 
// rejection ratio small).
// On the other hand, the cumulative distribution is better when the size 
// of the prob is small.
// (It does not depend on the values of the probabilities.)

#ifndef DISCRETE_H
#define DISCRETE_H

#include "Random3.h"
#include <vector>

using namespace std;

//
// A class for the random number generator with a discrete distribution.
//
class Discrete {
   public :
	// Constructor.
	Discrete(const vector<double> & pr, const unsigned long s=1);
	// Destructor.
	~Discrete() {};	
	
	// Drawing a number (non-negarive integer) i
	// using the rejection method.
	virtual long draw();	
	// Printing the probability.
	virtual void print();
   private :
   	// Normalize the probability distribution.
   	void normalize();
	
   protected :
   	int size;
	Random3 ran;

   private :
	vector<double> prob;
	double max;

};

class Discrete_c : public Discrete {
   public :
	// Constructor.
	Discrete_c(const vector<double> & pr, const unsigned long s=1);
	// Destructor.
	~Discrete_c() {};	
	
	// Drawing a number (non-negarive integer)
	// using the cumulative distribution.
	virtual long draw();	
	// Printing the probability.
	virtual void print();
	
   private :
	vector<double> cumu;
};

#endif
