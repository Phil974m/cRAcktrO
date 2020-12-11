#if !defined(AFX_OPENGLANIM_H__B18C7CB9_BC39_4A61_8718_6958C7653A47__INCLUDED_)
#define AFX_OPENGLANIM_H__B18C7CB9_BC39_4A61_8718_6958C7653A47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenGLAnim.h : header file
//
#include "OpenGLDevice.h"
#include <GL\gl.h>
#include <GL\glu.h>
#include <gl\glaux.h>
#include <stdio.h>
#include <math.h>       // En tête pour les fonctions mathématiques

/////////////////////////////////////////////////////////////////////////////
// COpenGLAnim window

class COpenGLAnim : public CWnd
{
// Construction
public:
	COpenGLAnim();
	
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COpenGLAnim)
	//}}AFX_VIRTUAL

// Implementation
public:
	void Create(CRect rect,CWnd* parent);
	virtual ~COpenGLAnim();

	// Generated message map functions
protected:
	int InitGL();
	void TriangleGL();
	void DrawGLScene();
	OpenGLDevice openGLDevice;
	CClientDC* dc;
	float rotation;

	//{{AFX_MSG(COpenGLAnim)
	afx_msg void OnPaint();	
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENGLANIM_H__B18C7CB9_BC39_4A61_8718_6958C7653A47__INCLUDED_)
