// CraCktrO_testDlg.h : header file
//

#if !defined(AFX_CRACKTRO_TESTDLG_H__17E459C8_7B4A_45DD_AE44_742801AD3B8F__INCLUDED_)
#define AFX_CRACKTRO_TESTDLG_H__17E459C8_7B4A_45DD_AE44_742801AD3B8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCraCktrO_testDlg dialog

#include "BitmapViewer.h"
#include "OpenGLAnim.h"
#include "MatrixStatic.h"

class CCraCktrO_testDlg : public CDialog
{
// Construction
public:
	CCraCktrO_testDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCraCktrO_testDlg)
	enum { IDD = IDD_CRACKTRO_TEST_DIALOG };
	
	CMatrixStatic m_lcd;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCraCktrO_testDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
//	CString	m_Path[2];
	CString	m_Path_a;
	CString	m_Path_b;
	HICON m_hIcon;
	BitmapViewer m_BitmapViewer;
	COpenGLAnim OpenGLAnim;
	// Init Mp3 var
	HWND m_mp_1;
	HWND m_mp_2;

	// Generated message map functions
	//{{AFX_MSG(CCraCktrO_testDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRACKTRO_TESTDLG_H__17E459C8_7B4A_45DD_AE44_742801AD3B8F__INCLUDED_)
