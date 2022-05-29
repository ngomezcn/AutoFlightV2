#include "Application.h"

Application::Application() {
	
};

void Application::run() {

	// Connect to fs2020
	if (simConnectManager.connect())
		std::cout << "Connected to Microsoft Flight Simulator 2020" << std::endl;
	else
		return;

	// Attach/Init config to SimConnect
	simConnectManager.addToDataDefinition();
	simConnectManager.requestDataOn();
	simConnectManager.subscribeTo();
	simConnectManager.unubscribeTo();

	while (true)
	{
		simConnectManager.callDispatcher();

		std::cout << "X: " << simConnectManager.simData->simVars.AILERON_POSITION << std::endl;

		simConnectManager.pushData();
		Sleep(100);
	}

	simConnectManager.disconnect();
};

int main()
{
	auto application = Application();
	application.run();
}

