//#include "DCCommonHeader.h"
//#include "DCFilePath.h"

#include "../EnginePCH.h"
void DCFilePath::SetFullPath(const char *_path)
{
	mWholeName = _path;
	uint32 seperator = mWholeName.find_last_of('\\');
	uint32 length = seperator + 1;
	mPath.assign(mWholeName.c_str(), 0, length);
	mFileName.assign(mWholeName.c_str(), length, mWholeName.size());
	mRegroup = false;
}

void DCFilePath::SetFullPath(const std::string& _path)
{
	mWholeName = _path;
	uint32 seperator = mWholeName.find_last_of('\\');
	uint32 length = seperator + 1;
	mPath.assign(mWholeName.c_str(), 0, length);
	mFileName.assign(mWholeName.c_str(), length, mWholeName.size());
	mRegroup = false;
}

DCFilePath::DCFilePath(const char* path, const char* file)
:	mRegroup(true)
{
	mPath = path;
	mFileName = file;
}

DCFilePath::DCFilePath(const DCFilePath& _file)
:	mRegroup(_file.mRegroup)
,	mPath(_file.mPath)
,	mFileName(_file.mFileName)
,	mWholeName(_file.mWholeName)
{

}