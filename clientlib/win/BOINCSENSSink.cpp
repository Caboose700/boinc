// Berkeley Open Infrastructure for Network Computing
// http://boinc.berkeley.edu
// Copyright (C) 2005 University of California
//
// This is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation;
// either version 2.1 of the License, or (at your option) any later version.
//
// This software is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU Lesser General Public License for more details.
//
// To view the GNU Lesser General Public License visit
// http://www.gnu.org/copyleft/lesser.html
// or write to the Free Software Foundation, Inc.,
// 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


#include "stdafx.h"
#include "BOINCSENSSink.h"
#include "SENSSubscriptions.h"


// CBOINCSENSSink

CBOINCSENSSink::CBOINCSENSSink()
{
}

HRESULT CBOINCSENSSink::FinalConstruct()
{
    return S_OK;
}

void CBOINCSENSSink::FinalRelease() 
{
}


// ISensNetwork Methods
HRESULT CBOINCSENSSink::ConnectionMade(BSTR bstrConnection, unsigned long ulType, SENS_QOCINFO * lpQOCInfo)
{
    USES_CONVERSION;
    std::vector<PNETWORK_CONNECTION>::iterator iter;
    BOOL bCachedConnectionFound = FALSE;

    // Check cached connection state
    for (iter = gpNetworkConnections.begin(); iter != gpNetworkConnections.end(); iter++) {
        if ((*iter)->bstrConnection == bstrConnection) {
            ATLTRACE(TEXT("ConnectionMade: Updating existing record.\n"));
            // Either we missed a disconnect notification or the
            //   ConnectionMadeNoQOCInfo event was fired first.
            bCachedConnectionFound = TRUE;
            (*iter)->ulType = ulType;
            (*iter)->QOCInfo = *lpQOCInfo;
        }
    }

    if (!bCachedConnectionFound) {
        PNETWORK_CONNECTION pNetworkConnection = new NETWORK_CONNECTION;
        pNetworkConnection->bstrConnection = bstrConnection;
        pNetworkConnection->ulType = ulType;
        pNetworkConnection->QOCInfo = *lpQOCInfo;
        gpNetworkConnections.push_back(pNetworkConnection);
    }

    return S_OK;
}

HRESULT CBOINCSENSSink::ConnectionMadeNoQOCInfo(BSTR bstrConnection, unsigned long ulType)
{
    USES_CONVERSION;
    std::vector<PNETWORK_CONNECTION>::iterator iter;
    BOOL bCachedConnectionFound = FALSE;

    // Check cached connection state
    for (iter = gpNetworkConnections.begin(); iter != gpNetworkConnections.end(); iter++) {
        if ((*iter)->bstrConnection == bstrConnection) {
            ATLTRACE(TEXT("ConnectionMadeNoQOCInfo: Updating existing record.\n"));
            // Either we missed a disconnect notification or the
            //   ConnectionMade event was fired first.
            bCachedConnectionFound = TRUE;
            (*iter)->ulType = ulType;
        }
    }

    if (!bCachedConnectionFound) {
        ATLTRACE(TEXT("ConnectionMadeNoQOCInfo: Creating new record.\n"));
        PNETWORK_CONNECTION pNetworkConnection = new NETWORK_CONNECTION;
        pNetworkConnection->bstrConnection = bstrConnection;
        pNetworkConnection->ulType = ulType;
        gpNetworkConnections.push_back(pNetworkConnection);
    }

    return S_OK;
}

HRESULT CBOINCSENSSink::ConnectionLost(BSTR bstrConnection, unsigned long ulType)
{
    USES_CONVERSION;
    std::vector<PNETWORK_CONNECTION>::iterator iter;
    for (iter = gpNetworkConnections.begin(); iter != gpNetworkConnections.end(); iter++) {
        if ((*iter)->bstrConnection == bstrConnection) {
            gpNetworkConnections.erase(iter);
            delete *iter;
        }
    }
    return S_OK;
}

HRESULT CBOINCSENSSink::DestinationReachable(BSTR bstrDestination, BSTR bstrConnection, unsigned long ulType, SENS_QOCINFO * lpQOCInfo)
{
    return S_OK;
}

HRESULT CBOINCSENSSink::DestinationReachableNoQOCInfo(BSTR bstrDestination, BSTR bstrConnection, unsigned long ulType)
{
    return S_OK;
}

// ISensOnNow Methods
HRESULT CBOINCSENSSink::OnACPower()
{
    return S_OK;
}

HRESULT CBOINCSENSSink::OnBatteryPower(unsigned long dwBatteryLifePercent)
{
    return S_OK;
}

HRESULT CBOINCSENSSink::BatteryLow(unsigned long dwBatteryLifePercent)
{
    return S_OK;
}

// ISensLogon Methods
HRESULT CBOINCSENSSink::Logon(BSTR bstrUserName)
{
    return S_OK;
}

HRESULT CBOINCSENSSink::Logoff(BSTR bstrUserName)
{
    return S_OK;
}

HRESULT CBOINCSENSSink::StartShell(BSTR bstrUserName)
{
    return S_OK;
}

HRESULT CBOINCSENSSink::DisplayLock(BSTR bstrUserName)
{
    return S_OK;
}

HRESULT CBOINCSENSSink::DisplayUnlock(BSTR bstrUserName)
{
    return S_OK;
}

HRESULT CBOINCSENSSink::StartScreenSaver(BSTR bstrUserName)
{
    return S_OK;
}

HRESULT CBOINCSENSSink::StopScreenSaver(BSTR bstrUserName)
{
    return S_OK;
}

