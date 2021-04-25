// OptionDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Tetris.h"
#include "OptionDialog.h"
//#include "DMUtil.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionDialog dialog
//extern	IDirectMusicAudioPath*  g_p3DAudiopath;
//extern	CMusicSegment*			g_pSound[5];

COptionDialog::COptionDialog(CWnd* pParent /*=NULL*/)
	: CDialog(COptionDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionDialog)
	m_difficulty = 0;
	m_level = 0;
	m_shownext = FALSE;
	m_smoothdown = FALSE;
	m_smoothrotate = FALSE;
	m_leftwindow = FALSE;
	m_othereffect = FALSE;
	m_ailevel = 0;
	m_edit_volumn = 0;
	//}}AFX_DATA_INIT
}


void COptionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionDialog)
	DDX_Control(pDX, IDC_SLIDER_VOLUMN, m_slider_volumn);
	DDX_Control(pDX, IDC_SPIN_AILEVEL, m_spin_ailevel);
	DDX_Control(pDX, IDC_SPIN_LEVEL, m_spin_level);
	DDX_Control(pDX, IDC_SPIN_DIFICULTY, m_spin_difficulty);
	DDX_Text(pDX, IDC_EDIT_DIFICULTY, m_difficulty);
	DDX_Text(pDX, IDC_EDIT_LEVEL, m_level);
	DDX_Check(pDX, IDC_CHECK_SHOWNEXT, m_shownext);
	DDX_Check(pDX, IDC_CHECK_SMOOTHDOWN, m_smoothdown);
	DDX_Check(pDX, IDC_CHECK_SMOOTHROTATE, m_smoothrotate);
	DDX_Check(pDX, IDC_LEFTWINDOW, m_leftwindow);
	DDX_Check(pDX, IDC_OTHEREFFECT, m_othereffect);
	DDX_Text(pDX, IDC_EDIT_AILEVEL, m_ailevel);
	DDX_Text(pDX, IDC_EDIT_VOLUMN, m_edit_volumn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionDialog, CDialog)
	//{{AFX_MSG_MAP(COptionDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_VOLUMN, OnCustomdrawSlider1)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_VOLUMN, OnReleasedcaptureSliderVolumn)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionDialog message handlers

BOOL COptionDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_spin_level.SetRange(1, MAX_LEVEL);
	m_spin_difficulty.SetRange(0, MAX_DIFICULTY);
	m_spin_ailevel.SetRange(1, MAX_AILEVEL);
	m_slider_volumn.SetRange(0, 100);

	m_slider_volumn.SetPos(m_edit_volumn);
	// TODO: Sound
	//m_slider_volumn.EnableWindow(g_pSound[0]!=NULL);	//如果directmusic创建失败，则无法调节
	//GetDlgItem(IDC_EDIT_VOLUMN)->EnableWindow(g_pSound[0]!=NULL);
	//GetDlgItem(IDC_LABEL_VOLUMN)->EnableWindow(g_pSound[0]!=NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionDialog::OnOK() 
{
	UpdateData();	
	CDialog::OnOK();
}

void COptionDialog::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_edit_volumn=m_slider_volumn.GetPos();
	UpdateData(FALSE);
	// TODO: Sound
	//if(g_p3DAudiopath)
	//	g_p3DAudiopath->SetVolume((m_edit_volumn-100)*10, 0);

	*pResult = 0;
}

void COptionDialog::OnReleasedcaptureSliderVolumn(NMHDR* pNMHDR, LRESULT* pResult) 
{// TODO: Sound
	//if(g_pSound[1])
	//	g_pSound[1]->Play( DMUS_SEGF_DEFAULT | DMUS_SEGF_SECONDARY, g_p3DAudiopath );
	*pResult = 0;
}
