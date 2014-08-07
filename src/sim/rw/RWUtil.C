// 	Filename : RWUtil.C
//
//	Author : Suhan Ree
//	Date   : 06-25-2004
//
//	Includes utility functions for RW2.

#include <iostream>
#include <string>
#include <set>
#include "Utilities.h"
#include "Graph.h"
#include "Errors.h"
#include "Types.h"
#include "Random1.h"
#include "Random2.h"
#include "Random3.h"
#include "Random4.h"
#include "RWUtil.h"
#include "RWState.h"
#include "RWTypes.h"

#define epsilon 1.0e-5 // Defining the very small number to check the convergence.

// distance between 2 Point2DInt's.
double Util::distance_2DInt(const Point2DInt &p1, const Point2DInt &p2) {
	Point2DInt diff=p1-p2;
	return diff.x+diff.y;
};

// Shortest possible distance between 2 Point's.
// (When points are in a torus, there can be many values.)
double Util::distance_2DInt(const Point2DIntTorus &p1, const Point2DIntTorus &p2) {
	Point2DIntTorus diff=p1-p2;
	long x=diff.x;
	long y=diff.y;
	if (x>Point2DIntTorus::get_xsize()-x) x=Point2DIntTorus::get_xsize()-x;
	if (y>Point2DIntTorus::get_ysize()-y) y=Point2DIntTorus::get_ysize()-y;
	return x+y;
};

// Find the neighbors given a distance for a Point.
void Util::find_rel_neighbors(long d, int neighbor_type, PointSet &pset) {
	pset.clear();
	long sizex=Point::get_xsize(); // size of lattice in x
	long sizey=Point::get_ysize(); // size of lattice in y
	long disx=(d<sizex ? d : sizex-1); // if d>=sizex, d in x should be sizex-1
	long disy=(d<sizey ? d : sizey-1); // if d>=sizey, d in y should be sizey-1
	switch (neighbor_type) {
	   case 1: // von Neumann + (0,0)
		for (long y=-disy;y<=disy;y++) {
			long tem=d-(y>=0 ? y : -y);
			long tem2=(tem<=disx ? tem : disx-1);
			for (long x=-tem2;x<=tem2;x++)
				pset.insert(Point(x,y));
		};
		break;
	   case 2: // von Neumann
		for (long y=-disy;y<=disy;y++) {
			long tem=d-(y>=0 ? y : -y);
			long tem2=(tem<=disx ? tem : disx-1);
			for (long x=-tem2;x<=tem2;x++)
				if (x!=0 || y!=0) {
					pset.insert(Point(x,y));
				};
		};
		break;
	   case 3: // Moore + (0,0)
		for (long y=-disy;y<=disy;y++) {
			for (long x=-disx;x<=disx;x++)
				pset.insert(Point(x,y));
		};
		break;
	   case 4: // Moore
		for (long y=-disy;y<=disy;y++) {
			for (long x=-disx;x<=disx;x++)
				if (x!=0 || y!=0) {
					pset.insert(Point(x,y));
				};
		};
		break;
	   default:
		for (long y=-disy;y<=disy;y++) {
			long tem=d-(y>=0 ? y : -y);
			long tem2=(tem<=disx ? tem : disx-1);
			for (long x=-tem2;x<=tem2;x++)
				pset.insert(Point(x,y));
		};
	};
};
     
void Util::print_state(const PointSet &s) {
	for (PointSet::const_iterator i=s.begin();i!=s.end();i++)
		std::cout << *i << '\n';
};

// Print the set of RWState objects.
// Print the set of class RWAgent.
void Util::print_agent(const AgentSet &s) {
	for (AgentSet::const_iterator i=s.begin();i!=s.end();i++)
		i->print();
};

// Print the vector of class RWAgent.
void Util::print_agent(const AgentVec &avec) {
	long num=avec.size();
	for (long i=0;i<num;i++) {
		std::cout << i << '\t';
		avec[i].print();
	};
};
      
// Print the set of class RWAgent from ID's.
void Util::print_agent(const AgentIDSet &s, const AgentMap &m) {
	for (AgentIDSet::const_iterator i=s.begin();i!=s.end();i++)
		((m.find(*i))->second).print();
};

