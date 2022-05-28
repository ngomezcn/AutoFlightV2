
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <iostream>

#include "SimConnect.h"


#ifndef SimConnectManager_h__
#define SimConnectManager_h__

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
