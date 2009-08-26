#include "stdafx.h"
#include "IdlePrevent.h"
#include "OptionsDlg.h"

UINT OptionsDlg::UWM_SET_TIMEOUT = ::RegisterWindowMessage(_T("UWM_SET_TIMEOUT-{8BD7ED10-C815-4cdd-9452-DB0072CFC544}"));
UINT OptionsDlg::UWM_GET_TIMEOUT = ::RegisterWindowMessage(_T("UWM_GET_TIMEOUT-{378232F3-538E-4488-943A-261905D3EADA}"));

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
}


BEGIN_MESSAGE_MAP(OptionsDlg, CDialog)
    ON_BN_CLICKED(IDOK, &OptionsDlg::OnBnClickedOk)
    ON_BN_CLICKED(IDCANCEL, &OptionsDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// OptionsDlg message handlers

BOOL OptionsDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
    c_txtTimeout.SetLimitText(4);
    CString tmpTextTimeoutVal;
    LRESULT lres;
    int timeout;
    
    lres = ::SendMessage(this->GetParent()->m_hWnd, UWM_GET_TIMEOUT, 0, 0);
    timeout = *(int*)lres;
    
    tmpTextTimeoutVal.Format(_T("%d"), timeout);
    c_txtTimeout.SetWindowText(tmpTextTimeoutVal);
    return TRUE;
}

void OptionsDlg::OnBnClickedOk()
{
    CString enteredText;
    int numericalValue = 0;
    c_txtTimeout.GetWindowText(enteredText);
    BOOL validationFailed = FALSE;
    
    if(enteredText.GetLength() == 0 )
        validationFailed = TRUE;

    numericalValue = _wtoi(enteredText);
    if( (numericalValue == 0) || (numericalValue > 9999) )
        validationFailed = TRUE;
    
    if(validationFailed)
    {
        AfxMessageBox(_T("Please enter a valid value. Valid values range from 1 to 9999."), MB_ICONERROR | MB_OK);
    }
    else
    {
        ::SendMessage(this->GetParent()->m_hWnd, UWM_SET_TIMEOUT, (WPARAM)numericalValue, 0);
        OnOK();
    }
}

void OptionsDlg::OnBnClickedCancel()
{
    OnCancel();
}
