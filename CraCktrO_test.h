// CraCktrO_test.h : main header file for the CRACKTRO_TEST application
//

#if !defined(AFX_CRACKTRO_TEST_H__F0692EE5_5D7D_42CB_A6C8_AA123F6A2F4D__INCLUDED_)
#define AFX_CRACKTRO_TEST_H__F0692EE5_5D7D_42CB_A6C8_AA123F6A2F4D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCraCktrO_testApp:
// See CraCktrO_test.cpp for the implementation of this class
//

class CCraCktrO_testApp : public CWinApp
{
public:
	CCraCktrO_testApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCraCktrO_testApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCraCktrO_testApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRACKTRO_TEST_H__F0692EE5_5D7D_42CB_A6C8_AA123F6A2F4D__INCLUDED_)