// Print the map of RWAgent objects.
void Util::print_agent(const AgentMap &m) {
	for (AgentMap::const_iterator i=m.begin();i!=m.end();i++) {
		std::cout << i->first << '\t';
		(i->second).print();
	};
};

// Print the information about all agents graphically.
// This function should be used for (xsize, ysize <20).
void Util::print_agent_screen(const AgentVec &avec) {
	using namespace std;

	long nagents=avec.size();
	if (nagents==0) return;
	long xsize=Point::get_xsize();
	long ysize=Point::get_ysize();
	
	string boundary("|");
	for (long i=0;i<xsize;i++) boundary+=string("-|");

	string *snapshot=new string[ysize];
	for (long i=0;i<ysize;i++) {
		snapshot[i]="|";
		for (long j=0;j<xsize;j++) snapshot[i]+=" |";
	};

	for (AgentID i=0;i<nagents;i++) {
		long ix=avec[i].get_state().get_pos().x;
		long iy=avec[i].get_state().get_pos().y;
		char c[2];
		c[0]=char('0')+i%10;
		c[1]='\0';
		snapshot[iy].replace(ix*2+1,1,c,1);
	};
	
	cout << boundary << endl;
	for (long iy=ysize-1;iy>=0;iy--) {
		cout << snapshot[iy] << endl;
		cout << boundary << endl;
	};
};

// checking the basic input parameters.
void Util::error_check(long nagents, long xsize, long ysize, double gullibility,\
	double standard_dev, double ag_threshold, double op_threshold, \
	short opinion_topology, short op_init_method,\
	int neighbor_type_sg, long agent_max_speed, double wiring_prob, long total_time,\
	long num_edges, unsigned long rseed1, unsigned long rseed2, \
	long max_rn) {
	if (nagents<=0) {
		cerr << "# Bad parameter value: nagents\n";
		exit(1);
	};
	if (double(nagents)*(nagents-1)*wiring_prob*0.9 > 2.1474836475e+9) {
		cerr << "# Bad parameter value: nagents (too big).\n";
		exit(1);
	};
	if (xsize<=0) {
		cerr << "# Bad parameter value: xsize\n";
		exit(1);
	};
	if (ysize<=0) {
		cerr << "# Bad parameter value: ysize\n";
		exit(1);
	};
	if (double(xsize)*ysize > 2.1474836475e+9 ) {
		cerr << "# Bad parameter value: xsize and ysize (too big).\n";
		exit(1);
	};
	if (gullibility<-1.0-epsilon) {
		cerr << "# Bad parameter value: gullibility\n";
		exit(1);
	};
	if (standard_dev<epsilon) {
		cerr << "# Bad parameter value: standard_dev\n";
		exit(1);
	};
	//if (ag_threshold<-epsilon || ag_threshold > 0.5+epsilon) {
		//cerr << "# Bad parameter value: ag_threshold.\n";
		//exit(1);
	//};
	if (op_threshold<-epsilon || op_threshold > 1.0+epsilon) {
		cerr << "# Bad parameter value: op_threshold.\n";
		exit(1);
	};
	if (opinion_topology<1 || opinion_topology > 2) {
		cerr << "# Bad parameter value: opinion_topology.\n";
		exit(1);
	};
	if (op_init_method<1 || op_init_method > 2) {
		cerr << "# Bad parameter value: op_init_method.\n";
		exit(1);
	};
	//if (nagents>xsize*ysize) {
		//cerr << "# Bad parameter value: nagents\n";
		//cerr << "# Too many agents...\n";
		//exit(1);
	//};
	if (neighbor_type_sg<0 || neighbor_type_sg>5 || neighbor_type_sg==2 || neighbor_type_sg==4) {
		cerr << "# Bad parameter value: neighbor_type_sg\n";
		exit(1);
	};
	if (agent_max_speed<0) {
		cerr << "# Bad parameter value: agent_max_speed\n";
		exit(1);
	};
	if (total_time<0) {
		cerr << "# Bad parameter value: total_time\n";
		exit(1);
	};
	if (wiring_prob<0 || wiring_prob>1) {
		cerr << "# Bad parameter value: wiring_prob=" << wiring_prob << '\n';
		exit(1);
	};
	if (double(nagents)*(nagents-1)< 2.1474836475e+9 && static_cast<double>(num_edges) > static_cast<double>(nagents)* \
		(static_cast<double>(nagents)-1.0)) {
		cerr << "# Bad parameter value: too big num_edges, " << num_edges << '\n';
		exit(1);
	};
	if (rseed1==0) {
		cerr << "# Bad parameter value: rseed1\n";
		exit(1);
	};
	if (rseed2==0) {
		cerr << "# Bad parameter value: rseed2\n";
		exit(1);
	};
	if (max_rn==0) {
		cerr << "# Bad parameter value: max_rn\n";
		exit(1);
	};
};

