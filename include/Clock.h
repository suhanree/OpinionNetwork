// 
// 	Filename : Clock.h
//
//	Author : Suhan Ree
//	Date   : 08-26-2003

#ifndef CLOCK_H
#define CLOCK_H

#include <iostream>
#include <fstream>

// A class that represents a clock.

class Clock {
   public:
   	Clock(): sec(0) {};
	Clock(long sec1) {
		sec=(sec1>0 ? sec1 : 0);
	};
	~Clock() {};

	// Incease the second by one and return the increased time.
	long tick() {
		return ++sec;
	};

	// Decease the second by one and return the decreased time.
	long downtick() {
		return --sec;
	};

	// Returns true if the current time is divided by the given interval.
	bool interval(long inter) {
		bool tf=(sec % inter ? false : true);
		return tf;
	};

	// Set the time.
	long set(long sec1) {
		return sec=(sec1>0 ? sec1 : 0);
	};
	
	// Show the time.
	long get() const {
		return sec;
	};

	// Print the time.
	void print(long interval=1) const {
		if (!(sec%interval)) std::cout << "Time: " << sec << std::endl;
	};

	// write the time.
	void write(std::ofstream &ofile, long interval=1) const {
		if (!(sec%interval)) ofile << "Time\t" << sec << '\n';
	};

   private:
   	long sec;
};

#endif

