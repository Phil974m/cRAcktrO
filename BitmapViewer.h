#if !defined(AFX_BITMAPVIEWER_H__F272E84E_5EC1_4F61_968B_A389930F3286__INCLUDED_)
#define AFX_BITMAPVIEWER_H__F272E84E_5EC1_4F61_968B_A389930F3286__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BitmapViewer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BitmapViewer window

class BitmapViewer : public CWnd
{
// Construction
public:
	BitmapViewer();

// Attributes
public:
	BOOL SetBitmap(UINT nIDResource);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BitmapViewer)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~BitmapViewer();

	// Generated message map functions
protected:
	CBitmap m_Bitmap;
	//{{AFX_MSG(BitmapViewer)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BITMAPVIEWER_H__F272E84E_5EC1_4F61_968B_A389930F3286__INCLUDED_)