// Initializing a graph.
void Util::initialize_graph(Graph &gr, long num_edges, unsigned long rseed) {
	gr.clear_edges(); // Delete all edges if exists.
	if (num_edges==0) return;

	long nagents=gr.show_vertex_size();
	
	Random4 rng(rseed);
	long max_nedges=nagents*(nagents-1)/(gr.if_directional() ? 1 :2);
	set<long> edgeset;
	do {
		edgeset.insert(rng.ndraw(0,max_nedges-1));
	} while (edgeset.size()<num_edges);

	AgentIDSet vertexset; // Empty set.
	gr.find_vertices(vertexset); // Find all vertices.
	vector<AgentID> agents(nagents);
	long j=0,k;
	for (AgentIDSet::const_iterator i=vertexset.begin(); \
		i!=vertexset.end();i++) {
		agents[j]=*i;
		j++;
	};
	if (gr.if_directional()) {
		for (set<long>::const_iterator i=edgeset.begin();\
			i!=edgeset.end();i++) {
			j=*i/(nagents-1);	// Origin of the edge.
			k=*i%(nagents-1);	// Destination of the edge.
			gr.add_edge(agents[j],(k<j ? agents[k] : agents[k+1]));
		};
	}
	else {
		for (set<long>::const_iterator i=edgeset.begin();\
			i!=edgeset.end();i++) {
			long temp=nagents-1, temp2=*i;
			while (temp>=0) {
				if (temp2<temp) {
					j=temp;
					k=temp2;
					gr.add_edge(agents[j],agents[k]);
					break;
				}
				else {
					temp2-=temp;
					temp--;
				};
			};
		};
	};
};

// Initializing a graph.
void Util::initialize_graph(Graph &gr, double wiring_prob, unsigned long rseed) {
	gr.clear_edges(); // Delete all edges if exists.
	long nagents=gr.show_vertex_size();
	
	Random4 rng(rseed);
	AgentID ori,des;
	AgentIDSet vertexset; // Empty set.

	gr.find_vertices(vertexset); // Find all vertices.

	for (AgentIDSet::const_iterator i=vertexset.begin(); \
		i!=vertexset.end();i++) 
		for (AgentIDSet::const_iterator j=vertexset.begin();\
			j!=vertexset.end();j++)
			if ((gr.if_directional() ? *i!=*j : *i<*j) && rng.fdraw()<wiring_prob)
				gr.add_edge(*i,*j);
};

// Special case of 1-d ring (geometry=0). (bidirectional only)
void Util::initialize_graph0(Graph &gr, long num_edges, int int_range, unsigned long rseed) {
	gr.clear_edges(); // Delete all edges if exists.
	if (num_edges==0) return;

	long nagents=gr.show_vertex_size();
	
	Random4 rng(rseed);
	long max_nedges=nagents*(nagents-1-2*int_range)/2;
	if (num_edges>max_nedges) num_edges=max_nedges;
	set<long> edgeset;
	do {
		edgeset.insert(rng.ndraw(0,max_nedges-1));
	} while (edgeset.size()<num_edges);

	AgentIDSet vertexset; // Empty set.
	gr.find_vertices(vertexset); // Find all vertices.
	vector<AgentID> agents(nagents);
	long j=0,k;
	for (AgentIDSet::const_iterator i=vertexset.begin(); \
		i!=vertexset.end();i++) {
		agents[j]=*i;
		j++;
	};
	for (set<long>::const_iterator i=edgeset.begin();i!=edgeset.end();i++) {
		long temp=nagents-2-int_range, temp2=*i, temp3=int_range;
		while (temp>=0) {
			if (temp2<temp-temp3+1) {
				j=temp+1+int_range;
				k=temp2+temp3;
				gr.add_edge(agents[j],agents[k]);
				break;
			}
			else {
				temp2-=(temp-temp3+1);
				temp--;
				if (temp3>0) temp3--;
			};
		};
	};
};

