
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

struct DATA {
	double THROTTLE1;
};


#ifndef SimConnectManager_h__
#define SimConnectManager_h__

class SimConnectManager {
private:
	HRESULT hr = NULL;
	HANDLE* hSimConnect = NULL;

public:
	SimConnectManager(HANDLE* _hSimConnect) : hSimConnect(_hSimConnect) {

	}

	bool connect() {
		return SUCCEEDED(SimConnect_Open(hSimConnect, "AutoFlightV2", NULL, 0, 0, 0));
	}

	void disconnect() {
		SimConnect_Close(hSimConnect);
	}

	void addToDataDefinition() {
		hr = SimConnect_AddToDataDefinition(*hSimConnect, DEFINITION1, "GENERAL ENG THROTTLE LEVER POSITION:1", "percent");
	}

	void requestData() {
		hr = SimConnect_RequestDataOnSimObject(*hSimConnect, REQUEST1, DEFINITION1, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD::SIMCONNECT_PERIOD_SIM_FRAME);
	}

	void setData(DATA data) {
		SimConnect_SetDataOnSimObject(*hSimConnect, DEFINITION1, SIMCONNECT_OBJECT_ID_USER, 0, 0, sizeof(data), &data);
	}
};

DATA myData;
void CALLBACK dispatchProc(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext) {
	
	switch (pData->dwID) {

	case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
	{
		auto* pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;

		switch (pObjData->dwRequestID)
		{
		case REQUEST1:
		{
			auto* pS = (DATA*)&pObjData->dwData;

			myData.THROTTLE1 = pS->THROTTLE1;
		}
		default:
			break;
		}
	}

	default:
		break;
	}
}

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
			cout << myData.THROTTLE1 << endl;
			myData.THROTTLE1 = 99.99f;
			simConnectManager->setData(myData);
			Sleep(1000);
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
