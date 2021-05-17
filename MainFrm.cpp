// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "Tetris.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
//	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	cs.cx=950;
	cs.cy=745;

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
bool closed = false;

void CMainFrame::OnClose() 
{
	if (!closed && MessageBox(L"Quit£¿", NULL, MB_OKCANCEL) == IDOK)
	{
		closed = true;
		CFrameWnd::OnClose();
	}
}

void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	SetWindowText(L"Tetris-AI");
}

void CMainFrame::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	CRect clientRect, windowRect;
	this->GetClientRect(&clientRect);
	this->GetWindowRect(&windowRect);

	lpMMI->ptMinTrackSize.x = windowRect.Width() - clientRect.Width() + 760 / 2;
	lpMMI->ptMinTrackSize.y = windowRect.Height() - clientRect.Height() + 550 / 2;
	CFrameWnd::OnGetMinMaxInfo(lpMMI);
}
