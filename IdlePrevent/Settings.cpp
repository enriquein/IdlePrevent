#include "stdafx.h"
#include <windows.h>
#include ".\Settings.h"

Settings::Settings()
{
    LPTSTR p = iniPath.GetBuffer(_MAX_PATH);
	SHGetSpecialFolderPath(NULL, p, CSIDL_APPDATA, FALSE);
    iniPath.ReleaseBuffer();
    iniPath += _T("\\IdlePrevent\\");
	if(_taccess(iniPath, 0) == -1)
	{
		_tmkdir(iniPath);
	}
    iniPath += _T("IdlePrevent.ini");
	ReadSettings();
}

Settings::~Settings() 
{ }

// The only reason you'd have to call this implicitly would be if you for some reason
// want to reload settings from file. 
void Settings::ReadSettings()
{
	timeoutInMinutes = (int)GetPrivateProfileInt(_T("IdlePrevent"), _T("TimeoutInMinutes"), 5, iniPath);
	useRDPFriendlyWakeMethod = (BOOL)GetPrivateProfileInt(_T("IdlePrevent"), _T("UseRDPFriendlyWakeMethod"), FALSE, iniPath);
}

void Settings::WriteSettings()
{
    CString buffer;
    buffer.Format(_T("%d"), timeoutInMinutes);
	WritePrivateProfileString(_T("IdlePrevent"), _T("TimeoutInMinutes"), buffer, iniPath);
	
	buffer.Format(_T("%d"), (int)useRDPFriendlyWakeMethod);
	WritePrivateProfileString(_T("IdlePrevent"), _T("UseRDPFriendlyWakeMethod"), buffer, iniPath);
}

