
// MFCApp_TEST_COM.h : main header file for the MFCApp_TEST_COM application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCAppTESTCOMApp:
// See MFCApp_TEST_COM.cpp for the implementation of this class
//

class CMFCAppTESTCOMApp : public CWinAppEx
{
public:
	CMFCAppTESTCOMApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCAppTESTCOMApp theApp;
