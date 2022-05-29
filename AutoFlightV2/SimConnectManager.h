
#ifndef SimConnectManager_h__
#define SimConnectManager_h__

#include <windows.h>

#ifndef _SIMCONNECT_API_
	#include <SimConnect.h>
#endif

#include "Simvars.hpp"

class SimConnectManager {
private:
	HRESULT hr = NULL;
	HANDLE* hSimConnect = NULL;

public:
	SimConnectManager(HANDLE* _hSimConnect);
	SIMVARS* data = nullptr;
	
	bool connect();

	void disconnect();

	void addToDataDefinition();

	void requestData();
	
	void setData(SIMVARS data);

	void callDispatcher();
};
#endif // SimConnectManager_h__