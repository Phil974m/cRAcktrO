#if !defined(AFX_MATRIXSTATIC_H__6D397C6B_F269_445C_89A5_B79669ED068A__INCLUDED_)
#define AFX_MATRIXSTATIC_H__6D397C6B_F269_445C_89A5_B79669ED068A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatrixStatic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatrixStatic window

class CMatrixStatic : public CStatic
{
// Construction
public:
	CMatrixStatic();
enum {SMALL = 0, LARGE, TINY};
enum {LEFT = 0, RIGHT, UP, DOWN};

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatrixStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
		void SetAutoPadding(bool pad, char ch = ' ');
	int  GetText(LPTSTR string,  int size);
	void SetDisplayColors(COLORREF bk,  COLORREF on,  COLORREF off);
	void SetBkColor(COLORREF bk);
	void SetColor(COLORREF off,  COLORREF on);
	void SetBitmapResource(UINT bitmap);
	void SetSize(int size = SMALL);
	void SetText(LPCTSTR lpszText);
	void StopScroll();
	void DoScroll(int speed, BOOL dir);
	void SetCustomCharSizes(int width, int height, int xspace,  int yspace);
	void AdjustClientYToSize(int size);
	void AdjustClientXToSize(int size);
	void SetNumberOfLines(int max = 0);
	void SetXCharsPerLine(int max = 0);
	virtual ~CMatrixStatic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMatrixStatic)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	
	bool GetCharBmpOffset(RECT *rc, char ch);
	char		m_cPadChar;
	CString		m_csStrText;
	bool		m_bModified, m_bImmediateUpdate, m_btimer, m_bAutoPad;	
	COLORREF	m_crOffColor,	m_crOnColor, m_crBackColor;
	UINT		m_iImagematrix, m_iTimer;
	int			m_icharwidth, m_icharheight, m_ixspacing, m_iyspacing;
	int			m_iMaxYChars, m_iMaxXChars, m_iDirection;
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATRIXSTATIC_H__6D397C6B_F269_445C_89A5_B79669ED068A__INCLUDED_)
