#pragma once

#include <vector>
#include <Utility>
#include "Files/MDX.h"
//#include "DCMathHeader.h"
//implementation of the data MDXAnimationBlock;
typedef std::pair<size_t, size_t> AnimRange; 

enum InterpolationType
{
	InterpolationNone,
	InterpolationLinear,
	InterpolationHermite,
	InterpolationBezier,
};


namespace
{
	template<class Type>
	Type  AnimLinearLerp(Type& _first,Type& _second,float ratio)
	{		
		return Lerp(ratio,_first,_second);
	}
}

struct PACK_QUATERNION 
{  
	int16 x,y,z,w;  
}; 

class Quat16ToQuat32 {
public:
	static const XMQuaternion conv(const PACK_QUATERNION t)
	{
		return XMQuaternion(
			float(t.x < 0? t.x + 32768 : t.x - 32767)/ 32767.0f, 
			float(t.y < 0? t.y + 32768 : t.y - 32767)/ 32767.0f,
			float(t.z < 0? t.z + 32768 : t.z - 32767)/ 32767.0f,
			float(t.w < 0? t.w + 32768 : t.w - 32767)/ 32767.0f);
	}
};

template <class T>
class Identity {
public:
	static const T& conv(const T& t)
	{
		return t;
	}
};

// Convert opacity values stored as shorts to floating point
// I wonder why Blizzard decided to save 2 bytes by doing this
class ShortToFloat {
public:
	static const float conv(const short t)
	{
		return t/32767.0f;
	}
};

#define	MAX_ANIMATED	500

template<class Type, class D=Type, class Conv=Identity<Type>>
class ANIM_DLL AnimData
{
public:
	bool GetIdentity(){return mIdentity;	}
	bool Use(uint32 anim)
	{
		if(mSeqIndex>-1)
		{
			anim = 0;
		}

		return mvData[anim].size()>0;
	}

	AnimData(){mIdentity = false;}

	AnimData(const MDXAnimationBlock& _block, const MPQFile& _file, const int32* _GlobalSequence);

	void Init(const MDXAnimationBlock& _block, MPQFile& _file, const int32* _GlobalSequence, MPQFile* animfiles)
	{
		mGlobalSequence = _GlobalSequence;
		mType = (InterpolationType)_block.mInterpolation;
		mSeqIndex = _block.mSequenceID;

		assert(mSeqIndex>=-1);

		//times
		assert(_block.mTimes.number == _block.mKeys.number);
		uint32 tNum = _block.mTimes.number;
		mSizes = _block.mTimes.number;

		for(uint32 i=0; i<tNum; i++)
		{
			AnimationBlockHeader* animHeader = (AnimationBlockHeader*)(_file.getBuffer()+_block.mTimes.offset+i*sizeof(AnimationBlockHeader));

			uint32 *ptimes;
			if (animfiles[i].getSize() > animHeader->Entries.offset)
				ptimes = (uint32*)(animfiles[i].getBuffer() + animHeader->Entries.offset);
			else if (_file.getSize() > animHeader->Entries.offset)
				ptimes = (uint32*)(_file.getBuffer() + animHeader->Entries.offset);
			else
				continue;
			for (size_t entryIdx=0; entryIdx < animHeader->Entries.number; entryIdx++)
			{
				mvTime[i].push_back(ptimes[entryIdx]);
			}
		}

// 		uint32* ptime = (uint32*)(_file.getBuffer()+_block.mTimes.offset);
// 		mvTime.resize(tNum);
// 		for(uint32 i=0; i<tNum; i++)
// 		{
// 			mvTime[i] = ptime[i];
// 		}

		//key frame data
		for(uint32 keyIdx=0; keyIdx<_block.mKeys.number; keyIdx++)
		{
			AnimationBlockHeader* keyHeader = (AnimationBlockHeader*)(_file.getBuffer()+_block.mKeys.offset+keyIdx*sizeof(AnimationBlockHeader));
			
			D* pkey = NULL;

			if (animfiles[keyIdx].getSize() > keyHeader->Entries.offset)
			{
				pkey = (D*)(animfiles[keyIdx].getBuffer() + keyHeader->Entries.offset);
			}
			else if (_file.getSize() > keyHeader->Entries.offset)
			{
				pkey = (D*)(_file.getBuffer() + keyHeader->Entries.offset);
			}
			else
			{
				continue;
			}

			//Type* pkey = (Type*)(_file.getBuffer()+keyHeader->Entries.offset);
			switch(mType)
			{
			case InterpolationNone:
			case InterpolationLinear:
				for(uint32 entryIdx=0; entryIdx<keyHeader->Entries.number; entryIdx++)
				{
					mvData[keyIdx].push_back(Conv::conv(pkey[entryIdx]));
				}
				break;
			case InterpolationHermite:
			case InterpolationBezier:
				{
					for(uint32 entryIdx=0; entryIdx<keyHeader->Entries.number; entryIdx++)
					{
						mvData[keyIdx].push_back(Conv::conv(pkey[entryIdx*3]));
						mIn[keyIdx].push_back(Conv::conv(pkey[entryIdx*3+1]));
						mOut[keyIdx].push_back(Conv::conv(pkey[entryIdx*3+2]));
					}
					break;
				}
			}
		}

		//assert((Type*)(_file.getBuffer()+_block.mKeys.number)!=NULL);
		//Type* pkey = (Type*)(_file.getBuffer() + _block.mKeys.offset);
		//uint32 keyNum = _block.mKeys.number;
		//switch(mType)
		//{
		//case InterpolationNone:
		//case InterpolationLinear:
		//	mvData.resize(keyNum);
		//	for(uint32 i=0;i<keyNum;i++)
		//	{
		//		mvData[i] = pkey[i];
		//	}
		//	break;
		//case InterpolationHermite:
		//	for(uint32 i=0;i<_block.mKeys.number;i++)
		//	{
		//		mvData.push_back(pkey[i*3]);
		//		mIn.push_back(pkey[i*3+1]);
		//		mOut.push_back(pkey[i*3+2]);
		//	}
		//	break;
		//}
	}



