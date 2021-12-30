
// MFCApp_TEST_COMView.h : interface of the CMFCAppTESTCOMView class
//

#pragma once
#include "MFCApp_TEST_COMDoc.h"

class CMFCAppTESTCOMView : public CView
{
protected: // create from serialization only
	CMFCAppTESTCOMView() noexcept;
	DECLARE_DYNCREATE(CMFCAppTESTCOMView)

// Attributes
public:
	CMFCAppTESTCOMDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCAppTESTCOMView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // debug version in MFCApp_TEST_COMView.cpp
inline CMFCAppTESTCOMDoc* CMFCAppTESTCOMView::GetDocument() const
   { return reinterpret_cast<CMFCAppTESTCOMDoc*>(m_pDocument); }
#endif

