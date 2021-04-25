// TetrisDoc.h : interface of the CTetrisDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TETRISDOC_H__AB32D800_3632_46E0_817A_57521DEB55A9__INCLUDED_)
#define AFX_TETRISDOC_H__AB32D800_3632_46E0_817A_57521DEB55A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTetrisDoc : public CDocument
{
protected: // create from serialization only
	CTetrisDoc();
	DECLARE_DYNCREATE(CTetrisDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTetrisDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTetrisDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTetrisDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TETRISDOC_H__AB32D800_3632_46E0_817A_57521DEB55A9__INCLUDED_)
