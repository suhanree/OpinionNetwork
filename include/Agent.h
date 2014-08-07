// 
// 	Filename : Agent.h
//
//	Author : Suhan Ree
//	Date   : 06-11-2004

#ifndef AGENT_H
#define AGENT_H

#include "Types.h"
#include "Random4.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

// A template class that represents an agent.
// This class contains the T class for the state variables for the 
// problem (which is not yet defined here).
// For a specifice problem, the state class should be defined,
// and the template class should be instantiated with T class.

template<class T> class Agent {
   public :
   	// Constructors.
	Agent(): state() {};
	Agent(const T &st1): state(st1) {};
	// Destructor.
   	~Agent() {};

	// Get values of the state.
	T get_state() const {
		return state;
	};

	// Set values of the state.
	void update(const T &st1) {
		state=st1;
	};

	// Print the information of an agent.
	void print() const {
		state.print();
	};

	void write(std::ofstream &of) const {
		state.write(of);
	};

   private :
   	T state; // State for an agent.
};

// A class that represents an agent with randomness.
// It has a random number generator with its own seed.
// Usage : If the object is agn, 
//	agn.set_seed(seed) will set the seed for the RNG.
//	agn.draw() will return the next random number.
// 	agn.ndraw(nmin,nmax) will draw an integer between nmin and nmax.
// 	agn.ndraw(vector<double> &prob) will draw an integer using the pdf.
// 	agn.fdraw(fmin=0,fmax=1) will draw a double between fmin and fmax.
template<class T> class RAgent {
   public :
   	// Constructors.
	RAgent(): state(), rng() {};
	RAgent(const T &st1, unsigned long in_seed=1)
		: state(st1), rng(in_seed) {};
	// Destructor.
   	~RAgent() {};

	// Get values of the state.
	T get_state() const {
		return state;
	};

	// Get values of the RNG.
	AgentRNGLimit get_rng() const {
		return rng;
	};

	// Set values of the agent. (rn_cnt of RNG will be updated, too.)
	void update(const T &st1, const AgentRNGLimit &rng1) {
		update_state(st1);
		update_rng(rng1);
	};

	// Set values of the state.
	void update_state(const T &st1) {
		state.update(st1);
	};

	// Set values of the RNG. (rn_cnt of RNG will be updated, too.)
	void update_rng(const AgentRNGLimit &rng1) {
		rng=rng1;
	};

	// Set only the seed values of the RNG. (rn_cnt of RNG will NOT be updated.)
	void update_rng_seed(const AgentRNG &rng1) {
		rng=rng1;
	};

	// Print the information of an agent.
	void print() const {
		state.print();
		// Show the seed value and the count of the random number produced.
		std::cout << "seed: " << show_seed() << " (" \
			<< rng.show_cnt() << ')' << std::endl;
	};

	void write(std::ofstream &of) const{
		state.write(of);
	};
	
	// Get seed value.
	unsigned long show_seed() const {
		return rng.show_seed();
	};

	// print seed value.
	void print_seed() const {
		std::cout << rng.show_seed() << '\n';
	};

	// Set the seed value of the RNG.
	void set_seed(unsigned long iseed) {
		rng.seed(iseed);
	};

	// Draw the next number and update the seed value.
	long draw() {
		return rng.draw();
	};

	// Draw a double between fmin and fmax
	double fdraw(double fmin=0.0, double fmax=1.0) {
		return rng.fdraw(fmin,fmax);
	};

	// Draw a long between nmin and nmax
	long ndraw(long nmin, long nmax) {
		return rng.ndraw(nmin,nmax);
	};
	
	// Draw a long using the given PDF represented by a vector.
	// pdf doesn't have to be normalized.
	long ndraw(const std::vector<double> &pdf) {
		return rng.ndraw(pdf);
	};
	long ndraw(const std::vector<long> &pdf) {
		return rng.ndraw(pdf);
	};
	
	// Draw a pair of doubles that satisfy the Gaussian dist.
	std::pair<double,double> gaussian_draw(double ave=0.0, double sd=1.0) {
		return rng.gaussian_draw(ave,sd);
	};

	// Get the maximun number of random numbers it can find.
	double rand_max() {
		return rng.rand_max();
	};

	// Get the maximum number of random numbers one agent can use.
	static long get_max_ran() {
		return AgentRNGLimit::get_max_ran();
	};

	// Set the maximum number of random numbers one agent can use.
	static void set_max_ran(long m) {
		AgentRNGLimit::set_max_ran(m);
	};

   private :
   	T state; // State for an agent.
   	AgentRNGLimit rng; //an RNG
};

#endif
