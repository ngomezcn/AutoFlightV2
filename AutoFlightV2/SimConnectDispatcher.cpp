#pragma once

#ifndef SimConnectDispatcher_h__
#define SimConnectDispatcher_h__

#ifndef _SIMCONNECT_API_
	#include <SimConnect.h>
#endif

#include "DataRequest.h"
#include <iostream>

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
	case SIMCONNECT_RECV_ID_VOR_LIST:
	{

		auto* pObjData = (SIMCONNECT_RECV_VOR_LIST*)pData;

		switch (pObjData->dwRequestID)
		{
		case REQUEST2:
		{
			//recv_data = *(SIMVARS*)&pObjData->dwData;
			std::cout << "recved vor list" << std::endl;

		}
		default:
			break;
		}

		
		break;
	}
	default:
		break;
	}
}
#endif // SimConnectDispatcher_h__