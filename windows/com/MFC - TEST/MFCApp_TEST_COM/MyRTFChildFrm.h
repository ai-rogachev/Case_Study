#pragma once

#include <atlwin.h>
#include <afxmdichildwndex.h>

class MyRTFChildFrm : public CMDIChildWndEx
{
public:
	MyRTFChildFrm();
	~MyRTFChildFrm();

private:
	CAxWindow2 m_ax;

private:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};