// Each agent originates an edge with randomly choosing destination.
void Util::initialize_graph2(Graph &gr, unsigned long rseed) {
	gr.clear_edges(); // Delete all edges if exists.
	long nagents=gr.show_vertex_size();
	
	Random3L rng(rseed);
	AgentID ori,des;
	AgentIDSet vertexset; // Empty set.

	gr.find_vertices(vertexset); // Find all vertices.

	// To store ID's in a vector 
	// (then this works also for the case for varying # of agents).
	vector<AgentID> vertexarray(nagents); 
	long ind=0;
	for (AgentIDSet::const_iterator j=vertexset.begin();\
		j!=vertexset.end();j++) {
		vertexarray[ind]=*j;
		ind++;
	};

	for (AgentIDSet::const_iterator i=vertexset.begin(); \
		i!=vertexset.end();i++) {
		AgentID k;
		do {
			k=rng.ndraw(0,nagents-1);
		} while (*i==vertexarray[k]); // Inhibit the self pointing.
		gr.add_edge(*i,vertexarray[k]);
	};
};
     
// Checking states of agents from a file 
// (Returns false if some states are the same)
bool Util::check_agents_pos(AgentVec &avec) {
	PointSet pset;
	for (AgentID i=0;i<avec.size();i++)
		if (!pset.insert(avec[i].get_state().get_pos()).second)
			return false;
	return true;
};

// Initializing agents.
void Util::initialize_agents_state(AgentVec &avec, short op_init_method, double gullibility, double sd,\
	long geometry, PointSet &excluded) {

	long nagents=avec.size();
	if (nagents==0) return;

	long xsize=Point::get_xsize();
	long ysize=Point::get_ysize();
	
	// Special case of 1d ring geometry (no movement of agents).
	if (geometry==0) {
		for (AgentID id=0;id<nagents;id++) {
			double new_op=avec[id].fdraw();
			RWState st(id,0,new_op,1);
			avec[id].update_state(st);
		};
		return;
	};

	Point p;
	if (gullibility<-epsilon)
		// Assuming gu satisfies gaussian(0.5,-gullibility)
		for (AgentID id=0; id<avec.size();id++) {
			do {
				p=Point(avec[id].ndraw(0,xsize-1),avec[id].ndraw(0,ysize-1));
			} while (excluded.size() && excluded.find(p)!=excluded.end());
			RWState st(p.get_x(), p.get_y(), \
				(op_init_method==2 ? double(id)/nagents+0.5/double(nagents) : avec[id].fdraw()),\
				avec[id].gaussian_draw(-gullibility,sd).first);
			avec[id].update_state(st);
		}
	else if (gullibility>1.0+epsilon)
		// Assuming gu is uniformly random.
		for (AgentID id=0; id<avec.size();id++) {
			do {
				p=Point(avec[id].ndraw(0,xsize-1),avec[id].ndraw(0,ysize-1));
			} while (excluded.size() && excluded.find(p)!=excluded.end());
			RWState st(p.get_x(), p.get_y(), \
				(op_init_method==2 ? double(id)/nagents+0.5/double(nagents) : avec[id].fdraw()),\
				avec[id].fdraw());
			avec[id].update_state(st);
		}
	else
		// Assuming gu is the same for all agents.
		for (AgentID id=0; id<avec.size();id++) {
			do {
				p=Point(avec[id].ndraw(0,xsize-1),avec[id].ndraw(0,ysize-1));
			} while (excluded.size() && excluded.find(p)!=excluded.end());
			RWState st(p.get_x(), p.get_y(), \
				(op_init_method==2 ? double(id)/nagents+0.5/double(nagents) : avec[id].fdraw()),\
				gullibility);
			avec[id].update_state(st);
		};
};

