
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <iostream>

#include "SimConnect.h"





#ifndef SimConnectManager_h__
#define SimConnectManager_h__

static enum DATA_DEFINE_ID { // Used in SimConnect_AddToDataDefinition(...)
	DEFINITION1,
};

static enum DATA_REQUEST_ID {
	REQUEST1,
};

static enum DATA_NAMES { 
	DATA_VERTICAL_SPEED,
};

class SimConnectManager {
private:
	HRESULT hr = NULL;
	HANDLE* phSimConnect = NULL;

public:
	SimConnectManager(HANDLE* _phSimConnect) : phSimConnect(_phSimConnect) {

	}

	bool connect() {

		return SUCCEEDED(SimConnect_Open(phSimConnect, "AutoFlightV2", NULL, 0, 0, 0));
	}

	void disconnect() {
		SimConnect_Close(phSimConnect);
	}

	void addToDataDefinition() {
		hr = SimConnect_AddToDataDefinition(phSimConnect, DEFINITION1, "Vertical Speed", "Feet per second", SIMCONNECT_DATATYPE_FLOAT32, 0, DATA_VERTICAL_SPEED);
	}

	void requestData() {
		hr = SimConnect_RequestDataOnSimObject(phSimConnect, REQUEST1, DEFINITION1,SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND, SIMCONNECT_DATA_REQUEST_FLAG_CHANGED | SIMCONNECT_DATA_REQUEST_FLAG_TAGGED);
	}
};
#endif // SimConnectManager_h__


#ifndef Application_h__
#define Application_h__

class Application {
private:
	HANDLE hSimConnect = NULL;
	SimConnectManager* simConnectManager = new SimConnectManager(&hSimConnect);

public:
	Application() {

	};

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
			
		// ....

		// Loop

	};
};
#endif // Application_h__

int main()
{
    auto application = Application();
	application.run();
}
