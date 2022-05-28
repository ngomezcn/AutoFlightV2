
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <strsafe.h>
#include <iostream>

#include "SimConnect.h"

#define _APP_NAME_ "AutoFlightV2"

class SimConnect {
private:
	HRESULT hr = NULL;
	HANDLE* phSimConnect = NULL;
		
public:	
	SimConnect(HANDLE* phSimConnect);

	bool connect();
};

SimConnect::SimConnect(HANDLE* _phSimConnect) : phSimConnect(_phSimConnect) {
	
}
	
bool SimConnect::connect() {

	return SUCCEEDED(SimConnect_Open(phSimConnect, _APP_NAME_, NULL, 0, 0, 0));
}

class Application {
private:
	HANDLE hSimConnect = NULL;
	SimConnect* simConnect = new SimConnect(&hSimConnect);
	
public:
	Application();

	void run();
};

Application::Application() {

};

void Application::run() {

	if (simConnect->connect()) 
		std::cout << "Connected to Microsoft Flight Simulator 2020" << std::endl;
	else
		return;
	
};

int main()
{
    auto application = Application();
	application.run();
}