// Initializing random seed for all agents.
void Util::initialize_agents_seed(AgentVec &avec, unsigned long rseed, \
	long max_rn) {
	long nagents=avec.size();
	double total_rn=(double) nagents*max_rn;

	long delta=nagents/10;
	AgentRNG rn1; // See "Types.h" for the RNG.
	rn1.seed(rseed);
	double cnt=0, max_ran_nums=rn1.period()/5;
	// If ngents*max_rn > 10^7, print the progress of initializing the seeds.
	if (total_rn>1.0e+7) 
		cout << "\tInitializing the random seeds for all "\
			<< "agents..." << endl << "\t   ";
	for (AgentID i=0;i<nagents-1;i++) {
		avec[i].update_rng_seed(rn1);
		if (total_rn>1.0e+7 && i!=0 && i%delta==0) 
			cout << 10*(i/delta) << "%..." << flush; 
		for (long j=0;j<max_rn;j++) {
			rn1.draw();
			cnt+=1.0;
			if (max_ran_nums < cnt) {
				Error::TOO_MANY_RN_NEEDED er;
				throw er;
			};
		};
	};
	avec[nagents-1].update_rng_seed(rn1);
	if (total_rn>1.0e+7) cout << "100%" << endl; 
};

// A function to check the convergence of the opinion of agents.
bool Util::check_convergence(const AgentVec &avec1, const AgentVec &avec2, \
	const Graph1 &ag1, const Graph1 &ag2, int convergence_method) {
	long size=avec1.size(), nc1, nc2;
	vector<AgentIDSet> bef,aft;
	const int meshsize=50;
	double per;
	int per_int;
	switch (convergence_method) {
	   // Check with the opinion values of all agents.
	   case 1 :
		for (long i=0;i<size;i++) {
			double diff=avec1[i].get_state().get_op()-avec2[i].get_state().get_op();
			if (diff>epsilon || diff<-epsilon)
				return false;
		};
		return true;
		break;
	   // Check with both methods given.
	   case 3 :
		for (long i=0;i<size;i++) {
			double diff=avec1[i].get_state().get_op()-avec2[i].get_state().get_op();
			if (diff>epsilon || diff<-epsilon)
				return false;
		};
		if (ag1.find_clusters(bef)==ag2.find_clusters(aft) && bef==aft)
			return true;
	   	break;
	   // Check with the cluster numbers.
	   case 2 :
		nc1=ag1.find_clusters(bef);
		nc2=ag2.find_clusters(aft);
		if (nc1!=1 || nc2!=1) // If not, go to the default action.
			if (ag1.find_clusters(bef)==ag2.find_clusters(aft) && bef==aft)
				return true;
			else
				return false;
		break;
	   // Find if the state reached period-1 or period-0 (used to find 2->1).
	   case 4 :
		per=abs(meshsize*Util::find_av_diff(avec1,2,meshsize));
		per_int=int(per+0.5);
		if (abs(per-per_int)<0.1 && per_int<=1)
			return true;
		else
			return false;
		break;
	   // Find if the state reached period-1 or period-0 (used to find 3->2).
	   case 5 :
		per=abs(meshsize*Util::find_av_diff(avec1,2,meshsize));
		per_int=int(per+0.5);
		if (abs(per-per_int)<0.1 && per_int<=2)
			return true;
		else
			return false;
		break;
	   // Find if the state reached period-1 or period-0 (used to find 4->3).
	   case 6 :
		per=abs(meshsize*Util::find_av_diff(avec1,2,meshsize));
		per_int=int(per+0.5);
		if (abs(per-per_int)<0.1 && per_int<=3)
			return true;
		else
			return false;
		break;
	   // Find if the state reached period-1 or period-0 (used to find 5->4).
	   case 7 :
		per=abs(meshsize*Util::find_av_diff(avec1,2,meshsize));
		per_int=int(per+0.5);
		if (abs(per-per_int)<0.1 && per_int<=4)
			return true;
		else
			return false;
		break;
	   // Find if the state reached period-0 (special case to find ?->0 transitions).
	   case 10 :
		per=abs(meshsize*Util::find_av_diff(avec1,2,meshsize));
		per_int=int(per+0.5);
		if (abs(per-per_int)<0.1 && per_int==0)
			return true;
		else
			return false;
		break;
	   // Check with the opinion values of all agents.
	   default :
		for (long i=0;i<size;i++) {
			double diff=avec1[i].get_state().get_op()-avec2[i].get_state().get_op();
			if (diff>epsilon || diff<-epsilon)
				return false;
		};
		return true;
	};   
	return false;
};

