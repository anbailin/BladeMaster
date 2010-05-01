#pragma once

class ENGINE_DLL DCFilePath
{
public:	
	DCFilePath():mRegroup(true){}
	DCFilePath(const char* path, const char* file);
	DCFilePath(const char* path)		{	SetFullPath(path);	}
	DCFilePath(const std::string& path)	{	SetFullPath(path);	}
	DCFilePath(const DCFilePath& _file);

	void SetPath(const char* path) { mPath = path; mRegroup = true;	}
	void SetFile(const char* file) { mFileName = file; mRegroup = true;	}
	
	void SetFullPath(const char* _path);
	void SetFullPath(const std::string& _path);
	const std::string& GetPath()const { return mPath;	}
	const std::string& GetFile()const { return mFileName;	}
	const std::string& GetWholeName() 
	{
		if(mRegroup)
		{
			mWholeName = mPath + mFileName;
			mRegroup = false;
		}
		return mWholeName;
	}
private:
	bool		mRegroup;
	std::string mPath;
	std::string mFileName;
	std::string mWholeName;
};