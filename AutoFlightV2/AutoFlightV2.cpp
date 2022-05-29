
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <iostream>
#include <stdexcept>

#include "SimConnect.h"

using namespace std;

static enum DATA_DEFINE_ID {
	DEFINITION1,
};

static enum DATA_REQUEST_ID {
	REQUEST1,
};

static enum DATA_NAMES {
	DATA_VERTICAL_SPEED,
};

#ifndef SimConnectManager_h__
#define SimConnectManager_h__

class SimConnectManager {
private:
	HRESULT hr = NULL;
	HANDLE hSimConnect = NULL;

public:
	SimConnectManager(HANDLE _hSimConnect) : hSimConnect(_hSimConnect) {

	}

	bool connect() {
		return SUCCEEDED(SimConnect_Open(&hSimConnect, "AutoFlightV2", NULL, 0, 0, 0));
	}

	void disconnect() {
		SimConnect_Close(hSimConnect);
	}

	void addToDataDefinition() {
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION1, "Vertical Speed", "Feet per second", SIMCONNECT_DATATYPE_FLOAT32, 0, DATA_VERTICAL_SPEED);
	}

	void requestData() {
		hr = SimConnect_RequestDataOnSimObject(hSimConnect, REQUEST1, DEFINITION1,SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED | SIMCONNECT_DATA_REQUEST_FLAG_TAGGED);
	}
};

void CALLBACK dispatchProc(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext) {
	
	switch (pData->SIMCONNECT_RECV::dwID) {

	case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
	{
		auto* pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;
		auto* a = dynamic_cast<SIMCONNECT_RECV_SIMOBJECT_DATA*>(pData);


	}

	default:
		throw std::runtime_error("Unknow dwID: " + pData->dwID);
		break;
	}
}

#endif // SimConnectManager_h__


#ifndef Application_h__
#define Application_h__

class Application {
private:
	HANDLE hSimConnect = NULL;
	SimConnectManager* simConnectManager = new SimConnectManager(hSimConnect);

public:
	Application() {

	};

	~Application()
	{
		delete simConnectManager;
	}

	void run() {

		// Connect to sim
		if (simConnectManager->connect()) 
			std::cout << "Connected to Microsoft Flight Simulator 2020" << std::endl;
		else
			return;

		// Add data to definition
		simConnectManager->addToDataDefinition();
		
		// Request data
		simConnectManager->requestData();
			

		while (true)
		{
			SimConnect_CallDispatch(hSimConnect, dispatchProc, NULL);
			Sleep(100);
		}
		
		simConnectManager->disconnect();
	};


};
#endif // Application_h__

int main()
{
    auto application = Application();
	application.run();
}
