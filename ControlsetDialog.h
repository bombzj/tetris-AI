#if !defined(AFX_CONTROLSETDIALOG_H__C02ADB0A_A26C_4ED0_AB1B_C9E998F535B8__INCLUDED_)
#define AFX_CONTROLSETDIALOG_H__C02ADB0A_A26C_4ED0_AB1B_C9E998F535B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ControlsetDialog.h : header file
//这个类用于显示一个设置键盘控制键的窗口
//玩家可以设置自己习惯的键位设置
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
	int playercontrol;			// 0表示player1，1表示player2
	int nkeydef;				// 从0-4分别为5个键位设置
	DWORD Keydef[MAX_PLAYER][MAX_KEYDEF];	// 保存两个玩家的键位设置
	UINT ControlID;				// 对应的edit控件ID

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
