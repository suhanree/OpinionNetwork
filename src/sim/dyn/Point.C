// 
// 	Filename : Point.C
//
//	Author : Suhan Ree
//	Date   : 06-04-2004
//
//	Defines the classes for 2D points and toroidal 2D points (integer).

#include "Point.h"
#include "Errors.h"

using namespace std;

// Assigning the initial value for the static data member.
long Point2DInt::xsize=10;
long Point2DInt::ysize=10;

// Constructor for Torus class
Torus::Torus(long xs, long ys) {
	if (xs>0 && ys>0) {
		xsize=xs;
		ysize=ys;
	}
	else 
		throw Error::Bad_Torus_Size();
};

// find the modularized point.
void Point2DIntTorus::torus() {
	(x>=0? x%=tor.xsize : x=tor.xsize+x%tor.xsize);
	(y>=0? y%=tor.ysize : y=tor.ysize+y%tor.ysize);
};

// Assigning the initial value for the static data member.
Torus Point2DIntTorus::tor=Torus(10,10);

// outstream operator overloading for Point2DInt. 
ostream & operator<<(ostream &s, const Point2DInt &p) {
	return s << '(' << p.x << ',' << p.y << ')';
};

// outstream operator overloading for Point2DIntTorus.
ostream & operator<<(ostream &s, const Point2DIntTorus &p) {
	return s << '(' << p.x << ',' << p.y << ')';
};
