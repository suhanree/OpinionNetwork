// 
// 	Filename : Types.h
//
//	Author : Suhan Ree
//	Date   : 07-09-2004

#ifndef TYPES_H
#define TYPES_H

#include <set>
#include <map>
#include "Random1.h"
#include "Random2.h"
#include "Random3.h"
#include "Random4.h"
#include "Point.h"

// typedef's for the AWDSIM project.

typedef long AgentID;		// ID for an agent is represented by long.
typedef AgentID Node;		// AgentID is also used as a node for graphs
typedef double EdgeStrength;	// strength of the edge is represented
				// by float.
typedef Random4L AgentRNGLimit;	// Random number generator used by RAgent.
typedef Random4 AgentRNG;	// Random number generator used by RAgent.

//typedef Point2DInt Point;	// Point class used.
//typedef Point2DIntLessThan PointLessThan;
typedef Point2DIntTorus Point;	// Point class used.
typedef Point2DIntTorusLessThan PointLessThan;

typedef double OpType;		// Type of the opinion. eg, double, int.

// Set of Agent ID's
typedef std::set<AgentID> AgentIDSet;
// Map of Agent ID and double
typedef std::map<AgentID,double> AgentIDMap;

// Set of Point2DIntTorus's.
typedef std::set<Point,PointLessThan> PointSet; 
typedef std::vector<Point> PointVec; 
// Map from Point2DIntTorus to double.
typedef std::map<Point,double,PointLessThan> PointMap; 


#endif
