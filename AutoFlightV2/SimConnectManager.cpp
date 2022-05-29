#include "SimConnectManager.h"
#include "SimConnectDispatcher.h"

SimConnectManager::SimConnectManager(HANDLE* _hSimConnect) : hSimConnect(_hSimConnect) {
	data = &recv_data;
}

bool SimConnectManager::connect() {
	return SUCCEEDED(SimConnect_Open(hSimConnect, "AutoFlightV2", NULL, 0, 0, 0));
}

void SimConnectManager::disconnect() {
	SimConnect_Close(hSimConnect);
}

void SimConnectManager::addToDataDefinition() {
	hr = SimConnect_AddToDataDefinition(*hSimConnect, DEFINITION1, "GENERAL ENG THROTTLE LEVER POSITION:1", "percent");
	hr = SimConnect_AddToDataDefinition(*hSimConnect, DEFINITION1, "GENERAL ENG THROTTLE LEVER POSITION:2", "percent");
}

void SimConnectManager::requestData() {
	hr = SimConnect_RequestDataOnSimObject(*hSimConnect, REQUEST1, DEFINITION1, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD::SIMCONNECT_PERIOD_SIM_FRAME);
}

void SimConnectManager::setData(SIMVARS data) {
	SimConnect_SetDataOnSimObject(*hSimConnect, DEFINITION1, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(data), &data);
}

void SimConnectManager::callDispatcher() {
	SimConnect_CallDispatch(*hSimConnect, simConnectDispatcher, NULL);
}