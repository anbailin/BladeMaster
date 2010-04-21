#pragma once

//#include <string>
//
//#include "DCCommonHeader.h"
//
//#include "DCRenderType.h"
//#include "mpq_lib.h"


template<class TYPE>
class HeaderPair
{
public:
	TYPE number;
	TYPE offset;
};

typedef HeaderPair<uint32> HeaderPair32;
typedef HeaderPair<uint16> HeaderPair16;
//float floats[14];
struct PhysicsSettings 
{
	XMFLOAT3 VertexBox[2];
	float VertexRadius;
	XMFLOAT3 BoundingBox[2];
	float BoundingRadius;
};

#pragma pack(push,1)
struct MDXModelHeader 
{
	char id[4];
	uint8 version[4];
	uint32 nameLength;
	uint32 nameOfs;
	uint32 GlobalModelFlags; // 1: tilt x, 2: tilt y, 4:, 8: add another field in header, 16: ; (no other flags as of 3.1.1);

	HeaderPair32	mAnimDuration;	//nGlobalSequences 
	HeaderPair32	mAnim;			//nAnimations
	HeaderPair32    mAnimLookup;
	HeaderPair32	mBone;
	HeaderPair32	mKeyBoneLookup;//BonesAndLookups

	HeaderPair32	mVertex;
	uint32 nViews; // GeometryAndRendering	

	HeaderPair32	mColor;
	HeaderPair32	mTexture;
	HeaderPair32	mTransparency;
	HeaderPair32	mTexAnim;
	HeaderPair32	mTexReplace;

	HeaderPair32    mTexFlag;
	HeaderPair32    mBoneLookup;

	HeaderPair32	mTexLookup;
	HeaderPair32	mMaterialLookup;
	HeaderPair32	mTransparencyLookup;
	HeaderPair32	mTexAnimLookup;

	struct PhysicsSettings ps;

	HeaderPair32	mBoundingBoxIndex;
	HeaderPair32	mBoundingBoxVertex;
	HeaderPair32	mBoundingBoxNormal;

	HeaderPair32	mAttachments;
	HeaderPair32	mAttachLookup;
	uint32 nEvents; // 
	uint32 ofsEvents; // Used for playing sounds when dying and a lot else.
	HeaderPair32	mLight;
	HeaderPair32	mCamera;
	HeaderPair32    mCameraLookup; // Miscellaneous
	
	HeaderPair32	mRibbonEmitter;
	HeaderPair32	mParticleEmitter;
};

//---------------animation--------------------------------------------
struct MDXAnimSequence
{
	uint32		mAnimID;
	uint32		mTimeStart;
	uint32		mTimeEnd;

	float		mMoveSpeed;

	uint32		mLoopType;
	uint32		mFlag;

	uint32		unknownA;
	uint32		unknownB;

	uint32		mPlaySpeed;
	XMFLOAT3	mBoundingBoxA;
	XMFLOAT3	mBoundingBoxB;

	float		mRadius;
	uint32		unknownC;
};

struct MDXAnimSequenceWLK
{
	int16		mAnimID; // AnimationDataDB.ID
	int16		mSubAnimID;
	uint32		mLength;
	float		mMoveSpeed;

	uint32		mFlags;
	uint16		mProbability; // This is used to determine how often the animation is played. For all animations of the same type, this adds up to 0x7FFF (32767).
	uint16		unused;
	uint32		d1;
	uint32		d2;
	uint32		mPlaySpeed;  // note: this can't be play speed because it's 0 for some models

	XMFLOAT3	boxA, boxB; // Minimum Extent, Maximum Extend
	float		mRadius;  // Bounds Radius

	int16		mNextAnimation;
	int16		mIndex;
};

//AnimationBlock
struct MDXAnimationBlock
{
	int16			mInterpolation;
	int16			mSequenceID;
	HeaderPair32	mTimes;
	HeaderPair32	mKeys;
};

struct MDXFakeAnimationBlock 
{
	HeaderPair32	mTimes;
	HeaderPair32	mKeys;
};

struct AnimationBlockHeader
{
	HeaderPair32	Entries;
};

struct MDXBoneDef
{
	int32				mAnimID;
	int32				mFlag;
	int16				mParent;
	int16				mGeoID;
	int32				unknown; // new int added to the bone definitions.  Added in WoW 2.0
	MDXAnimationBlock	mTranslation;
	MDXAnimationBlock	mRotation;
	MDXAnimationBlock	mScaling;
	XMFLOAT3			mPivot;
};



