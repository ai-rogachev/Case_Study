
// MFCApp_TEST_COMView.cpp : implementation of the CMFCAppTESTCOMView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCApp_TEST_COM.h"
#endif

#include "MFCApp_TEST_COMDoc.h"
#include "MFCApp_TEST_COMView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCAppTESTCOMView

IMPLEMENT_DYNCREATE(CMFCAppTESTCOMView, CView)

BEGIN_MESSAGE_MAP(CMFCAppTESTCOMView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCAppTESTCOMView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMFCAppTESTCOMView construction/destruction

CMFCAppTESTCOMView::CMFCAppTESTCOMView() noexcept
{
	// TODO: add construction code here

}

CMFCAppTESTCOMView::~CMFCAppTESTCOMView()
{
}

BOOL CMFCAppTESTCOMView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCAppTESTCOMView drawing

void CMFCAppTESTCOMView::OnDraw(CDC* /*pDC*/)
{
	CMFCAppTESTCOMDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CMFCAppTESTCOMView printing


void CMFCAppTESTCOMView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCAppTESTCOMView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCAppTESTCOMView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCAppTESTCOMView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CMFCAppTESTCOMView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCAppTESTCOMView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCAppTESTCOMView diagnostics

#ifdef _DEBUG
void CMFCAppTESTCOMView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCAppTESTCOMView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCAppTESTCOMDoc* CMFCAppTESTCOMView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCAppTESTCOMDoc)));
	return (CMFCAppTESTCOMDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCAppTESTCOMView message handlers


BOOL CMFCAppTESTCOMView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class

	return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


int CMFCAppTESTCOMView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
		
	return 0;
}