// A function to find the absolutedifference between two opinions when opinions are linear(1) or circular(2).
double Util::find_op_diff(double a, double b, short topology) {
	double diff=a-b;
	if (topology==2) { // when circular.
		if (diff>=0.5) diff=1.0-diff;
		else if (diff<0.0)
			if (diff>-0.5) diff=-diff;
			else diff=1.0+diff;
		return diff;
	};
	// when linear.
	if (diff<0) diff=-diff;
	return diff;
};

// A function to find the difference between two opinions when opinions are linear(1) or circular(2).
double Util::find_op_diff2(double a, double b, short topology) {
	double diff=a-b;
	if (topology==2) { // when circular.
		if (diff>=0.5) diff=diff-1;
		else if (diff<-0.5) diff=1.0+diff;
		return diff;
	};
	return diff;
};

// Finding groups of opinions based on opinions only
long Util::find_opiniongroups(const AgentVec &avec, \
	std::vector<multiset<double> > & opiniongroups, \
	short topology, double op_resolution) {
	long nagents=avec.size();
	double temp=avec[0].get_state().get_op();
	long ngroups=1;
	const long max_groups=1000;
	vector<double> opinions(max_groups);
	opinions[0]=temp;
	opiniongroups[0].insert(temp);
	multiset<double> temp_set;
	for (long i=1;i<nagents;i++) {
		temp=avec[i].get_state().get_op();
		bool ingroup=false;
		for (long j=0;j<ngroups;j++) {
			double diff=find_op_diff(opinions[j],temp,topology);
			if (diff<op_resolution && diff > -op_resolution) {
				opiniongroups[j].insert(temp);
				ingroup=true;
				break;
			};
		};
		if (!ingroup) {
			ngroups++;
			opinions[ngroups-1]=temp;
			temp_set.clear();
			temp_set.insert(temp);
			opiniongroups.push_back(temp_set);
		};
	};
				
	return ngroups;
};

// Finding the spread of opinions based on opinions only (topology=circular).
double Util::find_opinionspread(const AgentVec &avec, int num_bins) {
	long nagents=avec.size();
	vector<int> count(num_bins);
	vector<double> pdf(num_bins);
	double bin_size=(double) 1/num_bins;
	for (int ibin=0;ibin<num_bins;ibin++) count[ibin]=0;
	for (long i=0;i<nagents;i++) {
		count[(int) (num_bins*avec[i].get_state().get_op())]++;
	};
	double sum=0;
	for (int ibin=0;ibin<num_bins;ibin++) {
		pdf[ibin]=(double) count[ibin]/nagents*num_bins;
		sum+=(pdf[ibin]-1)*(pdf[ibin]-1);
//cout << ibin << '\t' << pdf[ibin] << '\t' << sum << endl;
	};
	return sqrt(sum/(num_bins*(num_bins-1))); // To normalize, the standard deviation is divided by the maximum value
};
double Util::find_opinionspread2(const AgentVec &avec) {
	long nagents=avec.size();
	int nhalf=nagents/2;
	int num_bins=nhalf*2;
	vector<int> count(num_bins);
	double bin_size=(double) 1/num_bins;
	for (int ibin=0;ibin<num_bins;ibin++) count[ibin]=0;
	vector<double> phi(nagents), phi2(nagents);
	for (long i=0;i<nagents;i++) {
		phi[i]=avec[i].get_state().get_op();
		count[(int) (num_bins*phi[i])]++;
	};
	int max_i=nhalf,max=0;
	for (int i=0;i<num_bins;i++) {
		if (count[i]>max) {max=count[i];max_i=i;};
	};

	double phi_s=(max_i+0.5)/num_bins;
	for (int i=0;i<nagents;i++) {
		double diff=phi[i]-phi_s;
		if (diff>0.5) phi2[i]=diff-1;
		else if (diff>-0.5) phi2[i]=diff;
		else phi2[i]=diff+1;
//cout << phi2[i] << endl;
	};
	double s1=0, s2=0;
	for (int i=0;i<nagents;i++) {
		s1+=phi2[i];
		s2+=phi2[i]*phi2[i];
	};
	s1/=nagents;
	s2/=nagents;
	return (s2-s1*s1>1.0e-12 ? sqrt((s2-s1*s1)*12) : 0);
};

