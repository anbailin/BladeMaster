#pragma once

#include "DCAABoundingBox.h"

//struct MapChunkHeader
//{
//	uint32 flags;
//	uint32 ix;
//	uint32 iy;
//	uint32 nLayers;
//	uint32 nDoodadRefs;
//	uint32 ofsHeight;
//	uint32 ofsNormal;
//	uint32 ofsLayer;
//	uint32 ofsRefs;
//	uint32 ofsAlpha;
//	uint32 sizeAlpha;
//	uint32 ofsShadow;
//	uint32 sizeShadow;
//	uint32 areaid;
//	uint32 nMapObjRefs;
//	uint32 holes;
//	uint16 s1;
//	uint16 s2;
//	uint32 d1;
//	uint32 d2;
//	uint32 d3;
//	uint32 predTex;
//	uint32 nEffectDoodad;
//	uint32 ofsSndEmitters;
//	uint32 nSndEmitters;
//	uint32 ofsLiquid;
//	uint32 sizeLiquid;
//	float  zpos;
//	float  xpos;
//	float  ypos;
//	uint32 textureId;
//	uint32 props;
//	uint32 effectId;
//};
//
//struct WMOGroupHeader 
//{
//	uint32 nameStart, nameStart2, flags;
//	DCVector3 mBox0,mBox1;
//	uint16 portalStart, portalCount;
//	uint16 batches[4];
//	uint8 fogs[4];
//	int32 unk1, id, unk2, unk3;
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
//0x00  uint32  nTextures - number of textures (BLP Files)  
//0x04  uint32  nGroups - number of WMO groups  
//0x08  uint32  nPortals - number of portals  
//0x0C  uint32  nLights - number of lights  
//0x10  uint32  nModels - number of M2 models imported  
//0x14  uint32  nDoodads - number of doodads (M2 instances)  
//0x18  uint32  nSets - number of doodad sets  
//0x1C  uint32  ambient color?  
//0x20  uint32  WMO ID (column 2 in WMOAreaTable.dbc)  
//0x24  float[3]  Bounding box corner 1  
//0x30  float[3]  Bounding box corner 2  
//0x3C  uint32  always 0?  
//*/
//struct WMOHeader
//{
//	uint32 mTextureNum;
//	uint32 mGroupNum;
//	uint32 mPortalNum;
//	uint32 mLightNum;
//	uint32 mDoodadNum;
//	uint32 mDoodadSetNum;
//	uint32 mAmbientColor;
//	uint32 mWMOID;
//	DCAABoundingBox	mBoundingBox;
//	uint32 unknownA;
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
//	uint32			mFlag;
//	DCAABoundingBox mBoundingBox;
//	int32			mNameOffset;
//};
//
///*
//0x00  uint32  Offset to the start of the model's filename in the MODN chunk.  
//0x04  3 * float  Position (X,Z,-Y)  
//0x10  float  W component of the orientation quaternion  
//0x14  3 * float  X, Y, Z components of the orientaton quaternion  
//0x20  float  Scale factor  
//0x24  4 * uint8  (B,G,R,A) color. Unknown. It is often (0,0,0,255). (something to do with lighting maybe?)  
//
//*/
//struct WMOMODDChunk
//{
//	uint32		mNameOffset;
//	DCVector3	mTranslation;
//	float		mAngle;
//	DCVector3	mAxis;
//	float		mScale;
//	uint32		mColor;
//};
//
///*
//0x00  uint32  ID (index in the MMDX list)  
//0x04  uint32  unique identifier for this instance  
//0x08  3 floats  Position (X,Y,Z)  
//0x14  3 floats  Orientation (A,B,C)  
//0x20  uint32  scale factor * 1024  
//*/
//struct ADTMDDFChunk
//{
//	uint32		mIndex;
//	uint32		guid;
//	DCVector3	mTranslation;
//	DCEuler 	mOrientation;
//	uint32		mScale;
//};
//
///*
//0x00  uint32  ID (index in the MWMO list)  
//0x04  uint32  unique identifier for this instance  
//0x08  3 floats  Position (X,Y,Z)  
//0x14  3 floats  Orientation (A,B,C)  
//0x20  3 floats  Position 2 - ?  
//0x2C  3 floats  Position 3 - ?  
//0x38  uint16  unknown (always 0?)  
//0x3A  uint16  Doodad set index  
//0x3C  uint32  Name set  
//*/
//struct ADTMODFChunk
//{
//	uint32		mIndex;
//	uint32		guid;
//	DCVector3	mTranslation;
//	DCEuler		mOrientation;
//	DCAABoundingBox mBoundingBox;
//	uint16      unkownA;
//	uint16		mDoodadSetIndex;
//	uint32		mNameSet;
//};