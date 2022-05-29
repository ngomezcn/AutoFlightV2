#pragma once

#ifndef SimConnectDispatcher_h__
#define SimConnectDispatcher_h__

#ifndef _SIMCONNECT_API_
	#include <SimConnect.h>
#endif

SIMVARS recv_data;
void CALLBACK simConnectDispatcher(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext) {

	switch (pData->dwID) {

	case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
	{
		auto* pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;

		switch (pObjData->dwRequestID)
		{
		case REQUEST1:
		{
			recv_data = *(SIMVARS*)&pObjData->dwData;
		}
		default:
			break;
		}
	}

	default:
		break;
	}
}
#endif // SimConnectDispatcher_h__