// Find the average diff of opinions between consecutive locations (location-wise)
//	xory=1: x, xory=2: y direction
double Util::find_av_diff(const AgentVec &final_vec, short topology, long meshsize, short xory) {
	long size,xsize,ysize;
	xsize=Point::get_xsize();
	ysize=Point::get_ysize();
	size=(xory==1 ? xsize : ysize);
	if (size<meshsize) meshsize=size;

	if (size%meshsize) {
		cerr << " # Bad meshsize.\n";
		exit(1);
	};

	int binsize=size/meshsize;

	vector<multiset<double> > opinionset(meshsize);
	multiset<double> vacantset;
	for (long i=0;i<meshsize;i++)
		opinionset[i]=vacantset;
	long nagents=final_vec.size();
	for (int n=0;n<nagents;n++) {
		long tem_x, tem_y;
		tem_x=final_vec[n].get_state().get_pos().get_x();
		tem_y=final_vec[n].get_state().get_pos().get_y();
		double tem_p=final_vec[n].get_state().get_op();
		if (xory==1) {
			//if (tem_y!=0) continue;
			opinionset[tem_x/binsize].insert(tem_p);
		}
		else {
			//if (tem_x!=0) continue;
			opinionset[tem_y/binsize].insert(tem_p);
		};
	};

	vector<double> density(meshsize);
	int not_used_meshsize=0;
	for (int i=0;i<meshsize;i++) {
		long size2=opinionset[i].size();
		if (size2==0) {
			density[i]=-1;
			not_used_meshsize++;
		}
		else if (size2==1) {
			density[i]=*(opinionset[i].begin());
		}
		else {
			//Random4 ran(1234);
			//int count=ran.ndraw(0,size2-1);
			//double av;
			//for (multiset<double>::const_iterator j=opinionset[i].begin();\
			//	j!=opinionset[i].end();j++) {
			//	if (count==0) {
			//		density[i]=*j;
			//		break;
			//	};
			//	count--;
			//};
			double sum=0;
			double std=*(opinionset[i].begin());
			double max=0, min=0;
			// This calculation is meaningful only when (opinion width inside a mesh) < 0.5.
			for (multiset<double>::const_iterator j=opinionset[i].begin();\
				j!=opinionset[i].end();j++) {
				double diff=find_op_diff2(*j,*(opinionset[i].begin()),topology);
				if (diff>max) max=diff;
				if (diff<min) min=diff;
				sum+=diff;
			};
			if (max-min< 0.5) {
				double average=sum/size2+*(opinionset[i].begin());
				if (average>1.0) average-=1.0;
				else if (average<0.0) average+=1.0;
				density[i]=average;
			}
			else {
				density[i]=-1;
				not_used_meshsize++;
			};
		};
	};
	if (not_used_meshsize>meshsize/2) return 100;
	short interval=0;
	multiset<double> diff_set;
	double prev;
	if (density[0]>-0.5) {
		interval=1;
		prev=density[0];
	};
	for (int i=1;i<meshsize;i++) {
		if (density[i]>-0.5) {
			if (interval) diff_set.insert(find_op_diff2(density[i],prev,topology)/interval);
			prev=density[i];
			interval=1;
		}
		else 
			if (interval) interval++;
	};
	double ave=0;
	for (multiset<double>::const_iterator j=diff_set.begin();j!=diff_set.end();j++) 
		ave+=*j;
	if (diff_set.size()>0)
		return (ave/diff_set.size());
	else
		return 0;
};

// Find the maximum min-max width of p at each x or y.
double Util::find_op_width(const AgentVec &final_vec, short topology, short xory) {
	long size,xsize,ysize;
	xsize=Point::get_xsize();
	ysize=Point::get_ysize();
	size=(xory==1 ? xsize : ysize);

	vector<multiset<double> > opinionset(size);
	multiset<double> vacantset;
	for (long i=0;i<size;i++)
		opinionset[i]=vacantset;
	long nagents=final_vec.size();
	for (int n=0;n<nagents;n++) {
		long tem_x, tem_y;
		tem_x=final_vec[n].get_state().get_pos().get_x();
		tem_y=final_vec[n].get_state().get_pos().get_y();
		double tem_p=final_vec[n].get_state().get_op();
		if (xory==1) {
			opinionset[tem_x].insert(tem_p);
		}
		else {
			opinionset[tem_y].insert(tem_p);
		};
	};

	double width;
	double maxwidth=0;
	for (int i=0;i<size;i++) {
		long size2=opinionset[i].size();
		if (size2==0) {
			width=0;
		}
		else if (size2==1) {
			width=0;
		}
		else {
			double plus=0, minus=0;
			for (multiset<double>::const_iterator j=opinionset[i].begin();\
				j!=opinionset[i].end();j++) {
				double diff=find_op_diff2(*j,*(opinionset[i].begin()),topology);
				if (diff>0 && diff>plus) plus=diff;
				if (diff<0 && diff<minus) minus=diff;
			};
			width=plus-minus;
		};
		if (width>maxwidth) maxwidth=width;
	};

	return maxwidth;
};

