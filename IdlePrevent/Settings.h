#pragma once

class Settings
{
public:
	Settings();
	~Settings();
    
    void ReadSettings();
	void WriteSettings();
	int iTimeoutInMinutes;

protected:
	CString iniPath;
};