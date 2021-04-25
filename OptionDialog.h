#if !defined(AFX_OPTIONDIALOG_H__25B8B47F_9F49_4F27_AD20_09462EE70C39__INCLUDED_)
#define AFX_OPTIONDIALOG_H__25B8B47F_9F49_4F27_AD20_09462EE70C39__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionDialog.h : header file
//
//�����������ʾһ������ѡ��Ĵ���
//���Ե�����ʼ������ʾЧ����
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
	int		m_difficulty;	//��ʼ�����Ѷȼ���
	int		m_level;		//�ٶȼ���
	BOOL	m_shownext;		//�Ƿ���ʾ��һ��
	BOOL	m_smoothdown;	//ƽ���½�Ч��
	BOOL	m_smoothrotate;	//ƽ����תЧ��
	BOOL	m_leftwindow;	//�������ʱ���Ƿ�����ߴ���
	BOOL	m_othereffect;	//����Ч������ը�ȣ�
	int		m_ailevel;		//����AI����
	int		m_edit_volumn;	//����
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
