#include "Core.h"


SINGLETON_DEFINE(DCSetupUtil);

void gLog(char *str, ...)
{
	//static bool glogfirst=true;
	//static FILE *flog;
	//errno_t error = 0;

	//if (glogfirst) 
	//{
	//	error = fopen_s(&flog,"log.txt","w");
	//	fclose(flog);
	//	glogfirst = false;
	//}
	//fopen_s(&flog, "log.txt","a");
	//fclose(flog);
}

void DCSetupUtil::SetGamePath()
{
	const u32 strSize = 1024;
	const wchar_t* dataPath = TEXT("Data\\");

	HKEY key;
	u32 dataSize;
	wchar_t path[strSize];

	memset(path, 0, sizeof(path));

	dataSize = 1024;

	// if it failed, look for World of Warcraft install
	u32 result = RegOpenKeyEx((HKEY)HKEY_LOCAL_MACHINE, TEXT("SOFTWARE\\Blizzard Entertainment\\World of Warcraft"), 0, KEY_QUERY_VALUE, &key);

	// If we found an install then set the game path, otherwise just set to C:\ for now
	if (result == ERROR_SUCCESS)
	{
		result = RegQueryValueEx(key, TEXT("InstallPath"), 0, NULL,(LPBYTE)path, &dataSize);
		RegCloseKey(key);

		m_gamePath += (const wchar_t*)path;
		m_gamePath += dataPath;
	} 
	else 
	{
		assert(0&&"can't find wow install path");
	}
}

void DCSetupUtil::SetDataPath()
{
	SetDataPathInFolder(m_gamePath);
}

void DCSetupUtil::SetDataPathInFolder(const std::wstring& Folder)
{
	std::wstring findPath = Folder+TEXT("*");
	const wchar_t* ext = TEXT(".MPQ");
	WIN32_FIND_DATA findData;
	HANDLE hFind = FindFirstFile(findPath.c_str(),&findData);

	const u32 strSize = 1024;
	char path[strSize];
	size_t convertedValue = 0;

	if(hFind==INVALID_HANDLE_VALUE)
	{
		return;
	}

	do 
	{
		if(findData.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)
		{
			if(wcscmp(findData.cFileName,TEXT("."))==0 || wcscmp(findData.cFileName,TEXT(".."))==0)
			{
				continue;
			}

			SetDataPathInFolder(Folder+findData.cFileName+TEXT("\\"));
		}
		else 
		{
			const wchar_t* fileName = findData.cFileName;
			const u32 nameLength = wcslen(fileName);
			const u32 extBias = nameLength-wcslen(ext);
			const wchar_t* extName = fileName+extBias;

			if(wcscmp(extName,ext)==0)
			{
				std::wstring archiveName(Folder);
				archiveName = archiveName + fileName;		
				wcstombs_s<strSize>(&convertedValue,path,archiveName.c_str(),strSize);
				new MPQArchive(path);
			}
		}
	} while (FindNextFile(hFind,&findData)!=0);
}