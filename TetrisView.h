// TetrisView.h : interface of the CTetrisView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TETRISVIEW_H__D4CED32F_0003_4CBA_9337_8388ADE9820A__INCLUDED_)
#define AFX_TETRISVIEW_H__D4CED32F_0003_4CBA_9337_8388ADE9820A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "OptionDialog.h"
#include "ControlsetDialog.h"
#include "Tetris_Game.h"

class CTetrisView : public CFormView
{
protected: // create from serialization only
	CTetrisView();
	DECLARE_DYNCREATE(CTetrisView)

public:
	//{{AFX_DATA(CTetrisView)
	enum{ IDD = IDD_TETRIS_FORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Attributes
public:
	CTetrisDoc* GetDocument();
	COptionDialog optiondlg;		// ѡ���
	CControlsetDialog controlsetdlg;// ����ѡ���

	DWORD LastTime_Game;
	CTetris_Game tetris_game;	// ��Ϸ��ʾ�Լ���������

	KeyStatus keystatus[MAX_PLAYER][MAX_KEYDEF];	// ����״̬
	DWORD DefaultKeydef[MAX_PLAYER][MAX_KEYDEF];	// �����λ����

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTetrisView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	void WriteSettings();	// ���������INI�ļ�
	void ReadSettings();	// ��INI�ļ���ȡ���ò���
	void ResetInputBuffer();// ���ü��������keydown����
	virtual ~CTetrisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTetrisView)
	afx_msg void OnGameNew();			// �˵���Ϣ������Ϸ
	afx_msg void OnGameOption();		// �˵���Ϣ��ѡ��
	afx_msg void OnGamePause();			// �˵���Ϣ����ͣ��Ϸ
	afx_msg void OnGameControl();		// �˵���Ϣ������ѡ��
	afx_msg void OnGameStop();			// �˵���Ϣ��ֹͣ��Ϸ
	afx_msg void OnPlayer1();			// ѡ������Ϸ
	afx_msg void OnUpdatePlayer1(CCmdUI* pCmdUI);
	afx_msg void OnPlayer2();			// ѡ��˫����Ϸ
	afx_msg void OnUpdatePlayer2(CCmdUI* pCmdUI);
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);	// ʧȥ�����Pause Game
	afx_msg void OnUpdateGamePause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGameOption(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGameStop(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent); //��timer����
	afx_msg void OnGamePlaymusic();		//  �˵���Ϣ����������
	afx_msg void OnUpdateGamePlaymusic(CCmdUI* pCmdUI);
	afx_msg void OnGamePlaysound();		//  �˵���Ϣ����Ч����
	afx_msg void OnUpdateGamePlaysound(CCmdUI* pCmdUI);
	afx_msg void OnComputer();
	afx_msg void OnUpdateComputer(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnGameFullscreen();
	afx_msg void OnForcewindowmode();
	afx_msg void OnModeAivsai();
	afx_msg void OnModeAionly();
	afx_msg void OnUpdateModeAionly(CCmdUI* pCmdUI);
	afx_msg void OnUpdateModeAivsai(CCmdUI* pCmdUI);
//	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
//	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
};

#ifndef _DEBUG  // debug version in TetrisView.cpp
inline CTetrisDoc* CTetrisView::GetDocument()
   { return (CTetrisDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TETRISVIEW_H__D4CED32F_0003_4CBA_9337_8388ADE9820A__INCLUDED_)