//----------------texture animation-------------------------------------------
struct MDXTextureAnim
{
	MDXAnimationBlock	mTranslation;
	MDXAnimationBlock	mRotation;
	MDXAnimationBlock	mScaling;
};

struct ModelVertex {
	XMFLOAT3	pos;
	uint8		weights[4];
	uint8		bones[4];
	XMFLOAT3	normal;
	XMFLOAT2	texcoords;
	int			unk1, unk2; // always 0,0 so this is probably unused
};

//----------------Model Definition---------------------------------------------
struct MDXModelLOD
{
	char id[4];				 // Signature
	HeaderPair32 mIdxTable;	 //contains the table of index, later [ofsIndex]
	HeaderPair32 mIdxLookup; //IndexTable[IndexLook[i]] is the index for i_th lookup [ofsTris]
	uint32 nProps;
	uint32 ofsProps; // int32, additional vtx properties
	HeaderPair32 mSub;//[ofsSub], geometry ModelGeoset, materials/renderops/submeshes
	HeaderPair32 mTex;// ModelTexUnit, material properties/textures
	int32 lod;				 // LOD bias?
};

struct MDXGeometry
{
	uint32				mID;	
	
	uint16				mVertexStart;
	uint16				mVertexCount;

	uint16				mIndexStart;
	uint16				mIndexCount;
	uint16				nBones;		// number of bone indices, Number of elements in the bone lookup table.
	uint16				StartBones;		// ? always 1 to 4, Starting index in the bone lookup table.
	uint16				d5;		// ?
	uint16				rootBone;		// root bone?
	XMFLOAT3			BoundingBox[2];
	float				radius;
};


struct MDXMaterial
{
	uint16 flags;		// Usually 16 for static textures, and 0 for animated textures.
	uint16 shading;		// If set to 0x8000: shaders. Used in skyboxes to ditch the need for depth buffering. See below.
	uint16 op;			// Material this texture is part of (index into mat), the geometry index used by this material
	uint16 op2;			// Always same as above?
	int16 colorIndex;	// A Color out of the Colors-Block or -1 if none.
	uint16 flagsIndex;	// RenderFlags (index into render flags, TexFlags)
	uint16 texunit;		// Index into the texture unit lookup table.
	uint16 mode;		// See below.
	uint16 textureid;	// Index into Texture lookup table
	uint16 texunit2;	// copy of texture unit value?
	uint16 transid;		// Index into transparency lookup table.
	uint16 texanimid;	// Index into uvanimation lookup table. 
};

//-------------------little definitions-----------------------------------------------------------------
//the info from http://wowdev.org/wiki/index.php/M2
//nRenderFlags (uint16, uint16) pairs starting at ofsRenderFlags 
//
//The first value contains flags. 
//
//Flag  Meaning  
//0x01  Unlit  
//0x02  Unfogged?  
//0x04  Two-sided (no backface culling if set)  
//0x08   ?  
//0x10  Disable z-buffer?  
//
//The second value specifies the blending mode 
//
//Value  Meaning  
//0  Opaque  
//1  Alpha testing only  
//2  Alpha blending  
//3  Additive?  
//4  Additive alpha?  
//5  Modulate?  
//6  Used in the Deeprun Tram subway glass, supposedly (src=dest_color, dest=src_color) (?)  

struct MDXRenderFlag
{
	uint16				mFlag;
	uint16				mBlend;
};

struct MDXModelColor
{
	MDXAnimationBlock	mColor;
	MDXAnimationBlock	mOpacity;
};

struct MDXModelTransDef
{
	MDXAnimationBlock	mTrans;
};

enum EMDXTexType
{
	TEXTURE_FILENAME=0,			// Texture given in filename
	TEXTURE_BODY,				// Body + clothes
	TEXTURE_CAPE,				// Item, Capes ("Item\ObjectComponents\Cape\*.blp")
	TEXTURE_ARMORREFLECT,		// 
	TEXTURE_HAIR=6,				// Hair, bear
	TEXTURE_FUR=8,				// Tauren fur
	TEXTURE_INVENTORY_ART1,		// Used on inventory art M2s (1): inventoryartgeometry.m2 and inventoryartgeometryold.m2
	TEXTURE_QUILL,				// Only used in quillboarpinata.m2. I can't even find something referencing that file. Oo Is it used?
	TEXTURE_GAMEOBJECT1,		// Skin for creatures or gameobjects #1
	TEXTURE_GAMEOBJECT2,		// Skin for creatures or gameobjects #2
	TEXTURE_GAMEOBJECT3,		// Skin for creatures or gameobjects #3
	TEXTURE_INVENTORY_ART2		// Used on inventory art M2s (2): ui-buffon.m2 and forcedbackpackitem.m2 (LUA::Model:ReplaceIconTexture("texture"))
};

