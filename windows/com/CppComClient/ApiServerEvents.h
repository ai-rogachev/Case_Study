#pragma once

/// <summary>
/// Класс обрабатывает события поступающие от клиента API.
/// Главное событие OnExecuteEvent.
/// </summary>
class CApiServerEvents : public CCmdTarget
{
	DECLARE_DYNCREATE(CApiServerEvents)

public:
	CApiServerEvents();
	CApiServerEvents(IApiServer* server);
	virtual ~CApiServerEvents();

	virtual void OnFinalRelease();

private:
	IApiServer* m_pApiServer;

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnTestMultiplyEvent(BSTR str1, BSTR str2, BSTR* str3);
	afx_msg void OnExecuteEvent(BSTR queryName, IStringDictionary* paramsDict, IStringDictionary** resultDict);

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};