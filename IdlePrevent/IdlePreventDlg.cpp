// IdlePreventDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IdlePrevent.h"
#include "IdlePreventDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

UINT CIdlePreventDlg::UWM_SHELLICON_MSG = ::RegisterWindowMessage(_T("UWM_SHELLICON_MSG-{8A439DA7-F0D7-4169-8705-6EDB93634399}"));
UINT CIdlePreventDlg::UWM_TIMER = ::RegisterWindowMessage(_T("UWM_TIMER-{969EC4DA-9905-4f68-A015-F03FC6F428A3}"));
#define RESET_COUNTER 5

// CIdlePreventDlg dialog
CIdlePreventDlg::CIdlePreventDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIdlePreventDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	isTimerEnabled = FALSE; // Set to false so the next toggle actually enables it.
	iTimerCount = 0; 
}

BEGIN_MESSAGE_MAP(CIdlePreventDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_TIMER, DoKeySending)
	ON_REGISTERED_MESSAGE(UWM_SHELLICON_MSG, ShellIconCallback)
	ON_COMMAND(IDTRAY_ENABLE, OnTrayEnableTimer)
	ON_COMMAND(IDTRAY_EXIT, OnTrayExit)
	//}}AFX_MSG_MAP
    ON_WM_WINDOWPOSCHANGING()
END_MESSAGE_MAP()

LRESULT CIdlePreventDlg::DoKeySending(WPARAM wparam, LPARAM lparam)
{
    iTimerCount++;
    if(iTimerCount >= RESET_COUNTER)
    {
        keybd_event(VK_RSHIFT,0xB6, KEYEVENTF_KEYUP,  0); 
        iTimerCount = 0;
    }
    return 0;
}

void CIdlePreventDlg::OnTrayEnableTimer()
{
    ToggleTimer();
}

void CIdlePreventDlg::ToggleTimer()
{
    if(isTimerEnabled)
    {
        KillTimer(UWM_TIMER);
    }
    else
    {
        SetTimer(UWM_TIMER, 60000, NULL);
    }
    isTimerEnabled = !isTimerEnabled;    
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
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
    mnuTray.LoadMenu(IDR_MENU1);
	ShellIcon_Initialize();
	ToggleTimer();
	return TRUE;  // return TRUE  unless you set the focus to a control
}
void CIdlePreventDlg::ShellIcon_Initialize()
{
    CString ttipText;
	NOTIFYICONDATA ni;
	ni.cbSize = NOTIFYICONDATA_V1_SIZE; 
	ni.hWnd = m_hWnd; 
	ni.uID = 1;
	ni.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    ni.uCallbackMessage = UWM_SHELLICON_MSG;
    ttipText = _T("IdlePrevent");
    _tcscpy_s(ni.szTip, ttipText);
	ni.hIcon = m_hIcon;
	
    // We have to keep retrying because Shell_NotifyIcon usually fails during Windows startup
    // on some machines with lots of other programs loading at startup as well.
    // We'll give it 30 seconds to consider some older machines running AOL/Norton etc.
	int iCount = 0;
    int maxCount = 30;
	while ( (Shell_NotifyIcon(NIM_ADD, &ni) && (iCount <= maxCount ) ) )
	{
        Sleep(1000);
        iCount += 1;
	}

	if(iCount > maxCount)
	{
		MessageBox(_T("Error while trying to create the System Tray Icon.\nThe program will continue to run in the background."),
					_T("IdlePrevent->ShellIcon_Initialize()"), MB_OK | MB_ICONINFORMATION);
	}
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
