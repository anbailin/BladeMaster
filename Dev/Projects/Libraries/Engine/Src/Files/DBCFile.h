#pragma once

#include <cassert>
#include <string>

/**
*	client database files, which stored names
*/
class DBCFile
{
public:
	static DBCFile* Create(const std::string& path);

	~DBCFile();

	class Iterator;
	class Record
	{
	public:
		float  GetFloat(u32 field) const{ assert(field < file->mFieldCount); return *reinterpret_cast<float*>(data + field*4);	}
		u32 GetUInt(u32 field) const { assert(field < file->mFieldCount); return *reinterpret_cast<unsigned int*>(data + field*4);}
		s32  GetInt(u32 field) const  { assert(field < file->mFieldCount); return *reinterpret_cast<int*>(data + field*4); }

		const char *GetString(u32 field) const
		{
			assert(field < file->mFieldCount);
			u32 stringOffset = GetUInt(field);
			assert(stringOffset < file->mStringTableSize);
			return reinterpret_cast<char*>(file->mStrTable + stringOffset);
		}
	private:
		Record(DBCFile* file, char* offset): file(file), data(offset) {}
		char*		data;
		DBCFile*	file;

		friend class DBCFile;
		friend class DBCFile::Iterator;
	};

	class Iterator
	{
	public:
		Iterator(DBCFile* file, char* offset):record(file, offset) {}
		Iterator& operator++() {  record.data += record.file->mRecordSize;  return *this;  }	

		Record const& operator*() const { return record; }
		const Record* operator->() const { return &record;}

		bool operator==(const Iterator &b) const{ return record.data == b.record.data; }
		bool operator!=(const Iterator &b) const{ return record.data != b.record.data; }
	private:
		Record record;
	};

	Record	GetRecord(u32 id);

	Iterator begin();	
	Iterator end();
	
	u32	GetRecordCount() const			{ return mRecordCount;}
	void	SetRecordCount(u32 count)	{ mRecordCount = count;}

	u32  GetRecordSize()					{ return mRecordSize;}
	void	SetRecordSize(u32 size)		{ mRecordSize = size;}

	u32	GetFieldCount() const			{ return mFieldCount; }
	void	SetFieldCount(u32 count)     { mFieldCount = count;}   

	u32  GetStringTableSize()const		{ return mStringTableSize;}
	void	SetStringTableSize(u32 size)	{ mStringTableSize = size; }

	void	SetDataInfo(char* data, char* strTable) { mData = data; mStrTable = strTable;}
	const char*	GetData()const				{return mData;}
	const char* GetStringTable()const		{return mStrTable;}

private:
	DBCFile();

	u32		mRecordSize;
	u32		mRecordCount;
	u32		mFieldCount;
	u32		mStringTableSize;
	char*		mData;
	char*		mStrTable;
};

class ENGINE_DLL CreatureModelData
{
public:
	static const char* path;
	static const u32 sModelID = 0;
	static const u32 sType = 1;
	static const u32 sFileName = 2;

	CreatureModelData();
	~CreatureModelData();

	DBCFile::Record GetByFileName(const std::string& file);
	DBCFile::Record GetByID(u32 id);
private:
	DBCFile* mDBCFile;
};

class ENGINE_DLL CreatureDisplayData
{
public:
	static const char* path;

	static const u32 sCreatureID = 0;			// uint
	static const u32 sModelID = 1;		// uint
	static const u32 sNPCID = 3;			// uint
	static const u32 sScale = 4;			// float
	static const u32 sSkin1 = 6;			// string
	static const u32 sSkin2 = 7;			// string
	static const u32 sSkin3 = 8;			// string

	CreatureDisplayData();
	~CreatureDisplayData();

	DBCFile::Record GetByCreatureID(u32 id);
	DBCFile::Record GetByModelID(u32 id);
private:
	DBCFile* mDBCFile;
};