struct MDXModelTextureDef
{
	uint32				mType;	//EMDXTexType
	uint32				mFlag;
	uint32				mNameLength;
	uint32				mNameOffset;
};

//-------------------------------------------------------------------------------------------
struct MDXModelLightDef
{
	uint16				mType;
	uint16				mBone;
	XMFLOAT3			mPos;
	MDXAnimationBlock	mAmbColor;
	MDXAnimationBlock	mAmbIntensity;
	MDXAnimationBlock	mDiffuseColor;
	MDXAnimationBlock	mDiffuseIntensity;
	MDXAnimationBlock	mAttenuationStart;
	MDXAnimationBlock	mAttenuationEnd;
	MDXAnimationBlock	unknownA;
};

struct MDXModelCamera
{
	int32				mID;
	float				mFov;
	float				mClipNear;
	float				mClipFar;
	MDXAnimationBlock	mTransPos;
	XMFLOAT3			mPos;
	MDXAnimationBlock	mTransTarget;
	XMFLOAT3			mTarget;
	MDXAnimationBlock	mRot;
};


//------------------------Special Effects---------------------------------------------------

struct MDXModelParticleInfo 
{
	float				mID;

	uint32				mColorStart;
	uint32				mColorMid;
	uint32				mColorEnd;

	float				mSizeStart;
	float				mSizeMid;
	float				mSizeEnd;

	int16				mTileTexIndex[10];
	float				unkownA[3];
	float				mScales[3];
	float				mSlowdown;
	float				mRotation;
	float				unknownB[16];
};

union MDXParticleEmitterParam
{
	struct
	{
		MDXAnimationBlock	mEmitSpeed;
		MDXAnimationBlock	mSpeedVariation;
		MDXAnimationBlock	mSpread;
		MDXAnimationBlock	mRange;//0 -- 2*pi
		MDXAnimationBlock	mGravity;
		MDXAnimationBlock	mLifeSpan;
		MDXAnimationBlock	mEmitRate;
		MDXAnimationBlock	mEmitAreaLength;
		MDXAnimationBlock	mEmitAreaWidth;
		MDXAnimationBlock	mGravity2;//?not sure yet
	};
	MDXAnimationBlock		mInfo[10];
};

struct MDXModelParticleEmitter
{
	int32					mID;
	int32					mFlag;
	XMFLOAT3				mPos;
	int16					mBoneID;
	int16					mTextureID;
	HeaderPair32			mZero1;//?
	HeaderPair32			mZero2;

	int16					mBlendType;
	int16					mEmitterType;
	int16					mParticleType;
	int16					mTextureTileRotation;
	int16					mTexCol;
	int16					mTexRow;
	MDXParticleEmitterParam	mParam;
	MDXModelParticleInfo	mParticleInfo;
	MDXAnimationBlock		unknownA;
};

struct MDXModelRibbonEmitter
{
	int32					mID;
	int32					mBone;
	XMFLOAT3				mPos;
	HeaderPair32			mTextuer;
	HeaderPair32			unknownA;
	MDXAnimationBlock		mColor;
	MDXAnimationBlock		mOpacity;
	MDXAnimationBlock		mHeightAbove;
	MDXAnimationBlock		mHeightBelow;
	float					mRes;
	float					mLength;
	float					unknownB;
	int16					unknownC[2];
	MDXAnimationBlock		unknownD[2];
};



struct MDXModelAttachment 
{
	int32					mID;
	int32					mBone;
	XMFLOAT3				mPos;
	MDXAnimationBlock		unknown;
};

//------------------------------------------------------------------------------------------------
struct MDXModelBlockQ//unknown
{
	char		id[4];
	int32		dbid;
	int32		bone;
	XMFLOAT3	pos;
	int16		type;
	int16		seq;
	uint32		nRanges;
	uint32		ofsRanges;
	uint32		nTimes;
	uint32		ofsTimes;
};

#pragma pack(pop)
//class MDXFile
//{
//public:
//	MDXFile(const std::string& path);
//	~MDXFile();
//
//	const MDXModelHeader*		GetHeader()const {return mHeader;}
//	const uint8*				GetBuffer()const {return mMPQFile.getBuffer();}
//private:
//	MPQFile						mMPQFile;
//
//	MDXModelHeader*				mHeader;
//
//};