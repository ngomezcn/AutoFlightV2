#include "SimConnectManager.h"
#include "SimUnits.h"
#include "SimDataDefine.h"

#include "SimConnectDispatcher.cpp"

SimConnectManager::SimConnectManager(HANDLE* _hSimConnect) : hSimConnect(_hSimConnect) {
	simData = &_simData;
}

bool SimConnectManager::connect() {
	return SUCCEEDED(SimConnect_Open(hSimConnect, "AutoFlightV2", NULL, 0, 0, 0));
}

void SimConnectManager::disconnect() {
	SimConnect_Close(hSimConnect);
}

void SimConnectManager::addToDataDefinition() {
	hr = SimConnect_AddToDataDefinition(*hSimConnect, DEFINITION1, "GENERAL ENG THROTTLE LEVER POSITION:1", SimUnits::percent);
	hr = SimConnect_AddToDataDefinition(*hSimConnect, DEFINITION1, "GENERAL ENG THROTTLE LEVER POSITION:2", SimUnits::percent);
	hr = SimConnect_AddToDataDefinition(*hSimConnect, DEFINITION1, "AILERON POSITION", SimUnits::position);
}

void SimConnectManager::requestDataOn() {

	hr = SimConnect_RequestDataOnSimObject(
		*hSimConnect, 
		REQUEST1, 
		DEFINITION1,
		SIMCONNECT_OBJECT_ID_USER,
		SIMCONNECT_PERIOD::SIMCONNECT_PERIOD_SIM_FRAME
	);
	
	hr = SimConnect_RequestFacilitiesList(
		*hSimConnect,
		SIMCONNECT_FACILITY_LIST_TYPE::SIMCONNECT_FACILITY_LIST_TYPE_VOR,
		REQUEST2
	);
}

void SimConnectManager::subscribeTo() {
	
	hr = SimConnect_SubscribeToFacilities(
		*hSimConnect,
		SIMCONNECT_FACILITY_LIST_TYPE::SIMCONNECT_FACILITY_LIST_TYPE_VOR,
		REQUEST2
	);
}

void SimConnectManager::unubscribeTo() {

	hr = SimConnect_UnsubscribeToFacilities(
		*hSimConnect,
		SIMCONNECT_FACILITY_LIST_TYPE::SIMCONNECT_FACILITY_LIST_TYPE_VOR
	);
}


void SimConnectManager::pushData() {
	SimConnect_SetDataOnSimObject(
		*hSimConnect,
		DEFINITION1,
		SIMCONNECT_OBJECT_ID_USER,
		0,
		0,
		sizeof(this->simData->simVars),
		&this->simData->simVars);
}

void SimConnectManager::callDispatcher() {

	SimConnect_CallDispatch(*hSimConnect, simConnectDispatcher, nullptr);
	
}
