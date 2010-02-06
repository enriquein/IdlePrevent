#pragma once
#include "afxwin.h"

class OptionsDlg : public CDialog
{
	DECLARE_DYNAMIC(OptionsDlg)

public:
	OptionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~OptionsDlg();
    
// Dialog Data
	enum { IDD = IDD_OPTIONSDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    void SaveSettings(int timeout, BOOL RDPFriendlyWakeMethod);
    
	DECLARE_MESSAGE_MAP()
public:
    CEdit c_txtTimeout;
    virtual BOOL OnInitDialog();
    afx_msg void OnBnClickedOk();
    afx_msg void OnBnClickedCancel();
    CButton chkUseRDPFriendlyMethod;
};
