#pragma once


#ifndef Application_h__
#define Application_h__

#include "SimConnectManager.h"
#include <iostream>

class Application {
private:
	HANDLE hSimConnect = NULL;
	SimConnectManager simConnectManager = SimConnectManager(&hSimConnect);

public:
	Application();


	void run();

};
#endif // Application_h__