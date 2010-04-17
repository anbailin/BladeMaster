//#include <Utility>
//#include "MDX.h"
//#include "DCAnimData.h"

//#include "DCAnimHeader.h"




//namespace
//{
//	template<class Type>
//	Type  AnimLinearLerp(const Type& _first,const Type& _second,float ratio)
//	{
//		return _first*(1-ratio) + _second*ratio;
//	}
//
//	DCQuaternion	AnimLinearLerp(const DCQuaternion& _first, const DCQuaternion& _second, float ratio)
//	{
//		DCQuaternion result;
//		Slerp(_first,_second,ratio,result);
//		return result;
//	}
//}
//
//template<class Type>
//AnimData<Type>::AnimData(const MDXAnimationBlock& _block, const MPQFile& _file,const int32* _GlobalSequence)
//{
//	Init(_block,_file, _GlobalSequence);
//}
//
//template<class Type>
//void AnimData<Type>::Init(const MDXAnimationBlock& _block, const MPQFile& _file,const int32* _GlobalSequence)
//{
//	mGlobalSequence = _GlobalSequence;
//	mType = (InterpolationType)_block.mInterpolation;
//	mSeqIndex = _block.mSequenceID;
//	assert(mSeqIndex>=-1);
//
//	//ranges
//	if(_block.mRange.number>0)
//	{
//		uint32* prange = (uint32*)(_file.getBuffer() + _block.mRange.offset);
//		uint32 count = _block.mRange.number*2;
//		for(uint32 i=0;i<cout;)
//		{
//			AnimRange r;
//			r.first = prange[i++];
//			r.second = prange[i++];
//			mvRange.push_back(r);
//		}
//	}else if(mType!=InterpolationNone && mSeqIndex == -1)
//	{
//		AnimRange r;
//		r.first = 0;
//		r.second = _block.mKey.number-1;
//	}else
//	{
//		assert(0);//something out of assumption;
//	}
//
//	//times
//	assert(_block.mTime.number == _block.mKey.number);
//	uint32* ptime = (uint32*)(_file.getBuffer()+_block.mTime.offset);
//	mvTime.reserve(_block.mTime.number);
//	for(uint32 i=0;i<_block.mTime.number;i++)
//		mvTime.push_back(ptime[i]);
//
//	assert((Type*)(_file.getBuffer()+_block.mKey.number)!=NULL);
//	Type* pkey = (Type*)(_file.getBuffer() + _block.mKey.offset);
//
//	switch(mType)
//	{
//	case InterpolationNone:
//	case InterpolationLinear:
//		for(uint32 i=0;i<_block.mKey.number;i++)
//		{
//			mvData.push_back(pkey[i]);
//		}
//		break;
//	case InterpolationHermite:
//		for(uint32 i=0;i<_block.mKey.number;i++)
//		{
//			mvData.push_back(pkey[i*3]);
//			mIn.push_back(pkey[i*3+1]);
//			mOut.push_back(pkey[i*3+2]);
//		}
//		break;
//	}
//}//to do part, consider the situation with interpolationNone;
//
//template<class Type>
//Type AnimData<Type>::GetValue(uint32 _anim, uint32 _time,uint32 _GlobalTime)
//{	
//	if(mType == InterpolationNone)
//	{
//		return mvData.size()==0? 0:mvData[0];
//	}
//
//	assert(mvData.size()>0);
//	AnimRange range;
//	if(mSeqIndex!=-1)	//sequence available, use sequnce info instead of range info
//	{
//		_time = (mGlobalSequence[mSeqIndex]==0)?0:_GlobalTime%mGlobalSequence[mSeqIndex];
//		range.first = 0;
//		range.second = mvData.size() - 1;
//	}else				//use Range info 
//	{
//		range = mvRange[_anim];
//	}
//
//	if(range.first==range.second)
//		return mvData[range.first];
//
//
//	uint32 pos = 0;
//	for(uint32 i=range.first;i<range.second;i++)
//	{
//		if(_time>=mvTime[i] && _time<mvTime[i+1])
//		{
//			pos = i;
//			break;
//		}
//	}
//
//	float ratio = (_time - mvTime[range.first])/(mvTime[range.second] - mvTime[range.first]);
//
//	if(mType == InterpolationLinear)
//		return AnimLinearLerp<Type>(ratio, mvData[pos], mvData[pos+1]);
//	else//not consider hermite interpolation yet
//	{
//		assert(0);
//		return 0;
//	}	
//}