#pragma once

class Settings
{
public:
	Settings();
	~Settings();
    
    void ReadSettings();
	void WriteSettings();
	int timeoutInMinutes;
	BOOL useRDPFriendlyWakeMethod;

protected:
	CString iniPath;
};