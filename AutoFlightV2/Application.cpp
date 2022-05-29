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
	simConnectManager.requestDataOn();


	while (true)
	{
		simConnectManager.callDispatcher();

		simConnectManager.setData(*simConnectManager.data);
		Sleep(100);
	}

	simConnectManager.disconnect();
};

class Aircraft {

};

int main()
{
	auto application = Application();
	application.run();
}

