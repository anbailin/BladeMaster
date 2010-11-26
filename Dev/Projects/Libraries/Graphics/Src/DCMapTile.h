//#pragma  once
//
//#define TILESIZE (533.33333f)
//#define CHUNKSIZE ((TILESIZE) / 16.0f)
//#define UNITSIZE (CHUNKSIZE / 8.0f)
//#define ZEROPOINT (32.0f * (TILESIZE))
//
//class MapTile;
//class DCLiquid;
//class WMOInstance;
//
//class MapNode
//{
//public:
//	MapNode(u32 _x, u32 _y, u32 _s):x(_x),y(_y),size(_s){}
//	virtual ~MapNode();
//
//	virtual void Draw();
//	void	SetUp(MapTile* mt);
//
//	void	SetInfo(u32 _x, u32 _y,u32 _size){ x = _x; y = _y; size = _size; }
//protected:
//	MapNode* mChildren[4];
//	MapTile* mMapTile;
//
//	u32		x, y, size;
//	DCVector3	vmin, vmax, vcenter;
//};
//
//class MapChunk:public MapNode
//{
//public:
//	MapChunk();
//	~MapChunk();
//	
//	void Init(MapTile* tile, MPQFile& file);
//	void Draw();
//	void InitStrip();
//protected:
//	u32						mTexNum;
//	DCVector3					mBaseV;
//	float						mRadius;
//	u32						mAreaID;
//	s32						mAnimateFlag[4];
//	u16*						mStrip;
//	u32						mStripLen;
//
//	bool						mHasHole;
//	bool						mHasWater;
//	bool						mVisible;
//	float						mWaterLevel;
//
//	DCLiquid*					mLiquid;
//
//	DCVector3					min,max;
//
//	VertexBufferPtr				mVtxBuffer;
//	std::vector<DCTexturePtr>	mTexes;
//	std::vector<DCTexturePtr>	mAlphaMaps;
//	std::vector<DCTexturePtr>   mShadowMaps;
//};
//
////refer to .adt file
//class MapTile
//{
//public:
//	MapTile(int x0, int z0, char* filename);
//	~MapTile();
//
//	void Init(int x0, int z0, char* filename);
//	void Draw();
//	void DrawWater();
//	void DrawObjects();
//	void DrawSky();
//	void DrawModels();
//
//	/// Get chunk for sub offset x,z
//	MapChunk *GetChunk(unsigned int x, unsigned int y){ return &(mMapChunk[x][y]);	}
//
//	const std::string& GetTexStr(u32 ndx)const{ return mTextures[ndx]; }
//	const std::string& GetWMOStr(u32 ndx)const{ return mWmos[ndx]; }
//	const std::string& GetModelStr(u32 ndx)const{ return mModels[ndx]; }
//
//private:
//	std::vector<std::string>		mTextures;
//	std::vector<std::string>		mWmos;
//	std::vector<std::string>		mModels;
//
//	std::vector<WMOInstance>		mWmoInstance;
//	std::vector<DCModelInstancePtr>	mModelInstance;
//
//	int nWMO;
//	int nMDX;
//
//	int x, z;
//	bool ok;
//
//	//World *world;
//
//	float xbase, zbase;
//
//	MapNode mRootNode;
//
//	MapChunk mMapChunk[16][16];
//
//};