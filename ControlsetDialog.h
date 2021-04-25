#if !defined(AFX_CONTROLSETDIALOG_H__C02ADB0A_A26C_4ED0_AB1B_C9E998F535B8__INCLUDED_)
#define AFX_CONTROLSETDIALOG_H__C02ADB0A_A26C_4ED0_AB1B_C9E998F535B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ControlsetDialog.h : header file
//�����������ʾһ�����ü��̿��Ƽ��Ĵ���
//��ҿ��������Լ�ϰ�ߵļ�λ����
/////////////////////////////////////////////////////////////////////////////
// CControlsetDialog dialog
#include "Tetrisinput.h"

#define KEYBOARD_NUMBER			256
#define KEYBOARD_STRINGLENGTH	50

class CControlsetDialog : public CDialog
{
// Construction
public:
	CControlsetDialog(CWnd* pParent = NULL);   // standard constructor
	int playercontrol;			// 0��ʾplayer1��1��ʾplayer2
	int nkeydef;				// ��0-4�ֱ�Ϊ5����λ����
	DWORD Keydef[MAX_PLAYER][MAX_KEYDEF];	// ����������ҵļ�λ����
	UINT ControlID;				// ��Ӧ��edit�ؼ�ID

// Dialog Data
	//{{AFX_DATA(CControlsetDialog)
	enum { IDD = IDD_CONTROLSET };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CControlsetDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CControlsetDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSetfocusEditLeft1();
	afx_msg void OnSetfocusEditRight1();
	afx_msg void OnSetfocusEditRotate1();
	afx_msg void OnSetfocusEditBottom1();
	afx_msg void OnSetfocusEditDown1();
	afx_msg void OnSetfocusEditLeft2();
	afx_msg void OnSetfocusEditRight2();
	afx_msg void OnSetfocusEditRotate2();
	afx_msg void OnSetfocusEditBottom2();
	afx_msg void OnSetfocusEditDown2();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKillfocusEditBottom1();
	afx_msg void OnKillfocusEditBottom2();
	afx_msg void OnKillfocusEditDown1();
	afx_msg void OnKillfocusEditDown2();
	afx_msg void OnKillfocusEditLeft1();
	afx_msg void OnKillfocusEditLeft2();
	afx_msg void OnKillfocusEditRight1();
	afx_msg void OnKillfocusEditRight2();
	afx_msg void OnKillfocusEditRotate1();
	afx_msg void OnKillfocusEditRotate2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLSETDIALOG_H__C02ADB0A_A26C_4ED0_AB1B_C9E998F535B8__INCLUDED_)
