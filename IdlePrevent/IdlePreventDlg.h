// IdlePreventDlg.h : header file
//

#pragma once


// CIdlePreventDlg dialog
class CIdlePreventDlg : public CDialog
{
// Construction
public:
	CIdlePreventDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_IDLEPREVENT_DIALOG };

protected:
	BOOL isTimerEnabled;
	CMenu mnuTray;
	int iTimeoutValue;
	void ToggleTimer();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    static UINT UWM_SHELLICON_MSG;
    static UINT UWM_TIMER;
    static UINT UWM_SET_TIMEOUT;
    static UINT UWM_GET_TIMEOUT;
    LRESULT DoKeySending(WPARAM wparam, LPARAM lparam);
    void OnTrayEnableTimer();
    void OnTrayOptions();
    void OnTrayAbout();
    void OnTrayExit();
    void ShellIcon_Initialize();
    void ShellIcon_Terminate();
    void DoCleanup();

// Implementation
protected:
	HICON m_hIcon;
    void ToggleTrayMenu(const BOOL& bEnable);
    void EnableTimer(const BOOL& bEnable);
    
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg LRESULT ShellIconCallback(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT GetTimeout(WPARAM wparam, LPARAM lparam);
    afx_msg LRESULT SetTimeout(WPARAM wparam, LPARAM lparam);
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};
