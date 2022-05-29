#include "Application.h"


Application::Application() {
	
};


void Application::run() {

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
		std::cout << simConnectManager.data->THROTTLE1 << std::endl;


		simConnectManager.setData(*simConnectManager.data);
		Sleep(1000);
	}

	simConnectManager.disconnect();
};