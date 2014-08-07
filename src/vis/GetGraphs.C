// 
// 	Filename : GetGraphs.C
//
//	Author : Suhan Ree
//	Date   : 09-20-2010

#include "Utilities.h"
#include "Types.h"
#include "Errors.h"
#include "Input.h"
#include "InputParam.h"
#include "Output.h"
#include "Point.h"
#include "Random4.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <list>
#include <set>
#include <map>

using namespace std;

double find_op(const std::multiset<double> &temset, Random4 ran) {
	long size=temset.size();
	if (size==0)
		return -1;
	else {
		int count=ran.ndraw(0,size-1);
		for (multiset<double>::const_iterator i=temset.begin();i!=temset.end();i++) {
			if (count==0) {
				return *i;
			};
			count--;
		};
	};
	return -1;
};

int main(int argc, char **argv) {

	// Command line input test.
	if (argc!=2) {
		cerr << " Usage: GetMath <input filename> (To produce data file for Mathematica)\n";
		exit(1);
	};
	// Input filename in a string.
	string infile(argv[1]);

try {
	//===============================================================
	//=================(Input Parameters)============================
	long nagents;
	long xsize;
	long ysize;

	long i_time;
	long f_time;
	long time_interval;
	long given_time; // when method=4 only, output the snapthot for this time only.
	int graph_method; // 1: For Mathematica, 2: For gnuplot
	string in_file;

	//===============================================================
	//==============(Reading Input Parameters)=======================
	cout << "1, Reading the input parameters..." << endl;
	InputParam in1(infile);
	in1.read();
	// in1.print_key_val();
	if (!in1.get("nagents",nagents,cerr)) {
		cerr << "# No parameter given: nagents \n";
		exit(1);
	};
	if (!in1.get("xsize",xsize,cerr)) {
		cerr << "# No parameter given: xsize \n";
		exit(1);
	};
	if (!in1.get("ysize",ysize,cerr)) {
		cerr << "# No parameter given: ysize \n";
		exit(1);
	};
	if (!in1.get("i_time",i_time,cerr)) {
		cerr << "# No parameter given: i_time \n";
		exit(1);
	};
	if (!in1.get("f_time",f_time,cerr)) {
		cerr << "# No parameter given: f_time \n";
		exit(1);
	};
	if (!in1.get("time_interval",time_interval,cerr)) {
		cerr << "# No parameter given: time_interval \n";
		exit(1);
	};
	if (!in1.get("graph_method",graph_method,cerr)) {
		cerr << "# No parameter given: graph_method \n";
		exit(1);
	};
	if (graph_method==4 && !in1.get("given_time",given_time,cerr)) {
		cerr << "# No parameter given: given_time \n";
		exit(1);
	};
	if (!in1.get("in_file",in_file,cerr)) {
		cerr << "# No parameter given: in_file \n";
		exit(1);
	};

	// close the input parameter file.
	in1.close();

	cout << "nagents\t" << nagents << endl;
	cout << "xsize\t" << xsize << endl;
	cout << "ysize\t" << ysize << endl;
	//==============================================================
	//=============(Setting Up : Initialization)====================
	cout << "2, Converting..." << endl;

	Input in2(in_file);
	int timewidth=7;
	Random4 ran(10000);
	char buffer[20];

	long time, tem_id, tem_x, tem_y;
	double tem_p, tem_g;

   if (graph_method!=4) {
	// For each time step.
	for (long t=i_time;t<=f_time;t+=time_interval) {
		// Skip the data with different times.
		while(in2.read(time)) {
			if (time<t) {
				if (!in2.read_lines(nagents)) {
					Error::Bad_Input_File badfile(in_file);
					throw badfile; };
			}
			else if (time==t) {
				string out_file(in_file);
				int numzerofront;
				if (time==0) 
					numzerofront=timewidth-1;
				else
					numzerofront=timewidth-int(log10(time+0.5))-1;
				out_file+="_t";
				for (int j=0;j<numzerofront;j++)
					out_file+="0";
				//itoa(time,buffer,10);
				sprintf(buffer,"%ld",time);
				out_file+=buffer;
				string out_file0=out_file+".data"; // Data for x vs p graph
				string out_file1=out_file+".data1"; // Data for mathematica
				string out_file2=out_file+".data2"; // Data for gnuplot
				Output out0(out_file0);

				map<Point2DInt,multiset<double>,Point2DIntLessThan> opinionset;
				multiset<double> vacantset;
				for (long x=0;x<xsize;x++)
					for (long y=0;y<ysize;y++)
						opinionset[Point2DInt(x,y)]=vacantset;
				in2.read(tem_id);in2.read(tem_x);in2.read(tem_y); 
				in2.read(tem_p);in2.read(tem_g);
				if (graph_method==2 || graph_method==3) {
					out0.write(tem_x); out0.write('\t');
					out0.write(tem_y); out0.write('\t');
					out0.write(tem_p);out0.write('\n');
				};
				opinionset[Point2DInt(tem_x,tem_y)].insert(tem_p);
				for (int n=1;n<nagents;n++) {
					in2.read(time);in2.read(tem_id);in2.read(tem_x);
					in2.read(tem_y);in2.read(tem_p);in2.read(tem_g);
					opinionset[Point2DInt(tem_x,tem_y)].insert(tem_p);
					if (graph_method==2 || graph_method==3) {
						out0.write(tem_x); out0.write('\t'); 
						out0.write(tem_y); out0.write('\t');
						out0.write(tem_p);out0.write('\n');
					};
				};
				out0.close();

				vector<vector<double> > density(xsize);
				vector<double> temp(ysize);
				for (long i=0;i<ysize;i++) temp[i]=-1;
				for (long i=0;i<xsize;i++) density[i]=temp;

				for (int x=0;x<xsize;x++) {
					for (int y=0;y<ysize;y++) {
						double op;
						long size=opinionset[Point2DInt(x,y)].size();
						if (size==1) {
							density[x][y]=*(opinionset[Point2DInt(x,y)].begin());
						}
						else {
							density[x][y]=find_op(opinionset[Point2DInt(x,y)],ran);
						};
					};
				};
// for (int x=0;x<xsize;x++) { for (int y=0;y<ysize;y++) {cout << x << y << density[x][y] << endl;}};

				long cnt_empty=0;
				if (graph_method==1 || graph_method==3) {
					Output out1(out_file1);
					for (int y=ysize-1;y>=0;y--) {
						for (int x=0;x<xsize;x++) {
							out1.write(density[x][y]);
							if (density[x][y]<-0.5) {
								cnt_empty++;
							};
							out1.write('\t');
						};
						out1.write('\n');
					};
					out1.close();
				};
				if (graph_method==2 || graph_method==3) {
					Output out2(out_file2);
					for (int x=0;x<xsize;x++) {
						for (int y=0;y<ysize;y++) {
							if (density[x][y]<-0.5) cnt_empty++;
							out2.write(x);
							out2.write('\t');
							out2.write(y);
							out2.write('\t');
							out2.write(density[x][y]);	
							out2.write('\n');
							out2.write(x);
							out2.write('\t');
							out2.write(y+1);
							out2.write('\t');
							out2.write(density[x][y]);	
							out2.write('\n');
						};
						out2.write('\n');
						for (int y=0;y<ysize;y++) {
							out2.write(x+1);
							out2.write('\t');
							out2.write(y);
							out2.write('\t');
							out2.write(density[x][y]);	
							out2.write('\n');
							out2.write(x+1);
							out2.write('\t');
							out2.write(y+1);
							out2.write('\t');
							out2.write(density[x][y]);	
							out2.write('\n');
						};
						out2.write('\n');
					};
					out2.close();
				};
				
				cout << " At Time = " << time << ", empty points: " << cnt_empty << endl;

				string out_file_m=out_file+".m";
				string out_file_g=out_file+".gnuplot";
				string out_file_gif0=out_file+"_X.gif";
				string out_file_gif1=out_file+"_m.gif";
				string out_file_gif2=out_file+"_g.gif";

				string tempstr;
				if (graph_method==1 || graph_method==3) {
					Output out_m(out_file_m);
					tempstr="data=Import[\""+out_file1+"\",\"Table\"]";
					out_m.write(tempstr); out_m.write('\n');
					tempstr="ArrayPlot[data, ColorFunction->Hue, PlotRange->{0,1}]";
					//tempstr="ArrayPlot[data]";
					out_m.write(tempstr); out_m.write('\n');
					tempstr="Export[\""+out_file_gif1+"\",%]";
					out_m.write(tempstr); out_m.write('\n');
					out_m.close();
					tempstr="math < "+out_file_m + " > /dev/null";
					//system(tempstr.c_str());

					// tempstr="rm "+out_file1;
					// system(tempstr.c_str());
					// tempstr="rm "+out_file_m;
					// system(tempstr.c_str());
				};
				if (graph_method==2 || graph_method==3) {
					Output out_g(out_file_g);
					sprintf(buffer,"%ld",time);
					tempstr=string("set title \"T=")+buffer+"\"\n";
					out_g.write(tempstr);
					out_g.write("set term gif\n");
					tempstr="set output \""+out_file_gif2+"\"\n";
					out_g.write(tempstr);
					out_g.write("set pm3d map\n");
					out_g.write("set palette defined (-1 \"white\", 0 \"white\", 1 \"black\") \n");
					sprintf(buffer,"%ld",xsize);
					tempstr=string("set xrange [0:")+buffer+"]\n";
					out_g.write(tempstr);
					sprintf(buffer,"%ld",ysize);
					tempstr=string("set yrange [0:")+buffer+"]\n";
					out_g.write(tempstr);
					out_g.write("set zrange [-2:1]\n");
					tempstr="splot \'"+out_file2+"\'\n";
					out_g.write(tempstr);
					tempstr="set output \""+out_file_gif0+"\"\n";
					out_g.write(tempstr);
					out_g.write("set yrange [0:1]\n");
					tempstr="plot \'"+out_file0+"\' using 1:3 with dots\n";
					out_g.write(tempstr);
					out_g.close();
					tempstr="gnuplot < "+out_file_g;
					system(tempstr.c_str());
					
				};
				break; 
			}
			else {
// cout << time << '\t' << t << endl;
				cerr << " # Bad timestep." << endl;
				exit(1);
			};
		};
	};
   }
   else { // only for ring structure
	while(in2.read(time)) {
		if (time<given_time) {
			if (!in2.read_lines(nagents)) {
				Error::Bad_Input_File badfile(in_file);
				throw badfile; };
		}
		else if (time==given_time) {
			string out_file(in_file);
			string out_file0=out_file+".data"; // Data for x vs p graph
			Output out0(out_file0);

			in2.read(tem_id);in2.read(tem_x);in2.read(tem_y); 
			in2.read(tem_p);in2.read(tem_g);
			out0.write(tem_x); out0.write('\t');
			out0.write(tem_p);out0.write('\n');
			for (int n=1;n<nagents;n++) {
				in2.read(time);in2.read(tem_id);in2.read(tem_x);
				in2.read(tem_y);in2.read(tem_p);in2.read(tem_g);
				out0.write(tem_x); out0.write('\t'); 
				out0.write(tem_p);out0.write('\n');
			};
			out0.close();

			string out_file_g=out_file+".gnuplot";
			string out_file_gif=out_file+".gif";

			string tempstr;
			Output out_g(out_file_g);
			sprintf(buffer,"%ld",time);
			tempstr=string("set title \"T=")+buffer+"\"\n";
			out_g.write(tempstr);
			out_g.write("set term gif\n");
			tempstr="set output \""+out_file_gif+"\"\n";
			out_g.write(tempstr);
			out_g.write("set yrange [0:1]\n");
			tempstr="plot \'"+out_file0+"\' using 1:2\n";
			//tempstr="plot \'"+out_file0+"\' using 1:2 with dots\n";
			out_g.write(tempstr);
			out_g.close();
			tempstr="gnuplot < "+out_file_g;
			system(tempstr.c_str());
			
		break; 
		};
   	};
   };
}
   catch (Error::Bad_Input_File badfile) {
	if (badfile.filename.size()!=0) 
   		cerr << "# Bad input file: " << badfile.filename << ".\n";
	else
   		cerr << "# Bad input file.\n";
		
	exit(1);
   };

	cout << "   Done." << endl;

	return 0;
};
