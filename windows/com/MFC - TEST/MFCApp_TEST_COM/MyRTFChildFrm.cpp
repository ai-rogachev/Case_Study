#include "pch.h"
#include "MyRTFChildFrm.h"


//#import "Interface\MyOfficeX.tlb"


// ATLMod.h : Declaration of copy of DllMain.h
class CAtlModuleSingleton : public ATL::CAtlModule
{
	HRESULT ATL::CAtlModule::AddCommonRGSReplacements(IRegistrarBase*) throw()
	{
		return S_OK;
	};
public:
} _AtlModule;

MyRTFChildFrm::MyRTFChildFrm()
{
}

MyRTFChildFrm::~MyRTFChildFrm()
{
}


BOOL MyRTFChildFrm::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	//RECT rect; GetClientRect(&rect);
	//LPCTSTR pszClassGUID = W2T(static_cast<BSTR>(CComBSTR(__uuidof(MyOfficeX::MyOfficeX))));

	//HWND hwndContainer = m_ax.Create(m_hWnd, rect, pszClassGUID, WS_CHILD | WS_VISIBLE);
	//ASSERT(hwndContainer);

	return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
}
