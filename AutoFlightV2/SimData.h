#pragma once

#include "SimVariables.h"
#include <vector>

struct SimData
{
	SIM_VARIABLES simVars;
	std::vector<SIMCONNECT_DATA_FACILITY_VOR> vorList;
	std::vector<SIMCONNECT_DATA_FACILITY_AIRPORT> airportList;
};
