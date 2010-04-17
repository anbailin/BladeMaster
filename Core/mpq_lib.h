#pragma once
#pragma warning (disable:4100)

#include "libmpq/mpq.h"

class CORE_DLL MPQArchive
{

public:
	MPQArchive(const char* filename);
	~MPQArchive();
	inline void close();
private:
	mpq_archive mMPQArchive;
	bool        mOpen;
};


class CORE_DLL MPQFile
{
public:
	MPQFile():eof(false),size(0),buffer(0),pointer(0) {}
	MPQFile(const char* filename);	// filenames are not case sensitive
	~MPQFile();

	void openFile(const char* filename);
	size_t	read(void* dest, size_t bytes);
	size_t  read(void* dest, size_t offset, size_t bytes){seek(offset); return read(dest,bytes);}
	size_t	getSize();
	size_t	getPos();
	char*	getBuffer();
	char*	getPointer();
	bool	isEof();
	void	seek(int offset);
	void	seekRelative(int offset);
	void	close();

private:
	bool eof;
	char *buffer;
	size_t pointer,size;
	// disable copying
	MPQFile(const MPQFile &f) {}
	void operator=(const MPQFile &f) {}
};

CORE_DLL void flipcc(char *fcc);