	Type GetValue(uint32 _anim, uint32 _time,uint32 _GlobalTime)
	{
		if (mSeqIndex>-1) 
		{
			// TODO
			if (mGlobalSequence[mSeqIndex]==0) 
				_time = 0;
			else 
				_time = _GlobalTime % mGlobalSequence[mSeqIndex];
			_anim = 0;
		}

		if(mvData[_anim].size()>1 &&mvTime[_anim].size()>1)
		{
			size_t t1, t2;
			size_t pos=0;
			int max_time = mvTime[_anim][mvTime[_anim].size()-1];
			if (max_time > 0)
				_time %= max_time; // I think this might not be necessary?
			for (size_t i=0; i<mvTime[_anim].size()-1; i++)
			{
				if (_time >= mvTime[_anim][i] && _time < mvTime[_anim][i+1]) {
					pos = i;
					break;
				}
			}
			t1 = mvTime[_anim][pos];
			t2 = mvTime[_anim][pos+1];
			float r = (_time-t1)/(float)(t2-t1);

			if (mType == InterpolationNone) 
				return mvData[_anim][pos];
			else if (mType == InterpolationLinear) 
				return AnimLinearLerp<Type>(mvData[_anim][pos],mvData[_anim][pos+1],r);
			else if (mType==InterpolationHermite){
				// INTERPOLATION_HERMITE is only used in cameras afaik?
				//return interpolateHermite<T>(r,data[_anim][pos],data[_anim][pos+1],in[_anim][pos],out[_anim][pos]);
				return Type();
			}
			else if (mType==InterpolationBezier)
			{
				//Is this used ingame or only by custom models?
				//return interpolateBezier<T>(r,data[_anim][pos],data[_anim][pos+1],in[_anim][pos],out[_anim][pos]);
				return Type();
			}
			else 
			{
				//this shouldn't appear!
				//return data[_anim][pos];
				return Type();
			}

		} 
		else 
		{
			// default value
			if (mvData[_anim].size() == 0)
				return Type();
			else
				return mvData[_anim][0];
		}
	}
public:
	InterpolationType			mType;
	int32						mSeqIndex;
	const int32*				mGlobalSequence;
	bool						mIdentity;
	uint32						mSizes;

	std::vector<AnimRange>		mvRange;
	std::vector<uint32>			mvTime[MAX_ANIMATED];
	std::vector<Type>			mvData[MAX_ANIMATED];
	std::vector<Type>			mIn[MAX_ANIMATED];
	std::vector<Type>			mOut[MAX_ANIMATED];
};
