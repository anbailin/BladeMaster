#pragma once

struct BLPHeader
{
	char				mId[4];			//"blp2"
	uint32				mType;			//always 1
	uint8				mEncoding;		//1--a8r8g8b8, 2--dxt series
	uint8				mAlphaDepth;	//0--no alpha channel, 1--1 bit alpha, 8--8bit alpha
	uint8				mAlphaEncoding;	//0--dxt1 alpha(0,1 bit),1--DXT2/3 alpha(4bit alpha),7--DXT4/5(interpolated alpha)
	uint8				mHasMips;		//0--no mips, 1--has mips, the size determine the mipmap level;
	uint32				mWidth;			//power of 2
	uint32				mHeight;		//power of 2
	uint32				mMipmapOffset[16];
	uint32				mMipmapSize[16];
	DCRGBAColor8		pallete[256];

    inline uint32 GetMipMapLevel()
    {
        uint32 wMip = Log2(mWidth);
        uint32 hMip = Log2(mHeight);
        uint32 mip = max(wMip,hMip);

#ifdef _DEBUG
        uint32 offset_mip = 0;
        for(uint32 i=0;i<16;i++)
        {
            if(mMipmapOffset[i]!=0)
                offset_mip++;
        }

        assert(mip == offset_mip);
#endif

        return mip;
    }

    inline D3DFORMAT GetBLPFormat()
    {
        assert(mType==1);
        if(mEncoding==1)
            return D3DFMT_A8R8G8B8;
        else if(mAlphaEncoding==0)
            return D3DFMT_DXT1;
        else if(mAlphaEncoding==1)
            return D3DFMT_DXT3;
        else //if(mAlphaEncoding==7)
            return D3DFMT_DXT5;
    }
	inline void*		GetPalleteAddr(){return &(pallete[0]);}
};



class BLPFile
{
public:
    BLPFile(const std::string& path)
    :     mMPQFile(path.c_str())
    ,     mSize(0)
      {
          if(mMPQFile.isEof())
              return;

          mSize = mMPQFile.getSize();
          mBuffer = mMPQFile.getBuffer();
          mHeader = (BLPHeader*)mBuffer;
          mPath = path;
          mMipMapLevel = mHeader->GetMipMapLevel();
          mTexFormat = mHeader->GetBLPFormat();
          mTexDataAddr = mBuffer + mHeader->mMipmapOffset[0];
          mTexSize = mSize - mHeader->mMipmapOffset[0];
      }
	~BLPFile()
    {
        //the just share the mem of mMPQFile;
        //the buffer will be freed when mMPQFile is freed;
        mBuffer = NULL;
        mHeader = NULL;
        mTexDataAddr = NULL;
    }

	const BLPHeader* GetBLPHeader(){return mHeader;}
	const char*      GetBuffer(){return mBuffer;}
	const char*		 GetTexDataAddr(){return mTexDataAddr;}
	void*			 GetPalleteAddr()const {return mHeader->GetPalleteAddr();}
	void*			 GetMipMapAddr(uint32 val)const{return mBuffer + mHeader->mMipmapOffset[val];}

	uint32			 GetWidth()const {return mHeader?mHeader->mWidth:0;}
	uint32			 GetHeight()const {return mHeader?mHeader->mHeight:0;}
	uint32			 GetMipMapLevel()const {return mMipMapLevel;}
	uint32			 GetTexDataSize()const {return mTexSize; }	
	uint32			 GetMipMapSize(uint32 val)const {return mHeader->mMipmapSize[val];	}
	D3DFORMAT		 GetFormat()const {return mTexFormat;}
	bool			 Available()const {return mSize!=0;}

private:
	MPQFile			mMPQFile;
	BLPHeader*		mHeader;
	char*			mBuffer;
	char*			mTexDataAddr;

	uint32			mMipMapLevel;
	uint32			mSize;
	uint32			mTexSize;
	std::string		mPath;	
	D3DFORMAT		mTexFormat;

private://the forbidden functions
	const BLPFile& operator=(const BLPFile& file){ return *this; }
};

