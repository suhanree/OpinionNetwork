// 
// 	Filename : RWState.h
//
//	Author : Suhan Ree
//	Date   : 06-04-2004
//
//	For the RW2 problem: each agent has an opinion (0<op<1) and gullibility (0<=gu<=1).

#ifndef RWSTATE_H
#define RWSTATE_H

#include <iostream>
#include <fstream>
#include "Point.h"
#include "Types.h"

#define epsilon 1.0e-5	// Very small number.

// A class that defines a state in RW2 problem.
class RWState {
   public :
   	// Constructors.
   	RWState(): pos(0,0), op(0.5), gu(0.5) {};
	RWState(long ix, long iy): pos(ix,iy), op(0.5), gu(0.5) {};
	RWState(const Point &pos1): pos(pos1), op(0.5), gu(0.5) {};
	RWState(long ix, long iy, double op1, double gu1): pos(ix,iy) { 
		update_op(op1); update_gu(gu1);
	};
	RWState(const Point & pos1, double op1, double gu1): pos(pos1) {
		update_op(op1); update_gu(gu1);
	};

	// Destructor.
	~RWState() {};

	// Change x and y values.
	void update_x(long lx) {
		pos.x=lx;
		pos.get_right();
//		(pos.x>=0? pos.x%=pos.tor.xsize : pos.x=pos.tor.xsize+pos.x%pos.tor.xsize);
	};
	void update_y(long ly) {
		pos.y=ly;
		pos.get_right();
//		(pos.y>=0? pos.y%=pos.tor.ysize : pos.y=pos.tor.ysize+pos.y%pos.tor.ysize);
	};
	void update_pos(long ix, long iy) {
		pos.x=ix; pos.y=iy;
		pos.get_right();
//		pos.torus();
	};
	void update_pos(const Point & pos1) {
		pos.x=pos1.x; pos.y=pos1.y;
		pos.get_right();
//		pos.torus();
	};

	// Change op and gu.
	void update_op(double op1) {
		if (op1<=0.0-epsilon)
			op=0.0;
		else if (op1>=1.0+epsilon) 
			op=1.0;
		else
			op=op1;
	};

	void update_gu(double gu1) {
		if (gu1<0.0-epsilon)
			gu=0.0;
		else if (gu1>1.0+epsilon) 
			gu=1.0;
		else
			gu=gu1;
	};

	// Update the whole state.
	void update(long ix, long iy, double op1, double gu1) {
		update_pos(ix,iy);
		update_op(op1);
		update_gu(gu1);
	};
	void update(const RWState & st) {
		pos.x=st.get_pos().x; pos.y=st.get_pos().y; op=st.get_op(); gu=st.get_gu();
	};
	
	// Read the point from a file.
	bool read(std::ifstream &ifile) {
		bool tf = (ifile >> pos.x >> pos.y >> op >> gu);
		pos.get_right();
//		pos.torus();
		if (op<=0 || op>=1 || gu<0-epsilon || gu>1+epsilon)
			return false;
		return tf;
	};

	// Get the agent postition.
	Point get_pos() const {
		return pos;
	};

	// Get the agent values.
	double get_op() const {
		return op;
	};
	double get_gu() const {
		return gu;
	};

	// Get the topology of the opinion space.
	static short get_op_topology() {
		return opinion_topology;
	};

	// Set the topology of the opinion space.
	static void set_op_topology(short topo) {
		opinion_topology=topo;
	};

	// Print the values.
	void print() const {
		std::cout << '(' << pos.x << ',' << pos.y << ')' << '\t' << op << '\t' << gu << '\n';
	};
	void write(std::ofstream &of) const {
		of << pos.x << '\t' << pos.y << '\t' << op << '\t' << gu << '\n';
	};

   private :
   	Point	pos; // Position of the agent.
	double op;	// Opinion of the agent. (0<op<1)
	double gu;	// Gullibility of the agent. (0<=gu<=1)
	
	// Topology of the opinion space. (1 when linear, 2 when circular).
	static short opinion_topology;
};

// A class that defines the "less than" function for the RWState class.
class RWStateLessThan {
public :
	inline bool operator() (const RWState & st1, const RWState & st2) {
		return (st1.get_pos().y==st2.get_pos().y ? \
			st1.get_pos().x < st2.get_pos().x : st1.get_pos().y < st2.get_pos().y);
	};
};

// outstream operator overloading for RWState.
std::ostream & operator<<(std::ostream &s, const RWState &p);

#endif
