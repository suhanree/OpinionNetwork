// 
// 	Filename : Point.h
//
//	Author : Suhan Ree
//	Date   : 06-04-2004
//
//	Defines the classes for 2D points and toroidal 2D points (integer).

#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <fstream>

// class for 2D integer.
class Point2DInt {
   public :
   	// Constructor.
	Point2DInt() : x(0), y(0) {};
	Point2DInt(long ix, long iy)
		: x(ix), y(iy) {};
	// Destructor.
	~Point2DInt() {};

	// Change x and y values.
	void update_x(long lx) {
		x=lx;
	};
	void update_y(long ly) {
		y=ly;
	};
	void update_pos(long ix, long iy) {
		x=ix; y=iy;
	};
	void update_pos(const Point2DInt & pos) {
		x=pos.x; y=pos.y;
	};
	
	void get_right() {};

	// Read the point from a file.
	bool read(std::ifstream &ifile) {
		return ifile >> x >> y;
	};

	// get the values.
	long get_x() const {return x;};
	long get_y() const {return y;};

	// Set the size of the square grid.
	static void set_size(long xs, long ys) {
		xsize=xs;
		ysize=ys;
	};

	// Get the size.
	static long get_xsize() {
		return xsize;
	};
	static long get_ysize() {
		return ysize;
	};

	// check the point is inside the grid.
	bool if_inside() const {
		return (x>=0 && x<xsize && y>=0 && y<ysize);
	};

	// Print the values.
	void print() const {
		std::cout << '(' << x << ',' << y << ")\n";
	};
	void write(std::ofstream &of) const {
		of << x << '\t' << y << '\n';
	};

	// overloading the unary operators +=, -=, -
	Point2DInt & operator+=(Point2DInt p2) {
		x+=p2.x; y+=p2.y;
		return *this;
	};
	Point2DInt & operator-=(Point2DInt p2) {
		x-=p2.x; y-=p2.y;
		return *this;
	};
	Point2DInt operator-() {
		return Point2DInt(-x,-y);
	};
	
	// overloading the binary operators, ==, +, -.
	bool operator==(const Point2DInt p2) const {
		return (x==p2.x && y==p2.y);
	};
	Point2DInt operator+(Point2DInt p2) const {
		return (p2+=*this);
	};
	Point2DInt operator-(Point2DInt p2) const {
		return (-(p2-=*this));
	};

   public : // To access the point values easier.
   	long x, y;
   
   private :
	static long xsize;
	static long ysize;
};

// A class that defines a 2D torus.
class Torus {
   public:
   	Torus(): xsize(10), ysize(10) {};
   	Torus(long xs, long ys);
	~Torus() {};

	void set_size(long xs, long ys) {
		xsize=xs;
		ysize=ys;
	};

	long xsize;
	long ysize;
};

// A class that defines a point in a 2D torus.
class Point2DIntTorus : public Point2DInt {
   public :
   	// Constructors.
   	Point2DIntTorus(): Point2DInt() {};
	Point2DIntTorus(long ix, long iy): Point2DInt(ix,iy) {
		this->torus();
	};
	Point2DIntTorus(const Point2DInt &pos1): Point2DInt(pos1) {
		this->torus();
	};
	Point2DIntTorus(const Point2DIntTorus &pos1): Point2DInt(pos1.x, pos1.y) {};

	// Destructor.
	~Point2DIntTorus() {};

	// Change x and y values.
	void update_x(long lx) {
		x=lx;
		(x>=0? x%=tor.xsize : x=tor.xsize+x%tor.xsize);
	};
	void update_y(long ly) {
		y=ly;
		(y>=0? y%=tor.ysize : y=tor.ysize+y%tor.ysize);
	};
	void update_pos(long ix, long iy) {
		x=ix; y=iy;
		this->torus();
	};
	void update_pos(const Point2DInt & pos) {
		x=pos.x; y=pos.y;
		this->torus();
	};
	void update_pos(const Point2DIntTorus & pos) {
		x=pos.x; y=pos.y;
	};

	void get_right() {
		torus();
	};

	// Read the point from a file.
	bool read(std::ifstream &ifile) {
		bool tf = (ifile >> x >> y);
		this->torus();
		return tf;
	};

	// find the modularized point.
	void torus();

	// Set the torus size.
	static void set_size(long xs, long ys) {
		tor.set_size(xs,ys);
	};

	// Get the torus size.
	static long get_xsize() {
		return tor.xsize;
	};
	static long get_ysize() {
		return tor.ysize;
	};

	// check the point is inside the grid. (always true for the torus).
	bool if_inside() const {
		return true;
	};

	// Print the values.
	void print() const {
		std::cout << '(' << x << ',' << y << ")\n";
	};
	void write(std::ofstream &of) const {
		of << x << '\t' << y << '\n';
	};

	// overloading the unary operators +=, -=, -
	Point2DIntTorus & operator+=(Point2DIntTorus p2) {
		x+=p2.x; y+=p2.y;
		this->torus();
		return *this;
	};
	Point2DIntTorus & operator-=(Point2DIntTorus p2) {
		x-=p2.x; y-=p2.y;
		this->torus();
		return *this;
	};
	Point2DIntTorus operator-() {
		return Point2DIntTorus(-x,-y);
	};
	
	// overloading the binary operators, ==, +, -.
	bool operator==(const Point2DIntTorus p2) const {
		return (x==p2.x && y==p2.y);
	};
	Point2DIntTorus operator+(Point2DIntTorus p2) const {
		p2+=*this;
		p2.torus();
		return (p2);
	};
	Point2DIntTorus operator-(Point2DIntTorus p2) const {
		p2-=*this;
		return p2=-p2;
	};

   public :
	static Torus tor;
};

// A class that defines the "less than" function for the 2D Point class.
class Point2DIntLessThan {
public :
	inline bool operator() (const Point2DInt & p1, const Point2DInt & p2) {
		return (p1.y==p2.y ? p1.x < p2.x : p1.y < p2.y);
	};
};

// A class that defines the "less than" function for the toroidal 2D Point class.
class Point2DIntTorusLessThan {
public :
	inline bool operator() (const Point2DIntTorus & p1, const Point2DIntTorus & p2) {
		return (p1.y==p2.y ? p1.x < p2.x : p1.y < p2.y);
	};
};

// outstream operator overloading for Point2DInt.
std::ostream & operator<<(std::ostream &s, const Point2DInt &p);

// outstream operator overloading for Point2DIntTorus.
std::ostream & operator<<(std::ostream &s, const Point2DIntTorus &p);

#endif
