#include "CorePrivate.h"
#include "mpq_lib.h"


//----------------------------------[MPQArchive]--------------------------------------------
typedef std::vector<mpq_archive*> ArchiveSet;
ArchiveSet gOpenArchives;

MPQArchive::MPQArchive(const char* filename):mOpen(false)
{
	int result = libmpq_archive_open(&mMPQArchive, (unsigned char*)filename);

	if(result) 
	{
		assert(0&&"fail at open mpq archive");
		return;
	}
	gOpenArchives.push_back(&mMPQArchive);
	mOpen = true;
}

MPQArchive::~MPQArchive()
{
	close();
}

inline void MPQArchive::close()
{
	if(mOpen==true)
	{
		libmpq_archive_close(&mMPQArchive);
		mOpen = false;
	}
}

//----------------------------------[MPQFile]--------------------------------------------
MPQFile::MPQFile(const char* filename):
	eof(false),
	buffer(0),
	pointer(0),
	size(0)
{
	for(ArchiveSet::iterator i=gOpenArchives.begin(); i!=gOpenArchives.end();++i)
	{
		mpq_archive &mpq_a = **i;
		int fileno = libmpq_file_number(&mpq_a, filename);
		if(fileno == LIBMPQ_EFILE_NOT_FOUND)
			continue;
		// Found!
		size = libmpq_file_info(&mpq_a, LIBMPQ_FILE_UNCOMPRESSED_SIZE, fileno);
		// HACK: in patch.mpq some files don't want to open and give 1 for filesize
		if (size<=1) 
		{
			eof = true;
			buffer = 0;
			return;
		}
		buffer = new char[size];
		libmpq_file_getdata(&mpq_a, fileno, (unsigned char*)buffer);
		return;
	}
	eof = true;
	buffer = 0;
}

MPQFile::~MPQFile()
{
	close();
}


void
MPQFile::openFile(const char* filename)
{
	eof = false;
	buffer = 0;
	pointer = 0;
	size = 0;
	//if( useLocalFiles ) {
	//	wxString fn = gamePath;
	//	fn.Append(wxString(filename, wxConvUTF8));

	//	if (wxFile::Exists(fn)) {
	//		// success
	//		wxFile file;
	//		// if successfully opened
	//		if (file.Open(fn, wxFile::read)) {
	//			size = file.Length();
	//			if (size > 0) {
	//				buffer = new unsigned char[size];
	//				// if successfully read data
	//				if (file.Read(buffer, size) > 0) {
	//					eof = false;
	//					file.Close();
	//					return;
	//				} else {
	//					wxDELETEA(buffer);
	//					eof = true;
	//					size = 0;
	//				}
	//			}
	//			file.Close();
	//		}
	//	}
	//}

	for(ArchiveSet::iterator i=gOpenArchives.begin(); i!=gOpenArchives.end(); ++i)
	{
		mpq_archive &mpq_a = **i;
		int fileno = libmpq_file_number(&mpq_a, filename);
		if(fileno == LIBMPQ_EFILE_NOT_FOUND)
			continue;

		// Found!
		size = libmpq_file_info(&mpq_a, LIBMPQ_FILE_UNCOMPRESSED_SIZE, fileno);

		// HACK: in patch.mpq some files don't want to open and give 1 for filesize
		if (size<=1)
		{
			eof = true;
			buffer = 0;
			return;
		}

		buffer = new char[size];
		libmpq_file_getdata(&mpq_a, fileno, (u8*)buffer);
		return;
	}

	eof = true;
	buffer = 0;
}

size_t MPQFile::read(void* dest, size_t bytes)
{
	if (eof) return 0;

	size_t rpos = pointer + bytes;
	if (rpos > size)
	{
		bytes = size - pointer;
		eof = true;
	}

	memcpy(dest, &(buffer[pointer]), bytes);

	pointer = rpos;

	return bytes;
}

bool MPQFile::isEof()
{
    return eof;
}

void MPQFile::seek(int offset)
{
	pointer = offset;
	eof = (pointer >= size);
}

void MPQFile::seekRelative(int offset)
{
	pointer += offset;
	eof = (pointer >= size);
}

void MPQFile::close()
{
	if (buffer) delete[] buffer;
	buffer = 0;
	eof = true;
}

size_t MPQFile::getSize()
{
	return size;
}

size_t MPQFile::getPos()
{
	return pointer;
}

char* MPQFile::getBuffer()
{
	return buffer;
}

char* MPQFile::getPointer()
{
	return buffer + pointer;
}

void flipcc(char *fcc)
{
	char t;
	t=fcc[0];
	fcc[0]=fcc[3];
	fcc[3]=t;
	t=fcc[1];
	fcc[1]=fcc[2];
	fcc[2]=t;
}