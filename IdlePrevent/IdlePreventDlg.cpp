#include "stdafx.h"
#include "IdlePrevent.h"
#include "IdlePreventDlg.h"
#include "Settings.h"
#include "OptionsDlg.h"
#include "AboutDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT CIdlePreventDlg::UWM_SHELLICON_MSG = ::RegisterWindowMessage(_T("UWM_SHELLICON_MSG-{8A439DA7-F0D7-4169-8705-6EDB93634399}"));
UINT CIdlePreventDlg::UWM_TIMER = ::RegisterWindowMessage(_T("UWM_TIMER-{969EC4DA-9905-4f68-A015-F03FC6F428A3}"));
UINT CIdlePreventDlg::UWM_SET_TIMEOUT = ::RegisterWindowMessage(_T("UWM_SET_TIMEOUT-{8BD7ED10-C815-4CDD-9452-DB0072CFC544}"));
UINT CIdlePreventDlg::UWM_GET_TIMEOUT = ::RegisterWindowMessage(_T("UWM_GET_TIMEOUT-{378232F3-538E-4488-943A-261905D3EADA}"));
UINT CIdlePreventDlg::UWM_TASKBAR_CREATED = ::RegisterWindowMessage(_T("TaskbarCreated"));

CIdlePreventDlg::CIdlePreventDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIdlePreventDlg::IDD, pParent)
{
    Settings s;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	isTimerEnabled = FALSE; // Initialize to false since we're not running a timer yet.
	iTimeoutValue = s.iTimeoutInMinutes; 
}

BEGIN_MESSAGE_MAP(CIdlePreventDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_TIMER, SendWakeEvent)
	ON_REGISTERED_MESSAGE(UWM_SHELLICON_MSG, ShellIconCallback)
	ON_REGISTERED_MESSAGE(UWM_SET_TIMEOUT, SetTimeout)
	ON_REGISTERED_MESSAGE(UWM_GET_TIMEOUT, GetTimeout)
	ON_REGISTERED_MESSAGE(UWM_TASKBAR_CREATED, ShellIcon_Initialize)
	ON_COMMAND(IDTRAY_ENABLE, OnTrayEnableTimer)
	ON_COMMAND(IDTRAY_OPTIONS, OnTrayOptions)
	ON_COMMAND(IDTRAY_EXIT, OnTrayExit)
	ON_COMMAND(IDTRAY_ABOUT, OnTrayAbout)
	//}}AFX_MSG_MAP
    ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()

/*  lparam contains a pointer to the numeric value to use as timeout for our timer. 
    sample call:
    LRESULT lres = ::SendMessage(hWnd, UWM_GET_TIMEOUT, 0, 0);
    int i = *(int*)lres;
*/
LRESULT CIdlePreventDlg::GetTimeout(WPARAM wparam, LPARAM lparam)
{
    return lparam = (LRESULT) &iTimeoutValue;
}

/* (int)wparam contains the numeric value to use as timeout for our timer. */
LRESULT CIdlePreventDlg::SetTimeout(WPARAM wparam, LPARAM lparam)
{
    Settings s;
    iTimeoutValue = (int)wparam;
    s.iTimeoutInMinutes = iTimeoutValue;
    s.WriteSettings();
    return 0;
}

LRESULT CIdlePreventDlg::SendWakeEvent(WPARAM wparam, LPARAM lparam)
{
	HDESK test = OpenInputDesktop(DF_ALLOWOTHERACCOUNTHOOK, TRUE,DESKTOP_CREATEMENU | DESKTOP_CREATEWINDOW |DESKTOP_ENUMERATE | DESKTOP_HOOKCONTROL |DESKTOP_WRITEOBJECTS | DESKTOP_READOBJECTS |DESKTOP_SWITCHDESKTOP |GENERIC_WRITE);
	if (test != NULL)
	{
		INPUT mouseInput[1];
		mouseInput[0].mi.dx = 0;
		mouseInput[0].mi.dy = 0;
		mouseInput[0].mi.mouseData = 0;
		mouseInput[0].mi.dwFlags = MOUSEEVENTF_MOVE;
		mouseInput[0].mi.time = 0;
		mouseInput[0].mi.dwExtraInfo = NULL;
		SendInput(1, mouseInput, sizeof(mouseInput));
		SetThreadExecutionState(ES_DISPLAY_REQUIRED);
	}
	CloseDesktop(test);
	return 0;
}

