#pragma once


#ifndef SimData_h__
#define SimData_h__

#include "SimVariables.h"
#include <vector>

struct SimData
{
	SimVariables simVars;
	std::vector<SIMCONNECT_DATA_FACILITY_VOR> vorList;
	std::vector<SIMCONNECT_DATA_FACILITY_AIRPORT> airportList;
};
#endif // SimData_h__
