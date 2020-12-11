// BitmapViewer.cpp : implementation file
//

#include "stdafx.h"
#include "CraCktrO_test.h"
#include "BitmapViewer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BitmapViewer

BitmapViewer::BitmapViewer()
{
}

BitmapViewer::~BitmapViewer()
{
}


BEGIN_MESSAGE_MAP(BitmapViewer, CWnd)
	//{{AFX_MSG_MAP(BitmapViewer)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// BitmapViewer message handlers

BOOL BitmapViewer::OnEraseBkgnd(CDC* pDC) 
{
// If we have an image then don't perform any erasing, since the OnPaint
    // function will simply draw over the background
    if (m_Bitmap.GetSafeHandle() != NULL)
        return TRUE;
	
    // Obviously we don't have a bitmap - let the base class deal with it.
	return CWnd::OnEraseBkgnd(pDC);
}

void BitmapViewer::OnPaint() 
{

// Draw the bitmap - if we have one.
    if (m_Bitmap.GetSafeHandle() != NULL)
    {
        CPaintDC dc(this); // device context for painting

        // Create memory DC
        CDC MemDC;
        if (!MemDC.CreateCompatibleDC(&dc))
            return;

        // Get Size of Display area
        CRect rect;
        GetClientRect(rect);

        // Get size of bitmap
        BITMAP bm;
        m_Bitmap.GetBitmap(&bm);
        
        // Draw the bitmap
        CBitmap* pOldBitmap = (CBitmap*) MemDC.SelectObject(&m_Bitmap);
        dc.StretchBlt(0, 0, rect.Width(), rect.Height(), 
                      &MemDC, 
                      0, 0, bm.bmWidth, bm.bmHeight, 
                      SRCCOPY);
        MemDC.SelectObject(pOldBitmap);      
    }
    
    // Do not call CWnd::OnPaint() for painting messages 
    }
	
BOOL BitmapViewer::SetBitmap(UINT nIDResource)
{
    return m_Bitmap.LoadBitmap(nIDResource);
}


