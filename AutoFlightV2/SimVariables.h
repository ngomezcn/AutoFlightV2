#pragma once

#ifndef Simvars_h__
#define Simvars_h__
#include <map>
#include <Windows.h>
#include <SimConnect.h>

// TODO: Categorize by engine, flight model, electrics, control, autopilot, landing/brake, fuel and misc | See: https://docs.flightsimulator.com/html/Programming_Tools/SimVars/Simulation_Variables.htm

struct SIM_VARIABLES {
	double THROTTLE1;
	double THROTTLE2;
	double AILERON_POSITION;
};
#endif // Simvars_h__

