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
		float  GetFloat(uint32 field) const{ assert(field < file->mFieldCount); return *reinterpret_cast<float*>(data + field*4);	}
		uint32 GetUInt(uint32 field) const { assert(field < file->mFieldCount); return *reinterpret_cast<unsigned int*>(data + field*4);}
		int32  GetInt(uint32 field) const  { assert(field < file->mFieldCount); return *reinterpret_cast<int*>(data + field*4); }

		const char *GetString(uint32 field) const
		{
			assert(field < file->mFieldCount);
			uint32 stringOffset = GetUInt(field);
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

	Record	GetRecord(uint32 id);

	Iterator begin();	
	Iterator end();
	
	uint32	GetRecordCount() const			{ return mRecordCount;}
	void	SetRecordCount(uint32 count)	{ mRecordCount = count;}

	uint32  GetRecordSize()					{ return mRecordSize;}
	void	SetRecordSize(uint32 size)		{ mRecordSize = size;}

	uint32	GetFieldCount() const			{ return mFieldCount; }
	void	SetFieldCount(uint32 count)     { mFieldCount = count;}   

	uint32  GetStringTableSize()const		{ return mStringTableSize;}
	void	SetStringTableSize(uint32 size)	{ mStringTableSize = size; }

	void	SetDataInfo(char* data, char* strTable) { mData = data; mStrTable = strTable;}
	const char*	GetData()const				{return mData;}
	const char* GetStringTable()const		{return mStrTable;}

private:
	DBCFile();

	uint32		mRecordSize;
	uint32		mRecordCount;
	uint32		mFieldCount;
	uint32		mStringTableSize;
	char*		mData;
	char*		mStrTable;
};

class ENGINE_DLL CreatureModelData
{
public:
	static const char* path;
	static const uint32 sModelID = 0;
	static const uint32 sType = 1;
	static const uint32 sFileName = 2;

	CreatureModelData();
	~CreatureModelData();

	DBCFile::Record GetByFileName(const std::string& file);
	DBCFile::Record GetByID(uint32 id);
private:
	DBCFile* mDBCFile;
};

class ENGINE_DLL CreatureDisplayData
{
public:
	static const char* path;

	static const uint32 sCreatureID = 0;			// uint
	static const uint32 sModelID = 1;		// uint
	static const uint32 sNPCID = 3;			// uint
	static const uint32 sScale = 4;			// float
	static const uint32 sSkin1 = 6;			// string
	static const uint32 sSkin2 = 7;			// string
	static const uint32 sSkin3 = 8;			// string

	CreatureDisplayData();
	~CreatureDisplayData();

	DBCFile::Record GetByCreatureID(uint32 id);
	DBCFile::Record GetByModelID(uint32 id);
private:
	DBCFile* mDBCFile;
};