// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IdlePrevent.h"
#include "AboutDlg.h"
#include "VersionNo.h"


// AboutDlg dialog

IMPLEMENT_DYNAMIC(AboutDlg, CDialog)

AboutDlg::AboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AboutDlg::IDD, pParent)
    , lblAppInfoStr(_T(""))
{

}

AboutDlg::~AboutDlg()
{
}

void AboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_LBLMAININFO, lblAppInfoStr);
}

BOOL AboutDlg::OnInitDialog()
{
    CString cpuBits;
    
	#ifdef _M_X64
	    cpuBits = _T("(64-bit)");    
	#else
	    cpuBits = _T("(32-bit)");
	#endif
	
	lblAppInfoStr.Format(_T("You are using IdlePrevent version %s %s."), _T(STRAPPVER), cpuBits);
	UpdateData(FALSE);
	return TRUE;
}

BEGIN_MESSAGE_MAP(AboutDlg, CDialog)
END_MESSAGE_MAP()


// AboutDlg message handlers