void CIdlePreventDlg::OnTrayOptions()
{
    OptionsDlg o((CWnd*) this);
    ToggleTrayMenu(FALSE);
    o.DoModal();
    if(isTimerEnabled)
    {
        EnableTimer(TRUE); // Refreshing the timeout value.
    }   
    ToggleTrayMenu(TRUE);
}

void CIdlePreventDlg::OnTrayAbout()
{
    AboutDlg abt((CWnd*) this);
    ToggleTrayMenu(FALSE);
    abt.DoModal();
    ToggleTrayMenu(TRUE);
}

// The idea is that if the timer is already enabled, just
// reset the timeout then to iTimeoutValue
void CIdlePreventDlg::EnableTimer(const BOOL& bEnable)
{
    if(isTimerEnabled)
    {
        KillTimer(UWM_TIMER);
    }
    
    if(bEnable)
    {
        // First convert value to seconds (*60) and then to milliseconds (*1000).
        // Remember iTimeoutValue represents the minutes.
        UINT milliseconds = iTimeoutValue * 60 * 1000;
        SetTimer(UWM_TIMER, milliseconds, NULL);
    }  
    isTimerEnabled = bEnable;    
}

void CIdlePreventDlg::ToggleTrayMenu(const BOOL& bEnable)
{	
	UINT lFlags;
	if(bEnable)
	{
		lFlags = MF_BYCOMMAND|MF_ENABLED;
	}
	else
	{
		lFlags = MF_BYCOMMAND|MF_DISABLED|MF_GRAYED;
	}
	mnuTray.GetSubMenu(0)->EnableMenuItem(IDTRAY_OPTIONS, lFlags);
	mnuTray.GetSubMenu(0)->EnableMenuItem(IDTRAY_EXIT, lFlags);
	mnuTray.GetSubMenu(0)->EnableMenuItem(IDTRAY_ENABLE, lFlags);
}

void CIdlePreventDlg::OnTrayEnableTimer()
{
    ToggleTimer();
}

void CIdlePreventDlg::ToggleTimer()
{
    EnableTimer(!isTimerEnabled);  
}

void CIdlePreventDlg::OnTrayExit()
{
    DoCleanup();
    EndDialog(0);
}

void CIdlePreventDlg::DoCleanup()
{
    if(isTimerEnabled)
    {
        KillTimer(UWM_TIMER);
        isTimerEnabled = FALSE;
    }
    ShellIcon_Terminate();
}

void CIdlePreventDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CIdlePreventDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
    mnuTray.LoadMenu(IDR_MENU1);
	ShellIcon_Initialize(0, 0);
	EnableTimer(TRUE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}
LRESULT CIdlePreventDlg::ShellIcon_Initialize(WPARAM wparam, LPARAM lparam)
{
    CString ttipText;
	NOTIFYICONDATA ni;
	ni.cbSize = NOTIFYICONDATA_V1_SIZE; 
	ni.hWnd = m_hWnd; 
	ni.uID = 1;
	ni.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    ni.uCallbackMessage = UWM_SHELLICON_MSG;
    ttipText = _T("IdlePrevent 1.1");
    _tcscpy_s(ni.szTip, ttipText);
	ni.hIcon = m_hIcon;
	
	Shell_NotifyIcon(NIM_ADD, &ni);
	return 0;
}

void CIdlePreventDlg::ShellIcon_Terminate()
{
	NOTIFYICONDATA ni;
	ni.cbSize = NOTIFYICONDATA_V1_SIZE; 
	ni.hWnd = m_hWnd; 
	ni.uID = 1;
	Shell_NotifyIcon(NIM_DELETE, &ni);
}

LRESULT CIdlePreventDlg::ShellIconCallback(WPARAM wParam, LPARAM lParam)
{
	if (lParam == WM_RBUTTONDOWN)
    {
        mnuTray.GetSubMenu(0)->CheckMenuItem(IDTRAY_ENABLE, isTimerEnabled ? MF_CHECKED : MF_UNCHECKED);
		CPoint pt;
		GetCursorPos(&pt);		
		SetForegroundWindow();
		mnuTray.GetSubMenu(0)->TrackPopupMenu(TPM_CENTERALIGN,pt.x,pt.y,this);
		PostMessage(WM_NULL, 0, 0);
	}
	return 0;
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CIdlePreventDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CIdlePreventDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CIdlePreventDlg::OnWindowPosChanging(WINDOWPOS* lpwndpos)
{
    lpwndpos->flags &= ~SWP_SHOWWINDOW;
    CDialog::OnWindowPosChanging(lpwndpos);
}
