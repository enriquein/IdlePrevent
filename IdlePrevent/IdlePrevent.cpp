#include "stdafx.h"
#include "IdlePrevent.h"
#include "IdlePreventDlg.h"
#include "LimitSingleInstance.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIdlePreventApp

BEGIN_MESSAGE_MAP(CIdlePreventApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CIdlePreventApp construction

CIdlePreventApp::CIdlePreventApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CIdlePreventApp object

CIdlePreventApp theApp;
CLimitSingleInstance g_SingleInstanceObj(_T("{980C42EF-856F-46dd-80BA-FBA72D728425}"), UNIQUE_TO_SESSION);
// {980C42EF-856F-46dd-80BA-FBA72D728425} Generated via GUIDGEN

// CIdlePreventApp initialization
BOOL CIdlePreventApp::InitInstance()
{
	// InitCommonControlsEx() is required on Windows XP if an application
	// manifest specifies use of ComCtl32.dll version 6 or later to enable
	// visual styles.  Otherwise, any window creation will fail.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Set this to include all the common control classes you want to use
	// in your application.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	// Is another instance running?
	if (g_SingleInstanceObj.IsAnotherInstanceRunning())
	{
		AfxMessageBox(_T("Program is already running."), MB_OK|MB_ICONERROR, 0);
		return FALSE;
	}
	
	CIdlePreventDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}
