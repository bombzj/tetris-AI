// Tetris.h : main header file for the Tetris application
//

#if !defined(AFX_TETRIS_H__A07C0E4C_65E0_48D4_803A_5B3145822C39__INCLUDED_)
#define AFX_TETRIS_H__A07C0E4C_65E0_48D4_803A_5B3145822C39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include "D3DX9.h"
//#include <DXErr8.h>
//#include <tchar.h>
#include "DXUT.h"
#include "D3DUtil.h"

/////////////////////////////////////////////////////////////////////////////
// CTetrisApp:
// See Tetris.cpp for the implementation of this class
//

class CTetrisApp : public CWinApp
{
public:
	CTetrisApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTetrisApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTetrisApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TETRIS_H__A07C0E4C_65E0_48D4_803A_5B3145822C39__INCLUDED_)
