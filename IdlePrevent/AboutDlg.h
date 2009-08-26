#pragma once


// AboutDlg dialog

class AboutDlg : public CDialog
{
	DECLARE_DYNAMIC(AboutDlg)

public:
	AboutDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~AboutDlg();

    CString labelText;
    
// Dialog Data
	enum { IDD = IDD_ABOUTDLG };
	virtual BOOL OnInitDialog();
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
