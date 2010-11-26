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

typedef HeaderPair<u32> HeaderPair32;
typedef HeaderPair<u16> HeaderPair16;
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
	u8 version[4];
	u32 nameLength;
	u32 nameOfs;
	u32 GlobalModelFlags; // 1: tilt x, 2: tilt y, 4:, 8: add another field in header, 16: ; (no other flags as of 3.1.1);

	HeaderPair32	mAnimDuration;	//nGlobalSequences 
	HeaderPair32	mAnim;			//nAnimations
	HeaderPair32    mAnimLookup;
	HeaderPair32	mBone;
	HeaderPair32	mKeyBoneLookup;//BonesAndLookups

	HeaderPair32	mVertex;
	u32 nViews; // GeometryAndRendering	

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
	u32 nEvents; // 
	u32 ofsEvents; // Used for playing sounds when dying and a lot else.
	HeaderPair32	mLight;
	HeaderPair32	mCamera;
	HeaderPair32    mCameraLookup; // Miscellaneous
	
	HeaderPair32	mRibbonEmitter;
	HeaderPair32	mParticleEmitter;
};

//---------------animation--------------------------------------------
struct MDXAnimSequence
{
	u32		mAnimID;
	u32		mTimeStart;
	u32		mTimeEnd;

	float		mMoveSpeed;

	u32		mLoopType;
	u32		mFlag;

	u32		unknownA;
	u32		unknownB;

	u32		mPlaySpeed;
	XMFLOAT3	mBoundingBoxA;
	XMFLOAT3	mBoundingBoxB;

	float		mRadius;
	u32		unknownC;
};

struct MDXAnimSequenceWLK
{
	s16		mAnimID; // AnimationDataDB.ID
	s16		mSubAnimID;
	u32		mLength;
	float		mMoveSpeed;

	u32		mFlags;
	u16		mProbability; // This is used to determine how often the animation is played. For all animations of the same type, this adds up to 0x7FFF (32767).
	u16		unused;
	u32		d1;
	u32		d2;
	u32		mPlaySpeed;  // note: this can't be play speed because it's 0 for some models

	XMFLOAT3	boxA, boxB; // Minimum Extent, Maximum Extend
	float		mRadius;  // Bounds Radius

	s16		mNextAnimation;
	s16		mIndex;
};

//AnimationBlock
struct MDXAnimationBlock
{
	s16			mInterpolation;
	s16			mSequenceID;
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
	s32				mAnimID;
	s32				mFlag;
	s16				mParent;
	s16				mGeoID;
	s32				unknown; // new int added to the bone definitions.  Added in WoW 2.0
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
	u8		weights[4];
	u8		bones[4];
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
	u32 nProps;
	u32 ofsProps; // s32, additional vtx properties
	HeaderPair32 mSub;//[ofsSub], geometry ModelGeoset, materials/renderops/submeshes
	HeaderPair32 mTex;// ModelTexUnit, material properties/textures
	s32 lod;				 // LOD bias?
};

struct MDXGeometry
{
	u32				mID;	
	
	u16				mVertexStart;
	u16				mVertexCount;

	u16				mIndexStart;
	u16				mIndexCount;
	u16				nBones;		// number of bone indices, Number of elements in the bone lookup table.
	u16				StartBones;		// ? always 1 to 4, Starting index in the bone lookup table.
	u16				d5;		// ?
	u16				rootBone;		// root bone?
	XMFLOAT3			BoundingBox[2];
	float				radius;
};


struct MDXMaterial
{
	u16 flags;		// Usually 16 for static textures, and 0 for animated textures.
	u16 shading;		// If set to 0x8000: shaders. Used in skyboxes to ditch the need for depth buffering. See below.
	u16 op;			// Material this texture is part of (index into mat), the geometry index used by this material
	u16 op2;			// Always same as above?
	s16 colorIndex;	// A Color out of the Colors-Block or -1 if none.
	u16 flagsIndex;	// RenderFlags (index into render flags, TexFlags)
	u16 texunit;		// Index into the texture unit lookup table.
	u16 mode;		// See below.
	u16 textureid;	// Index into Texture lookup table
	u16 texunit2;	// copy of texture unit value?
	u16 transid;		// Index into transparency lookup table.
	u16 texanimid;	// Index into uvanimation lookup table. 
};

//-------------------little definitions-----------------------------------------------------------------
//the info from http://wowdev.org/wiki/index.php/M2
//nRenderFlags (u16, u16) pairs starting at ofsRenderFlags 
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
	u16				mFlag;
	u16				mBlend;
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
	u32				mType;	//EMDXTexType
	u32				mFlag;
	u32				mNameLength;
	u32				mNameOffset;
};

//-------------------------------------------------------------------------------------------
struct MDXModelLightDef
{
	u16				mType;
	u16				mBone;
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
	s32				mID;
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

	u32				mColorStart;
	u32				mColorMid;
	u32				mColorEnd;

	float				mSizeStart;
	float				mSizeMid;
	float				mSizeEnd;

	s16				mTileTexIndex[10];
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
	s32					mID;
	s32					mFlag;
	XMFLOAT3				mPos;
	s16					mBoneID;
	s16					mTextureID;
	HeaderPair32			mZero1;//?
	HeaderPair32			mZero2;

	s16					mBlendType;
	s16					mEmitterType;
	s16					mParticleType;
	s16					mTextureTileRotation;
	s16					mTexCol;
	s16					mTexRow;
	MDXParticleEmitterParam	mParam;
	MDXModelParticleInfo	mParticleInfo;
	MDXAnimationBlock		unknownA;
};

struct MDXModelRibbonEmitter
{
	s32					mID;
	s32					mBone;
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
	s16					unknownC[2];
	MDXAnimationBlock		unknownD[2];
};



struct MDXModelAttachment 
{
	s32					mID;
	s32					mBone;
	XMFLOAT3				mPos;
	MDXAnimationBlock		unknown;
};

//------------------------------------------------------------------------------------------------
struct MDXModelBlockQ//unknown
{
	char		id[4];
	s32		dbid;
	s32		bone;
	XMFLOAT3	pos;
	s16		type;
	s16		seq;
	u32		nRanges;
	u32		ofsRanges;
	u32		nTimes;
	u32		ofsTimes;
};

#pragma pack(pop)
//class MDXFile
//{
//public:
//	MDXFile(const std::string& path);
//	~MDXFile();
//
//	const MDXModelHeader*		GetHeader()const {return mHeader;}
//	const u8*				GetBuffer()const {return mMPQFile.getBuffer();}
//private:
//	MPQFile						mMPQFile;
//
//	MDXModelHeader*				mHeader;
//
//};