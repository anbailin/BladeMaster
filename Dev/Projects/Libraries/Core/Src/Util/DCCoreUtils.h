#pragma once

/**
*	get game path
*   get the data paths
*/
class CORE_DLL DCSetupUtil
{
	SINGLETON_DECLARE(DCSetupUtil);
	
public:
	void SetGamePath();
	void SetDataPath();

	//utility
protected:
	void SetDataPathInFolder(const std::wstring& folder);

	//attributes	
private:
	std::wstring m_gamePath;
};