#include "stdafx.h"
#include "IdlePrevent.h"
#include "OptionsDlg.h"
#include "Settings.h"

IMPLEMENT_DYNAMIC(OptionsDlg, CDialog)

OptionsDlg::OptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(OptionsDlg::IDD, pParent)
{
}

OptionsDlg::~OptionsDlg()
{
}

void OptionsDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TXTTIMEOUT, c_txtTimeout);
    DDX_Control(pDX, IDC_CHKRDPFRIENDLYMETHOD, chkUseRDPFriendlyMethod);
}


BEGIN_MESSAGE_MAP(OptionsDlg, CDialog)
    ON_BN_CLICKED(IDOK, &OptionsDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &OptionsDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// OptionsDlg message handlers

BOOL OptionsDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    Settings s;
    c_txtTimeout.SetLimitText(4);
    CString tmpTextTimeoutVal;
    
    tmpTextTimeoutVal.Format(_T("%d"), s.timeoutInMinutes);
    c_txtTimeout.SetWindowText(tmpTextTimeoutVal);
    
    chkUseRDPFriendlyMethod.SetCheck( s.useRDPFriendlyWakeMethod ? BST_CHECKED : BST_UNCHECKED );
    return TRUE;
}

void OptionsDlg::OnBnClickedOk()
{
    CString enteredText;
    int numericalValue = 0;
    c_txtTimeout.GetWindowText(enteredText);
    BOOL validated = TRUE;
    
    if(enteredText.GetLength() == 0 )
        validated = FALSE;

    numericalValue = _wtoi(enteredText);
    if( (numericalValue == 0) || (numericalValue > 9999) )
        validated = FALSE;
    
    if(validated)
    {
        SaveSettings(numericalValue, chkUseRDPFriendlyMethod.GetCheck() == BST_CHECKED);
        OnOK();        
    }
    else
    {
        AfxMessageBox(_T("Please enter a valid value. Valid values range from 1 to 9999."), MB_ICONERROR | MB_OK);
    }
}

void OptionsDlg::OnBnClickedCancel()
{
    OnCancel();
}

void OptionsDlg::SaveSettings(int timeout, BOOL RDPFriendlyWakeMethod)
{
    Settings s;
    s.timeoutInMinutes = timeout;
    s.useRDPFriendlyWakeMethod = RDPFriendlyWakeMethod;
    s.WriteSettings();
}