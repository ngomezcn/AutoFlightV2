
#ifndef SimConnectManager_h__
#define SimConnectManager_h__

#include <windows.h>

#ifndef _SIMCONNECT_API_
	#include <SimConnect.h>
#endif

#include "SimVariables.h"

class SimConnectManager {
private:
	HRESULT hr = NULL;
	HANDLE* hSimConnect = NULL;

public:
	SimConnectManager(HANDLE* _hSimConnect);
	SIM_VARIABLES* data = nullptr;
	
	bool connect();

	void disconnect();

	void addToDataDefinition();

	void requestDataOn();
	
	void subscribeTo();

	void unubscribeTo();
	
	void setData(SIM_VARIABLES data);

	void callDispatcher();
};
#endif // SimConnectManager_h__