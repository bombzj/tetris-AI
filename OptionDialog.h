#if !defined(AFX_OPTIONDIALOG_H__25B8B47F_9F49_4F27_AD20_09462EE70C39__INCLUDED_)
#define AFX_OPTIONDIALOG_H__25B8B47F_9F49_4F27_AD20_09462EE70C39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionDialog.h : header file
//
//这个类用于显示一个设置选项的窗口
//可以调整初始级别、显示效果等
/////////////////////////////////////////////////////////////////////////////
// COptionDialog dialog

class COptionDialog : public CDialog
{
// Construction
public:
	COptionDialog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionDialog)
	enum { IDD = IDD_OPTION };
	CSliderCtrl	m_slider_volumn;
	CSpinButtonCtrl	m_spin_ailevel;
	CSpinButtonCtrl	m_spin_level;
	CSpinButtonCtrl	m_spin_difficulty;
	int		m_difficulty;	//初始行数难度级别
	int		m_level;		//速度级别
	BOOL	m_shownext;		//是否显示下一个
	BOOL	m_smoothdown;	//平滑下降效果
	BOOL	m_smoothrotate;	//平滑旋转效果
	BOOL	m_leftwindow;	//单人玩的时候是否在左边窗口
	BOOL	m_othereffect;	//其他效果（爆炸等）
	int		m_ailevel;		//电脑AI级别
	int		m_edit_volumn;	//音量
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderVolumn(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONDIALOG_H__25B8B47F_9F49_4F27_AD20_09462EE70C39__INCLUDED_)
