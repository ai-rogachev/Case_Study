
// ChildFrm.cpp : implementation of the CChildFrame class
//

#include "pch.h"
#include "framework.h"
#include "MFCApp_TEST_COM.h"

#include "ChildFrm.h"
#include "MFCApp_TEST_COMView.h"
#include <fstream>
#include <sstream>

#import "Interface\MyOfficeX.tlb"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CChildFrame construction/destruction

CChildFrame::CChildFrame() noexcept
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME;

	return TRUE;
}

// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}
#endif //_DEBUG

// CChildFrame message handlers

//void AdjustFloatingPointMode()
//{
//	static unsigned int bits, mask;
//
//	static bool guard = false;
//	if (!guard)
//	{
//#ifdef _DEBUG
//		bits = _PC_64;
//		mask = _MCW_PC | _EM_INVALID | _EM_ZERODIVIDE | _EM_OVERFLOW;
//#else
//		bits = _PC_64;
//		mask = _MCW_PC;
//#endif
//
//		auto app = AfxGetApp();
//		const TCHAR section[] = _T("Debug\\controlfp");
//		bits = app->GetProfileInt(section, _T("bits"), bits);
//		mask = app->GetProfileInt(section, _T("mask"), mask);
//		guard = true;
//	}
//
//	_clearfp(); // сбросить маскированные ошибки
//	_controlfp(bits, mask);
//}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	//AdjustFloatingPointMode();

	USES_CONVERSION;

	RECT rect; GetClientRect(&rect);
	LPCTSTR pszClassGUID = W2T(static_cast<BSTR>(CComBSTR(__uuidof(MyOfficeX::MyOfficeX))));

	HWND hwndContainer = m_ax.Create(m_hWnd, rect, pszClassGUID, WS_CHILD | WS_VISIBLE, 0, AFX_IDW_PANE_FIRST);
	ASSERT(hwndContainer);

	std::ifstream t;
	t.open("test_data.rtf");
	if (t)
	{
		std::stringstream buffer;
		buffer << t.rdbuf();

		std::string rtf;
		rtf = buffer.str();

		CComPtr<MyOfficeX::IMyOfficeX> spOffice;
		HRESULT rs = m_ax.QueryControl(&spOffice);
		if (SUCCEEDED(rs))
		{
			spOffice->LoadRTF(rtf.c_str());
		}
	}
	return CMDIChildWndEx::OnCreateClient(lpcs, pContext);
}


void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWndEx::OnSize(nType, cx, cy);

	if (m_ax) 
	{
		RECT rect = { 0, 0, cx, cy };
		m_ax.MoveWindow(&rect);
	}
}
