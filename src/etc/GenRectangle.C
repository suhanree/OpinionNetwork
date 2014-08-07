// Making the square shaped holes in the initial states of actors.
// And excluded files.
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>


int main(int argc, char ** argv) {
	using namespace std;

	if (argc!=6) {
		cerr << "Usage: GenHole <nagents> <xsize> <ysize> <hole-xsize> <hole-ysize>" << '\n';
		exit(1);
	};
	
	const long nagents=atoi(argv[1]);
	const long X=atoi(argv[2]);
	const long Y=atoi(argv[3]);
	const long HoleX=atoi(argv[4]);
	const long HoleY=atoi(argv[5]);
	if (HoleX>X || HoleY>Y || HoleX<1 || HoleY<1) {
		cerr << "Check the hole sizes." << '\n';
		exit(1);
	};

	long halfX=X/2;
	long halfY=Y/2;
	long xmax=halfX+HoleX/2-(HoleX%2==0?1:0);
	long xmin=halfX-HoleX/2;
	long ymax=halfY+HoleY/2-(HoleY%2==0?1:0);
	long ymin=halfY-HoleY/2;
//cout << xmin << xmax << ymin << ymax << endl;

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
	sprintf(buffer, "%d", HoleX);
	file2+="_h";
	file1+="_h";
	file2+=buffer;
	file1+=buffer;
	if (HoleX!=HoleY) {
		sprintf(buffer, "%d", HoleY);
		file2+="X";
		file1+="X";
		file2+=buffer;
		file1+=buffer;
	};
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
		} while (x>=xmin && x<=xmax && y>=ymin && y<=ymax);
		double p=double(x)/X+1/(2*double(X));
		ofile2 << n << '\t' << x << '\t' << y << '\t' << p << '\t' << g << '\n';
	};
	ofile2.close();

	ofile1.open(file1.c_str(),ios::out);
	for (int x=xmin;x<=xmax;x++)
		for (int y=ymin;y<=ymax;y++)
			ofile1 << x << '\t' << y << '\n';
	ofile1.close();
	return 0;
};
