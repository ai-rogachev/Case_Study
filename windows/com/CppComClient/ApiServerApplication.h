#pragma once

#import "interface/Api.Server.tlb" no_namespace

#include "ApiServerEvents.h"

/// <summary>
/// Главный класс API ТЕХТРАН.
/// Собирает в себе все необходимые компоненты ТЕХТРАН
/// и обеспечивает связь клиента API и ТЕХТРАН.
/// </summary>
class CApiServerApplication : public IApiServer
{
public:
	CApiServerApplication();
	~CApiServerApplication();

	bool Start();
	void SetDataBaseConnection(const CString& strConnection);

	// Inherited via IApiServer
	virtual void CallbackOneWay(CApiStringDictionary* paramsDict) override;
	virtual void CallbackWithResponse(CApiStringDictionary* paramsDict,
		CApiStringDictionary* responsDict) override;
	virtual CApiUtility* GetUtility() override;

	virtual ITehtranController* GetTehtranController() override;

private:
	void InitTehtran();

private:
	CComPtr<IComApplication> m_pComApp;

	CApiServerEvents m_comEvents;
	DWORD m_dwCookie;
};