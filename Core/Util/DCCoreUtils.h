#pragma once

/**
*	get game path
*   get the data paths
*/
class CORE_DLL DCSetupUtil
{
public:
	SINGLETON_DECLARE(DCSetupUtil);
	
	void SetGamePath();
	void SetDataPath();

	//utility
protected:
	void SetDataPathInFolder(const std::wstring& folder);

	//attributes	
private:
	std::wstring m_gamePath;
};