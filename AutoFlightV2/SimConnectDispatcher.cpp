#pragma once

#ifndef SimConnectDispatcher_h__
#define SimConnectDispatcher_h__

#include <SimConnect.h>
#include "SimDataRequest.h"
#include <iostream>
#include <vector>
#include "SimData.h"

SimData _simData;

void CALLBACK simConnectDispatcher(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext) {
	
	switch (pData->dwID) {

	case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
	{
		auto* pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;

		switch (pObjData->dwRequestID)
		{
		case REQUEST1:
		{
			_simData.simVars = *(SimVariables*)&pObjData->dwData;
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
			for (size_t i = 0; i < pObjData->dwArraySize; i++)
			{
				auto a = *(SIMCONNECT_DATA_FACILITY_VOR*)&pObjData->rgData[i];
				_simData.vorList.push_back(a);
			}
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
