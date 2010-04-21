#pragma once

// ------------------alpha test------------------------------------------------------------------------------------
typedef enum
{
	kAlphaTestOn,
	kAlphaTestOff,
	kNumberOfAlphaTestStates
}	AlphaTestState;

typedef enum
{
	kAlphaTestNever, 
	kAlphaTestLess, 
	kAlphaTestEqual, 
	kAlphaTestLessEqual, 
	kAlphaTestGreater, 
	kAlphaTestNotEqual, 
	kAlphaTestGreaterEqual, 
	kAlphaTestAlways,
	kNumberOfAlphaTestFuncStates
}	AlphaTestFunc;

class DCAlphaTestState
{
public:

	DCAlphaTestState(AlphaTestState _state = kAlphaTestOff,  AlphaTestFunc _func = kAlphaTestGreaterEqual, uint8 _ref = 0):
	  mTestState(_state), mFunc(_func), mRef(_ref)
	  {}

	  AlphaTestState	GetAlphaTestState()const	{ return mTestState;  }
	  void				SetAlphaTestState(AlphaTestState _state) {	mTestState = _state;  }

	  AlphaTestFunc		GetAlphaTestFunc()const		{ return mFunc; }
	  void				SetAlphaTestFunc(AlphaTestFunc _func) { mFunc = _func; }

	  uint8				GetReference()const			{ return mRef;  }
	  void				SetReference(uint8 _ref)    { mRef = _ref;  }

	  bool operator == (const DCAlphaTestState& _state)
	  {
		  return ( mTestState == _state.mTestState ) && ( mFunc == _state.mFunc ) && ( mRef == _state.mRef );
	  }

	  bool operator != (const DCAlphaTestState& _state)
	  {
		  return !(*this == _state);
	  }
private:
	AlphaTestState mTestState;
	AlphaTestFunc  mFunc;
	uint8		   mRef;
};

// ------------------alpha blend------------------------------------------------------------------------------------

typedef enum 
{ 
	kAlphaBlendOn, 
	kAlphaBlendOff,							// Default value
	kNumberOfAlphaBlendStates
}	AlphaBlendState;

typedef enum
{
	kAlphaBlendZero,
	kAlphaBlendOne,
	kAlphaBlendSourceAlpha,					// Source default
	kAlphaBlendInverseSourceAlpha,			// Destination default
	kAlphaBlendSourceColor,
	kAlphaBlendInverseSourceColor,
	kAlphaBlendDestinationColor,
	kAlphaBlendInverseDestinationColor,
	kAlphaBlendDestinationAlpha,
	kAlphaBlendInverseDestinationAlpha,
	kAlphaBlendBothSourceAlpha,
	kAlphaBlendBothInverseSourceAlpha,
	kNumberOfAlphaBlendFuncStates
}	AlphaBlendFunc;

class DCAlphaBlendState
{
public:
	// constructor, destructor
	DCAlphaBlendState(
		AlphaBlendState state = kAlphaBlendOff, 
		AlphaBlendFunc srcFunc = kAlphaBlendSourceAlpha, 
		AlphaBlendFunc dstFunc = kAlphaBlendInverseSourceAlpha ):
		mAlphaBlendingState(state),mSrcFunc(srcFunc),mDstFunc(dstFunc)
		{}

	~DCAlphaBlendState(){}

	void SetAlphaBlendingState( AlphaBlendState state ) 
	{ mAlphaBlendingState = state; }
	AlphaBlendState GetAlphaBlendingState() const
	{ return mAlphaBlendingState; }

	void SetSrcFunc( AlphaBlendFunc srcFunc )
	{ mSrcFunc = srcFunc; }
	AlphaBlendFunc GetSrcFunc() const
	{ return mSrcFunc; }

	void SetDstFunc( AlphaBlendFunc dstFunc )
	{ mDstFunc = dstFunc; } 
	AlphaBlendFunc GetDstFunc() const
	{ return mDstFunc; }

	bool operator==(const DCAlphaBlendState& rhs) const { return mAlphaBlendingState==rhs.GetAlphaBlendingState() && mSrcFunc==rhs.GetSrcFunc() && mDstFunc==rhs.GetDstFunc(); }
	bool operator!=(const DCAlphaBlendState& rhs) const { return !(*this == rhs); }

private:
	AlphaBlendState				mAlphaBlendingState;
	AlphaBlendFunc				mSrcFunc;
	AlphaBlendFunc				mDstFunc;
};