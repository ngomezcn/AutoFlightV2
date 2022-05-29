
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <iostream>
#include <stdexcept>

#include <SimConnect.h>

using namespace std;

#include "SimConnectManager.h"

#ifndef Application_h__
#define Application_h__

class Application {
private:
	HANDLE hSimConnect = NULL;
	SimConnectManager simConnectManager = SimConnectManager(&hSimConnect);

public:
	Application() {

	};

	~Application()
	{
	}

	void run() {

		// Connect to fs2020
		if (simConnectManager.connect()) 
			std::cout << "Connected to Microsoft Flight Simulator 2020" << std::endl;
		else
			return;

		simConnectManager.addToDataDefinition();
		simConnectManager.requestData();
			
		
		while (true)
		{
			simConnectManager.callDispatcher();
			cout << simConnectManager.data->THROTTLE1 << endl;

			
			simConnectManager.setData(*simConnectManager.data);
			Sleep(1000);
		}
		
		simConnectManager.disconnect();
	};


};
#endif // Application_h__


int main()
{
    auto application = Application();
	application.run();
}
