// Making the square shaped holes in the initial states of actors.
// And excluded files.
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>

bool if_inside(long x, long y, long x0, long y0, double radius) {
	using namespace std;
	double distance=(x-x0)*(x-x0)+(y-y0)*(y-y0);
	return (sqrt(distance)<(radius+0.00000001));
};
	
int main(int argc, char ** argv) {
	using namespace std;

	if (argc!=5) {
		cerr << "Usage: GenHole <nagents> <xsize> <ysize> <hole-radius> " << '\n';
		exit(1);
	};
	
	const long nagents=atoi(argv[1]);
	const long X=atoi(argv[2]);
	const long Y=atoi(argv[3]);
	const long radius=atoi(argv[4]);
	if (radius>X || radius<1) {
		cerr << "Check the hole sizes." << '\n';
		exit(1);
	};

	long halfX=X/2;
	long halfY=Y/2;

	double g=1;

	long seed=1;
	srand(seed);

	string file1;
	string file2;
	char buffer[10];
	
	sprintf(buffer, "%d", nagents);
	file2=string("agents_n")+buffer;
	file1=string("points_n")+buffer;
	sprintf(buffer, "%d", X);
	file2+="_x";
	file1+="_x";
	file2+=buffer;
	file1+=buffer;
	sprintf(buffer, "%d", Y);
	file2+="_y";
	file1+="_y";
	file2+=buffer;
	file1+=buffer;
	sprintf(buffer, "%d", radius);
	file2+="_r";
	file1+="_r";
	file2+=buffer;
	file1+=buffer;
	file2+="_period1.in";

	ofstream ofile2;
	ofstream ofile1;

	ofile2.open(file2.c_str(),ios::out);
	for (int n=0;n<nagents;n++) {
		long x,y;
		do {
			x=rand()%X;
			y=rand()%Y;
//cout << x << y <<endl;
		} while (if_inside(x,y,halfX,halfY,radius));
		double p=double(x)/X+1/(2*double(X));
		ofile2 << n << '\t' << x << '\t' << y << '\t' << p << '\t' << g << '\n';
	};
	ofile2.close();

	ofile1.open(file1.c_str(),ios::out);
	for (int x=0;x<X;x++)
		for (int y=0;y<Y;y++)
			if (if_inside(x,y,halfX,halfY,radius)) ofile1 << x << '\t' << y << '\n';
	ofile1.close();
	return 0;
};
