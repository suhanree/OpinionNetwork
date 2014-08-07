// 
// 	Filename : RWerrors.h
//
//	Author : Suhan Ree
//	Date   : 08-25-2003

#ifndef RWERRORS_H
#define RWERRORS_H

#include <string>
// errors for the RW project.

namespace Error {

struct Occupancy_State {}; // State doesn't exist for the given occupancy array.
struct NeighborTypeError {
	NeighborTypeError(std::string in=""): message(in) {};
	std::string message;
};

}; // End of namespace RWErrors.

#endif
