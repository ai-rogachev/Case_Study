#include "ApiServerApplication.h"

CApiServerApplication::CApiServerApplication() :
	m_pComApp(nullptr)
	, m_comEvents(this)
	, m_dwCookie(0)
{
	// COM
	CoInitialize(NULL);
	SCODE sc = m_pComApp.CoCreateInstance(__uuidof(ComApplication));
	if (FAILED(sc))
	{
		CoUninitialize();

#ifdef _DEBUG
		TRACE(traceOle, 0, _T("Warning: CreateDispatch returning scode = %Ts.\n"),
			AfxGetFullScodeString(sc));
		throw std::exception(AfxGetFullScodeString(sc));
#endif
	}

	LPUNKNOWN pUnkSink = m_comEvents.GetIDispatch(FALSE);
	BOOL bRes = AfxConnectionAdvise(m_pComApp, __uuidof(IComApplicationEvents), pUnkSink, FALSE, &m_dwCookie);
}

CApiServerApplication::~CApiServerApplication()
{
	// COM
	LPUNKNOWN pUnkSink = m_comEvents.GetIDispatch(FALSE);
	BOOL bRes = AfxConnectionUnadvise(m_pComApp, __uuidof(IComApplicationEvents), pUnkSink, FALSE, m_dwCookie);
	ASSERT(bRes);

	CoUninitialize();
}

bool CApiServerApplication::Start()
{
	long result = m_pComApp->StartServer(200003);
	return result == 0;
}

void CApiServerApplication::SetDataBaseConnection(const CString& strConnection)
{
	CComBSTR bstrConnection = strConnection;
	m_pComApp->put_DataBaseStringConnection(bstrConnection);
}

// событие для клиента без ожидания
void CApiServerApplication::CallbackOneWay(CApiStringDictionary* paramsDict)
{
	m_pComApp->CallbackOneWay("CallbackOneWay", paramsDict->Get());
}

// событие для клиента с ожиданием ответа от клиента
void CApiServerApplication::CallbackWithResponse(CApiStringDictionary* paramsDict, CApiStringDictionary* responsDict)
{
	m_pComApp->CallbackWithResponse("CallbackWithResponse", paramsDict->Get(), responsDict->Get());
}

CApiUtility* CApiServerApplication::GetUtility()
{
	CComPtr<IUtility> pComUtility = m_pComApp->GetUtility();
	m_utility.Attach(pComUtility);

	return &m_utility;
}