#include "ApiServerEvents.h"

// CApiServerEvents
IMPLEMENT_DYNCREATE(CApiServerEvents, CCmdTarget)

CApiServerEvents::CApiServerEvents()
{
}

CApiServerEvents::CApiServerEvents(IApiServer* server) :
	m_pApiServer(server)
{
	EnableAutomation();
}

CApiServerEvents::~CApiServerEvents()
{
}

void CApiServerEvents::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.
	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CApiServerEvents, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CApiServerEvents, CCmdTarget)
	DISP_FUNCTION_ID(CApiServerEvents, "TestMultiplyEvent", 0x60000001, OnTestMultiplyEvent, VT_EMPTY, VTS_WBSTR VTS_WBSTR VTS_PBSTR)
	DISP_FUNCTION_ID(CApiServerEvents, "ExecuteEvent", 0x60000003, OnExecuteEvent, VT_EMPTY, VTS_WBSTR VTS_DISPATCH VTS_PDISPATCH)
END_DISPATCH_MAP()

BEGIN_INTERFACE_MAP(CApiServerEvents, CCmdTarget)
	INTERFACE_PART(CApiServerEvents, __uuidof(IComApplicationEvents), Dispatch)
END_INTERFACE_MAP()

/// <summary>
/// Тестовое событие "Умножить 2 числа".
/// </summary>
/// <param name="str1">Множитель 1.</param>
/// <param name="str2">Мнодитель 2.</param>
/// <param name="str3">Произведение (результат).</param>
void CApiServerEvents::OnTestMultiplyEvent(BSTR str1, BSTR str2, BSTR* str3)
{
	int s1 = StrToIntW(str1);
	int s2 = StrToIntW(str2);
	int s3 = s1 * s2;
	wchar_t temp_str[11]; // we assume that the maximal string length can be 10
	_itow(s3, temp_str, 10);
	*str3 = SysAllocString(temp_str);
}

/// <summary>
/// Событие "Выполнить API запрос".
/// Клиента API выполнил запрос к ТЕХТРАН.
/// </summary>
/// <param name="queryName">Имя запроса.</param>
/// <param name="paramsDict">Параметры входящего запроса.</param>
/// <param name="resultDict">Параметы ответа на запрос.</param>
void CApiServerEvents::OnExecuteEvent(BSTR queryName, IStringDictionary* paramsDict, IStringDictionary** resultDict)
{
#ifdef FEATURE_API
	CString strQueryName(queryName);

	// выполнение запросов пользователя API
	CApiCommandFactory cmdFactory;
	auto apiCmd = cmdFactory.CreateCommand( strQueryName, CApiStringDictionary(paramsDict) );

	// обработка ошибки создания команды
	if (apiCmd == nullptr)
		return;

	// необходимо для выполнения обратного запроса у клиента,
	// в ходе выполнения текущего запроса.
	apiCmd->SetApiServer(m_pApiServer);
	apiCmd->SetQueryName(queryName);

	auto outputDict = std::unique_ptr<CApiStringDictionary>(new CApiStringDictionary(*resultDict));
	apiCmd->Execute( std::move(outputDict) );

#endif // FEATURE_API
}