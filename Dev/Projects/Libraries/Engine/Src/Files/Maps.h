#pragma once

#include "DCAABoundingBox.h"

//struct MapChunkHeader
//{
//	u32 flags;
//	u32 ix;
//	u32 iy;
//	u32 nLayers;
//	u32 nDoodadRefs;
//	u32 ofsHeight;
//	u32 ofsNormal;
//	u32 ofsLayer;
//	u32 ofsRefs;
//	u32 ofsAlpha;
//	u32 sizeAlpha;
//	u32 ofsShadow;
//	u32 sizeShadow;
//	u32 areaid;
//	u32 nMapObjRefs;
//	u32 holes;
//	u16 s1;
//	u16 s2;
//	u32 d1;
//	u32 d2;
//	u32 d3;
//	u32 predTex;
//	u32 nEffectDoodad;
//	u32 ofsSndEmitters;
//	u32 nSndEmitters;
//	u32 ofsLiquid;
//	u32 sizeLiquid;
//	float  zpos;
//	float  xpos;
//	float  ypos;
//	u32 textureId;
//	u32 props;
//	u32 effectId;
//};
//
//struct WMOGroupHeader 
//{
//	u32 nameStart, nameStart2, flags;
//	DCVector3 mBox0,mBox1;
//	u16 portalStart, portalCount;
//	u16 batches[4];
//	u8 fogs[4];
//	s32 unk1, id, unk2, unk3;
//};
//
//struct WMOBatch 
//{
//	signed char bytes[12];
//	unsigned int indexStart;
//	unsigned short indexCount, vertexStart, vertexEnd;
//	unsigned char flags, texture;
//};
//
///*
//0x00  u32  nTextures - number of textures (BLP Files)  
//0x04  u32  nGroups - number of WMO groups  
//0x08  u32  nPortals - number of portals  
//0x0C  u32  nLights - number of lights  
//0x10  u32  nModels - number of M2 models imported  
//0x14  u32  nDoodads - number of doodads (M2 instances)  
//0x18  u32  nSets - number of doodad sets  
//0x1C  u32  ambient color?  
//0x20  u32  WMO ID (column 2 in WMOAreaTable.dbc)  
//0x24  float[3]  Bounding box corner 1  
//0x30  float[3]  Bounding box corner 2  
//0x3C  u32  always 0?  
//*/
//struct WMOHeader
//{
//	u32 mTextureNum;
//	u32 mGroupNum;
//	u32 mPortalNum;
//	u32 mLightNum;
//	u32 mDoodadNum;
//	u32 mDoodadSetNum;
//	u32 mAmbientColor;
//	u32 mWMOID;
//	DCAABoundingBox	mBoundingBox;
//	u32 unknownA;
//};
//
//struct WMOMaterial 
//{
//	int flags;
//	int d1;
//	int transparent;
//	int nameStart;
//	unsigned int col1;
//	int d3;
//	int nameEnd;
//	unsigned int col2;
//	int d4;
//	float f1,f2;
//	int dx[5];
//	//// read up to here -_-
//	//TextureID tex;
//};
//
//struct WMOGroupInfo
//{
//	u32			mFlag;
//	DCAABoundingBox mBoundingBox;
//	s32			mNameOffset;
//};
//
///*
//0x00  u32  Offset to the start of the model's filename in the MODN chunk.  
//0x04  3 * float  Position (X,Z,-Y)  
//0x10  float  W component of the orientation quaternion  
//0x14  3 * float  X, Y, Z components of the orientaton quaternion  
//0x20  float  Scale factor  
//0x24  4 * u8  (B,G,R,A) color. Unknown. It is often (0,0,0,255). (something to do with lighting maybe?)  
//
//*/
//struct WMOMODDChunk
//{
//	u32		mNameOffset;
//	DCVector3	mTranslation;
//	float		mAngle;
//	DCVector3	mAxis;
//	float		mScale;
//	u32		mColor;
//};
//
///*
//0x00  u32  ID (index in the MMDX list)  
//0x04  u32  unique identifier for this instance  
//0x08  3 floats  Position (X,Y,Z)  
//0x14  3 floats  Orientation (A,B,C)  
//0x20  u32  scale factor * 1024  
//*/
//struct ADTMDDFChunk
//{
//	u32		mIndex;
//	u32		guid;
//	DCVector3	mTranslation;
//	DCEuler 	mOrientation;
//	u32		mScale;
//};
//
///*
//0x00  u32  ID (index in the MWMO list)  
//0x04  u32  unique identifier for this instance  
//0x08  3 floats  Position (X,Y,Z)  
//0x14  3 floats  Orientation (A,B,C)  
//0x20  3 floats  Position 2 - ?  
//0x2C  3 floats  Position 3 - ?  
//0x38  u16  unknown (always 0?)  
//0x3A  u16  Doodad set index  
//0x3C  u32  Name set  
//*/
//struct ADTMODFChunk
//{
//	u32		mIndex;
//	u32		guid;
//	DCVector3	mTranslation;
//	DCEuler		mOrientation;
//	DCAABoundingBox mBoundingBox;
//	u16      unkownA;
//	u16		mDoodadSetIndex;
//	u32		mNameSet;
//};