
#ifndef SimConnectManager_h__
#define SimConnectManager_h__

#include <windows.h>

#ifndef _SIMCONNECT_API_
	#include <SimConnect.h>
#endif

#include "SimVariables.h"
#include "SimData.h"

class SimConnectManager {
private:
	HRESULT hr = NULL;
	HANDLE* hSimConnect = NULL;
	
public:
	SimData *simData;

	SimConnectManager(HANDLE* _hSimConnect);
	
	bool connect();

	void disconnect();

	void addToDataDefinition();

	void requestDataOn();
	
	void subscribeTo();

	void unubscribeTo();
	
	void pushData();

	void callDispatcher();
	
	void dispatcher();
};
#endif // SimConnectManager_h__