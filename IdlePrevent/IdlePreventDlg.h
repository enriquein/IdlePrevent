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
	int iTimerCount;
	CMenu mnuTray;
	void ToggleTimer();
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
    static UINT UWM_SHELLICON_MSG;
    static UINT UWM_TIMER;
    LRESULT DoKeySending(WPARAM wparam, LPARAM lparam);
    void OnTrayEnableTimer();
    void OnTrayExit();
    void ShellIcon_Initialize();
    void ShellIcon_Terminate();
    void DoCleanup();

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
    afx_msg LRESULT ShellIconCallback(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};
