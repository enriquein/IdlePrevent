// AboutDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IdlePrevent.h"
#include "AboutDlg.h"


// AboutDlg dialog

IMPLEMENT_DYNAMIC(AboutDlg, CDialog)

AboutDlg::AboutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(AboutDlg::IDD, pParent)
{

}

AboutDlg::~AboutDlg()
{
}

void AboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL AboutDlg::OnInitDialog()
{
    CString cpuBits;
    
	#ifdef _M_X64
	    cpuBits = _T("(64-bit)");    
	#else
	    cpuBits = _T("(32-bit)");
	#endif
	
	labelText.Format(_T("You are using idle prevent version 1.0 %s."), cpuBits);
	return TRUE;
}

BEGIN_MESSAGE_MAP(AboutDlg, CDialog)
END_MESSAGE_MAP()


// AboutDlg message handlers
