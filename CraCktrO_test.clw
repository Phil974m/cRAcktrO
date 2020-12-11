; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=COpenGLAnim
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "CraCktrO_test.h"

ClassCount=5
Class1=CCraCktrO_testApp
Class2=CCraCktrO_testDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=COpenGLAnim
Class5=CMatrixStatic
Resource3=IDD_CRACKTRO_TEST_DIALOG

[CLS:CCraCktrO_testApp]
Type=0
HeaderFile=CraCktrO_test.h
ImplementationFile=CraCktrO_test.cpp
Filter=N
LastObject=CCraCktrO_testApp

[CLS:CCraCktrO_testDlg]
Type=0
HeaderFile=CraCktrO_testDlg.h
ImplementationFile=CraCktrO_testDlg.cpp
Filter=D
LastObject=IDC_LCD1
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=CraCktrO_testDlg.h
ImplementationFile=CraCktrO_testDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CRACKTRO_TEST_DIALOG]
Type=1
Class=CCraCktrO_testDlg
ControlCount=5
Control1=IDCANCEL,button,1342242816
Control2=IDC_STATIC_OGL,static,1073872896
Control3=IDC_IMG,static,1342308359
Control4=IDC_LCD,static,1342308364
Control5=IDC_cRacK,button,1342242816

[CLS:COpenGLAnim]
Type=0
HeaderFile=OpenGLAnim.h
ImplementationFile=OpenGLAnim.cpp
BaseClass=CWnd
Filter=W
LastObject=COpenGLAnim
VirtualFilter=WC

[CLS:CMatrixStatic]
Type=0
HeaderFile=MatrixStatic.h
ImplementationFile=MatrixStatic.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CMatrixStatic

