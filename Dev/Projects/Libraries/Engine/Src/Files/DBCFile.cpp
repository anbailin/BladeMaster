#include "EnginePrivate.h"

//-----------------------DBCFile--------------------------------------------------------------------------
DBCFile::DBCFile():
mData(NULL),
mStrTable(NULL),
mRecordCount(0),
mRecordSize(0),
mFieldCount(0),
mStringTableSize(0)
{}

DBCFile::~DBCFile()
{
	SAFE_DELETE_ARRAY(mData);

	mStrTable = NULL;

	mRecordCount = 0;
	mRecordSize = 0;
	mFieldCount = 0;
	mStringTableSize = 0;
}

DBCFile::Iterator DBCFile::begin()
{
	assert(mData);
	return DBCFile::Iterator(this,mData);
}

DBCFile::Iterator DBCFile::end()
{
	assert(mData);
	return DBCFile::Iterator(this,mStrTable);
}

DBCFile::Record DBCFile::GetRecord(u32 id)
{
	assert(id<mRecordCount);
	return DBCFile::Record(this,mData + id*mRecordSize);
}

DBCFile* DBCFile::Create(const std::string& path)
{
	MPQFile mpq(path.c_str());
	
	if(mpq.isEof())
		return NULL;

	char header[4];
	mpq.read(header,0,sizeof(header));
	assert( header[0] == 'W' && header[1] == 'D' && header[2] == 'B' && header[3] == 'C');

	u32 info[4];	
	mpq.read(info,sizeof(info));

	DBCFile* result = new DBCFile;
	result->SetRecordCount(info[0]);
	result->SetFieldCount(info[1]);
	result->SetRecordSize(info[2]);
	result->SetStringTableSize(info[3]);
	
	u32 dataSize = result->GetRecordSize() * result->GetRecordCount();
	u32 totalSize = dataSize + result->GetStringTableSize();
	char* data = new char[totalSize];
	char* strblock = data + dataSize;
	mpq.read(data,totalSize);

	result->SetDataInfo(data,strblock);

	return result;
}

//-------------------------CreatureModelData------------------------------------------------------------------------

const char* CreatureModelData::path= "DBFilesClient\\CreatureModelData.dbc";

CreatureModelData::CreatureModelData()
{
	mDBCFile = DBCFile::Create(path);
	assert(mDBCFile);
}

CreatureModelData::~CreatureModelData()
{
	SAFE_DELETE(mDBCFile);
}

DBCFile::Record CreatureModelData::GetByID(u32 id)
{
	for(DBCFile::Iterator it = mDBCFile->begin();it!=mDBCFile->end();++it)
	{
		if(it->GetUInt(sModelID) == id)
			return *it;
	}
	assert(0);
	return *(mDBCFile->begin());//just do something meaningless under wrong situation
}

DBCFile::Record CreatureModelData::GetByFileName(const std::string &file)
{
	for(DBCFile::Iterator it = mDBCFile->begin(); it!=mDBCFile->end(); ++it)
	{
		const char* str = it->GetString(sFileName);
		
		//log code
		//wchar_t wstr[256];
		//MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED | MB_ERR_INVALID_CHARS, str,-1, wstr, 256);
		//OutputDebugString(wstr);
		//OutputDebugString(TEXT("\n"));
		if(strcmp(str,file.c_str())==0)
			return *it;
	}
	assert(0);
	return *(mDBCFile->begin());//just do something meaningless under wrong situation
}

//-------------------------CreatureDisplayData------------------------------------------------------------------------
const char* CreatureDisplayData::path = "DBFilesClient\\CreatureDisplayInfo.dbc";

CreatureDisplayData::CreatureDisplayData()
{
	mDBCFile = DBCFile::Create(path);
	assert(mDBCFile);
}

CreatureDisplayData::~CreatureDisplayData()
{
	SAFE_DELETE(mDBCFile);
}

DBCFile::Record CreatureDisplayData::GetByCreatureID(u32 id)
{
	for(DBCFile::Iterator it = mDBCFile->begin();it!=mDBCFile->end();++it)
	{
		if(it->GetUInt(sCreatureID)==id)
			return *it;
	}
	assert(0);//fail,just return something useless
	return *(mDBCFile->begin());
}

DBCFile::Record CreatureDisplayData::GetByModelID(u32 id)
{
	for(DBCFile::Iterator it = mDBCFile->begin();it!=mDBCFile->end();++it)
	{
		if(it->GetUInt(sModelID) == id)
			return *it;
	}
	assert(0);//fail, return something useless
	return *(mDBCFile->begin());
}