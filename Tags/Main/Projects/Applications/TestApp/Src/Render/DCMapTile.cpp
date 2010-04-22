#include "DCRenderHeader.h"
//
//#include "DCWMO.h"
////---------map tile-------------------------------------------------------------------------------------
//namespace
//{
//	struct NamePair
//	{
//		char* name[5];
//		uint32 size;
//		uint32 nextpos;
//		void ReadIn(MPQFile& file)
//		{
//			file.read(name,4);
//			file.read(&size,4);
//			flipcc((char*)name);
//			name[4] = 0;
//			nextpos = file.getPos() + size;
//		}
//	};
//
//	struct DataPair
//	{
//		char*	addr;
//		uint32	num;
//	};
//
//	struct DataDescPair
//	{
//		uint32 offset;
//		uint32 size;
//	};
//
//	struct MCINData
//	{
//		DataDescPair data[256];
//	};
//}
//
//
//void MapTile::Init(int x0, int z0, char *filename)
//{
//	mRootNode.SetInfo(0,0,16);
//
//	MPQFile file(filename);
//
//	NamePair name;
//	
//	MCINData tMCINData;
//
//	while(file.isEof() == false)
//	{
//		name.ReadIn(file);
//		
//		char* name_ptr = (char*)name.name;
//
//		if (!strcmp(name_ptr,"MCIN")) // chunk info
//		{
//			file.read(&tMCINData,sizeof(MCINData));
//		}else if (!strcmp(name_ptr,"MTEX")) //texture names
//		{
//			char* buf = file.getPointer();
//			char* p = buf;
//			while(p<buf+name.size)
//			{
//				std::string path(p);
//				p+=strlen(p) + 1;
//				fixname(path);
//				mTextures.push_back(path);
//			}
//		}else if (!strcmp(name_ptr,"MMDX")) //model names
//		{
//			char* buf = file.getPointer();
//			char* p = buf;
//			while(p<buf + name.size)
//			{
//				std::string path(p);
//				p+=strlen(p) + 1;
//				fixname(path);
//				mModels.push_back(path);
//			}
//		}else if (!strcmp(name_ptr,"MWMO")) 
//		{
//			char* buf = file.getPointer();
//			char* p = buf;
//			while(p<buf + name.size)
//			{
//				std::string path(p);
//				p+=strlen(p) + 1;
//				fixname(path);
//				mWmos.push_back(path);
//			}
//		}else if (!strcmp(name_ptr,"MDDF")) 
//		{
//			uint32 nModel = name.size/sizeof(ADTMDDFChunk);
//			mModelInstance.resize(nModel);
//
//			ADTMDDFChunk chunk;
//			for(uint32 i=0;i<nModel;i++)
//			{
//				file.read(&chunk,sizeof(ADTMDDFChunk));
//				const std::string & str = mModels[chunk.mIndex];
//
//				DCFilePath path()
//				DCModelPtr tModelPtr(DCWOWLoader::LoadModel(str));
//				DCModelInstancePtr tModelInstancePtr(new DCModelInstance);
//				tModelInstancePtr->Init(tModelPtr,chunk);
//				mModelInstance[i] = tModelInstancePtr;
//			}
//		}else if (!strcmp(name_ptr,"MODF")) 
//		{
//			uint32 nWMO = name.size/sizeof(ADTMODFChunk);
//			mWmoInstance.resize(nWMO);
//			
//			for(uint32 i=0;i<nWMO;i++)
//			{
//				ADTMODFChunk chunk;
//				const std::string str = mWmos[chunk.mIndex];
//
//				WMOPtr tWMOPtr(new WMO);
//				tWMOPtr->Init(str);
//
//				WMOInstancePtr ptr(new WMOInstance);
//				ptr->Init(tWMOPtr,chunk);
//				mWmoInstance[i] = ptr;
//			}
//		}
//
//		file.seek(name.nextpos);
//	}
//
//	for(uint32 i=0;i<16;i++)
//	{
//		for(uint32 j=0;j<16;j++)
//		{
//			file.seek(tMCINData.data[i*16 + j].offset);
//			mMapChunk[i][j].Init(this,file);
//		}
//	}
//
//	mRootNode.SetUp(this);
//}
////---------map node-------------------------------------------------------------------------------------
//MapNode::~MapNode()
//{
//	for(uint32 i=0;i<4;i++)
//	{
//		SafeDelete(mChildren[i]);
//	}
//}
//
//
//void MapNode::SetUp(MapTile *mt)
//{
//	mMapTile = mt;
//
//	if(size == 2)
//	{
//		mChildren[0] = &(mt->GetChunk(y,x));
//		mChildren[1] = &(mt->GetChunk(y,x+1));
//		mChildren[2] = &(mt->GetChunk(y+1,x));
//		mChildren[3] = &(mt->GetChunk(y+1,x+1));
//	}else
//	{
//		uint32 half = size/2;
//		mChildren[0] = new MapNode(x,y,half);			mChildren[0].SetUp(mt);
//		mChildren[1] = new MapNode(x+half,y,half);		mChildren[1].SetUp(mt);
//		mChildren[2] = new MapNode(x, y+half, half);	mChildren[2].SetUp(mt);
//		mChildren[3] = new MapNode(x+half,y+half,half);	mChildren[3].SetUp(mt);
//	}
//}
//
//void MapNode::Draw()
//{
//	for(uint32 i=0;i<4;i++)
//	{
//		mChildren[i]->Draw();
//	}
//}
//
//MapNode::~MapNode()
//{
//	if(size>2)
//	{
//		for(uint32 i=0;i<4;i++i)
//			SafeDelete(mChildren[i]);
//	}
//}
////--------map chunk--------------------------------------------------------------------------------------
//namespace
//{
//	const uint32 kMapBufferSize = 9*9 + 8*8;
//	const float  kDetailSize = 8.0f;
//	
//}
//
//MapChunk::MapChunk()
//{
//
//}
//
//MapChunk::~MapChunk()
//{
//
//}
//
//
//void MapChunk::Init(MapTile* tile, MPQFile& file)
//{
//	DCVertPosNorTex vtx[kMapBufferSize];
//
//	file.seekRelative(4);
//	char fcc[5];
//
//	uint32 size;
//	file.read(&size,4);
//	uint32 end = file.getPos() + size;
//
//	MapChunkHeader header;
//	f.read(&header,sizeof(MapChunkHeader));
//
//	mAreaID = header.areaid;
//	mBaseV.Set(header.xpos,header.ypos,-header.zpos);
//	
//	while(file.getPos() < end)
//	{
//		file.read(fcc,4);
//		file.read(&size,4);
//
//		flipcc(fcc);
//		fcc[4] = 0;
//
//		uint32 nextPos = file.getPos() + size;
//
//		if (!strcmp(fcc,"MCNR")) //normal---
//		{
//			nextPos = f.getPos() + 0x1C0;
//			uint8 data[3];
//			DCVertPosNorTex* _vtx = vtx;
//			for (int j=0; j<17; j++) 
//			{
//				for (int i=0; i<((j%2)?8:9); i++) 
//				{
//					f.read(data,3);
//					_vtx->normal.Set( (float)data[0]/127.0f, (float)data[2]/127.0f, (float)data[1]/127.0f );
//					_vtx++;
//				}
//			}
//		}else if(!strcmp(fcc,"MCVT"))//vertice---
//		{
//			DCVertPosNorTex* _vtx = vtx;
//
//			for (int j=0; j<17; j++) 
//			{
//				for (int i=0; i<((j%2)?8:9); i++) 
//				{
//					float h,xpos,zpos;
//					f.read(&h,4);
//					xpos = i * UNITSIZE;
//					zpos = j * 0.5f * UNITSIZE;
//					if (j%2) 
//					{
//						xpos += UNITSIZE*0.5f;
//					}
//					DCVector3 v = DCVector3(mBaseV.x+xpos, mBaseV.x+h, mBaseV.x+zpos);
//					_vtx->pos = v;
//					_vtx++;
//				}
//			}
//		}else if(!strcmp(fcc,"MCLY"))//textures---
//		{
//			mTexNum = (int)size / 16;
//
//			for (int i=0; i<nTextures; i++) 
//			{
//				int tex, flags;
//				file.read(&tex,4);
//				file.read(&flags, 4);
//
//				file.seekRelative(8);
//
//				flags &= ~0x100;
//
//				if (flags & 0x80) 
//				{
//					mAnimateFlag[i] = flags;
//				} else 
//				{
//					mAnimateFlag[i] = 0;
//				}
//
//				DCTexturePtr texPtr( DCWOWLoader::LoadTexture(mt->GetTexStr(tex)) );
//				mTexes[i] = texPtr;
//			}
//		}else if (!strcmp(fcc,"MCSH"))
//		{
//			;
//		}else if (!strcmp(fcc,"MCAL")) 
//		{
//			;
//		}else if (!strcmp(fcc,"MCLQ")) 
//		{
//		}
//
//		f.seek(nextPos);
//	}
//
//	mMapTile = mt;
//	
//	//tex coordinate
//	DCVertPosNorTex* _vtx = vtx;
//	const float detail_half = 0.5f * kDetailSize / 8.0f;
//	float tx,ty;
//	for (int j=0; j<17; j++)
//	{
//		for (int i=0; i<((j%2)?8:9); i++) 
//		{
//			tx = kDetailSize / 8.0f * i;
//			ty = kDetailSize / 8.0f * j * 0.5f;
//			if (j%2) 
//			{
//				tx += detail_half;
//			}
//			_vtx->tex.Set(tx,ty);
//			_vtx++;
//		}
//	}
//
//	const uint32 length = sizeof(DCVertPosNorTex) * kMapBufferSize;
//	BM_AssertHr( DEVICEPTR->CreateVertexBuffer(length, 0, 0, D3DPOOL_MANAGED, &mVtxBuffer, 0));
//}
//
//void MapChunk::InitStrip()
//{
//
//}
//
//void MapChunk::Draw()
//{
//	DCSimpleCreatureShader::Get()->Apply();
//
//	DCRenderer::ApplyTexture(0,mTexes[0]);
//
//	BM_AssertHr( DEVICEPTR->SetStreamSource( 0,mVtxBuffer, 0, sizeof(DCVertPosNorTex) ) );
//
//	BM_AssertHr( DEVICEPTR->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, kMapBufferSize-2));
//}