// Find the average diff of x-location between consecutive opinions
double Util::find_av_diff_p(const AgentVec &final_vec, short topology, long meshsize, double op_thres) {
	long size=meshsize;
	long xsize,ysize;
	xsize=Point::get_xsize();
	ysize=Point::get_ysize();
	vector<multiset<double> > xset(size);
	vector<multiset<double> > xset2(size*10);
	multiset<double> vacantset;
	for (long i=0;i<size;i++) xset[i]=vacantset;
	for (long i=0;i<size*10;i++) xset2[i]=vacantset;
	long nagents=final_vec.size();
	for (int n=0;n<nagents;n++) {
		long tem_x, tem_y;
		tem_x=final_vec[n].get_state().get_pos().get_x();
		double tem_x_double=(double(tem_x)+0.5)/xsize;
		tem_y=final_vec[n].get_state().get_pos().get_y();
		double tem_p=final_vec[n].get_state().get_op();
		long tem_p_int=int(size*tem_p);
		long tem_p_int2=int(size*10*tem_p);
		xset[tem_p_int].insert(tem_x_double);
		xset2[tem_p_int2].insert(tem_x_double);
	};

	double width, maxwidth=0;
	for (int i=0;i<size*10;i++) {
		long size2=xset2[i].size();
		if (size2==0) {
			width=0;
		}
		else if (size2==1) {
			width=0;
		}
		else {
			double plus=0, minus=0;
			for (multiset<double>::const_iterator j=xset2[i].begin();\
				j!=xset2[i].end();j++) {
				double difference=find_op_diff2(*j,*(xset2[i].begin()),topology);
				if (difference>plus) plus=difference;
				if (difference<minus) minus=difference;
			};
			width=plus-minus;
			if (width>maxwidth) maxwidth=width;
		};
	};
	if (maxwidth>op_thres) return -2;


	vector<double> density(size);
	for (int i=0;i<size;i++) {
		long size2=xset[i].size();
		if (size2==0) {
			density[i]=-1;
		}
		else if (size2==1) {
			density[i]=*(xset[i].begin());
		}
		else {
			double sum=0;
			for (multiset<double>::const_iterator j=xset[i].begin();\
				j!=xset[i].end();j++) {
				double difference=find_op_diff2(*j,*(xset[i].begin()),topology);
				sum+=difference;
			};
			double average=sum/size2+*(xset[i].begin());
			if (average>1.0) average-=1.0;
			else if (average<0.0) average+=1.0;
			density[i]=average;
		};
	};

	short interval=0;
	multiset<double> diff_set;
	double prev;
	if (density[0]>-0.5) {
		interval=1;
		prev=density[0];
	};
	for (int i=1;i<size;i++) {
		if (density[i]>-0.5) {
			if (interval) diff_set.insert(find_op_diff2(density[i],prev,topology)/interval);
			prev=density[i];
			interval=1;
		}
		else 
			if (interval) interval++;
	};
	double ave=0;
	for (multiset<double>::const_iterator j=diff_set.begin();j!=diff_set.end();j++) {
		ave+=*j;
	};

	if (diff_set.size()>0)
		return (ave/diff_set.size());
	else
		return 0;
};

void Util::change_g(AgentVec &avec, double gullibility) {
	for (AgentID id=0; id<avec.size();id++) {
		long tem_x, tem_y;
		tem_x=avec[id].get_state().get_pos().get_x();
		tem_y=avec[id].get_state().get_pos().get_y();
		double tem_p=avec[id].get_state().get_op();
		RWState st(tem_x,tem_y,tem_p,gullibility);
		avec[id].update_state(st);
	};
};
