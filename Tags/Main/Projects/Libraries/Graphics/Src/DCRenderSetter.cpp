
#include "Graphics.h"

DCRenderSetter* DCRenderSetter::mInstance = NULL;

void DCRenderSetter::Init()
{
	mInstance = new DCRenderSetter;

	mInstance->mAlphaBlendCache.SetAlphaBlendingState(kNumberOfAlphaBlendStates);
	mInstance->mAlphaBlendCache.SetDstFunc(kNumberOfAlphaBlendFuncStates);
	mInstance->mAlphaBlendCache.SetSrcFunc(kNumberOfAlphaBlendFuncStates);
	
	mInstance->mAlphaTestCache.SetAlphaTestFunc(kNumberOfAlphaTestFuncStates);
	mInstance->mAlphaTestCache.SetAlphaTestState(kNumberOfAlphaTestStates);
	mInstance->mAlphaTestCache.SetReference(0xff);	
}


void DCRenderSetter::ApplyAlphaTest(DCAlphaTestState _state)
{
	if(_state == mAlphaTestCache)
		return;
	if(_state.GetAlphaTestState() != mAlphaTestCache.GetAlphaTestState())
	{
		switch(_state.GetAlphaTestState())
		{
		case kAlphaTestOn:
			DEVICEPTR->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE); 
			break;
		case kAlphaTestOff:
			DEVICEPTR->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE); 
			break;
		default:
			assert(0);//error part;
		}
		mAlphaTestCache.SetAlphaTestState(_state.GetAlphaTestState());
	}

	if(_state.GetAlphaTestFunc() != mAlphaTestCache.GetAlphaTestFunc())
	{
		switch(_state.GetAlphaTestFunc())
		{
		case kAlphaTestNever:
			DEVICEPTR->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NEVER);
			break;
		case kAlphaTestLess:
			DEVICEPTR->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_LESS);
			break;
		case kAlphaTestEqual:
			DEVICEPTR->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_EQUAL );
			break;
		case kAlphaTestLessEqual:
			DEVICEPTR->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_LESSEQUAL );
			break;	
		case kAlphaTestGreater:
			DEVICEPTR->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER );
			break;	
		case kAlphaTestNotEqual:
			DEVICEPTR->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_NOTEQUAL );
			break;	
		case kAlphaTestGreaterEqual:
			DEVICEPTR->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL );
			break;
		case kAlphaTestAlways:
			DEVICEPTR->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS );
			break;
		default:
			assert(0);//error part;
		}
		mAlphaTestCache.SetAlphaTestFunc(_state.GetAlphaTestFunc());
	}

	if(_state.GetReference() != mAlphaTestCache.GetReference())
	{
		DEVICEPTR->SetRenderState(D3DRS_ALPHAREF, (DWORD)(_state.GetReference()));
		mAlphaTestCache.SetReference(_state.GetReference());
	}
}

void DCRenderSetter::ApplyAlphaBlend(DCAlphaBlendState _state)
{
	if(_state == mAlphaBlendCache)
		return;

	if(_state.GetAlphaBlendingState() != mAlphaBlendCache.GetAlphaBlendingState())
	{
		switch(_state.GetAlphaBlendingState())
		{
		case kAlphaBlendOn:
			DEVICEPTR->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
			break;
		case kAlphaBlendOff:
			DEVICEPTR->SetRenderState( D3DRS_ALPHABLENDENABLE, FALSE );
			break;
		default:
			assert(0);//error situation
		}

		mAlphaBlendCache.SetAlphaBlendingState(_state.GetAlphaBlendingState());
	}

	if(_state.GetSrcFunc() != mAlphaBlendCache.GetSrcFunc())
	{
		switch(_state.GetSrcFunc())
		{
		case kAlphaBlendZero:
			DEVICEPTR->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ZERO);
			break;
		case kAlphaBlendOne:
			DEVICEPTR->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_ONE);
			break;
		case kAlphaBlendSourceAlpha:				// Source default
			DEVICEPTR->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			break;
		case kAlphaBlendInverseSourceAlpha:			// Destination default
			DEVICEPTR->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_INVSRCALPHA );
			break;
		case kAlphaBlendSourceColor:
			DEVICEPTR->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR );
			break;
		case kAlphaBlendInverseSourceColor:
			DEVICEPTR->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_INVSRCCOLOR );
			break;
		case kAlphaBlendDestinationColor:
			DEVICEPTR->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_DESTCOLOR );
			break;
		case kAlphaBlendInverseDestinationColor:
			DEVICEPTR->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR );
			break;
		case kAlphaBlendDestinationAlpha:
			DEVICEPTR->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_DESTALPHA );
			break;
		case kAlphaBlendInverseDestinationAlpha:
			DEVICEPTR->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_INVDESTALPHA );
			break;
		//case kAlphaBlendBothSourceAlpha:
		//	DEVICEPTR->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_BOTHSRCALPHA );
		//	break;
		//case kAlphaBlendBothInverseSourceAlpha:
		//	DEVICEPTR->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_BOTHINVSRCALPHA );
		//	break;
		default:assert(0);
		}

		mAlphaBlendCache.SetSrcFunc(_state.GetSrcFunc());
	}

	if( _state.GetDstFunc() != mAlphaBlendCache.GetDstFunc())
	{
		switch(_state.GetDstFunc())
		{
		case kAlphaBlendZero:
			DEVICEPTR->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ZERO);
			break;
		case kAlphaBlendOne:
			DEVICEPTR->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case kAlphaBlendSourceAlpha:				// Source default
			DEVICEPTR->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_SRCALPHA);
			break;
		case kAlphaBlendInverseSourceAlpha:			// Destination default
			DEVICEPTR->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
			break;
		case kAlphaBlendSourceColor:
			DEVICEPTR->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR );
			break;
		case kAlphaBlendInverseSourceColor:
			DEVICEPTR->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCCOLOR );
			break;
		case kAlphaBlendDestinationColor:
			DEVICEPTR->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_DESTCOLOR );
			break;
		case kAlphaBlendInverseDestinationColor:
			DEVICEPTR->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVDESTCOLOR );
			break;
		case kAlphaBlendDestinationAlpha:
			DEVICEPTR->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_DESTALPHA );
			break;
		case kAlphaBlendInverseDestinationAlpha:
			DEVICEPTR->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVDESTALPHA );
			break;
		//case kAlphaBlendBothSourceAlpha:
		//	DEVICEPTR->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_BOTHSRCALPHA );
		//	break;
		//case kAlphaBlendBothInverseSourceAlpha:
		//	DEVICEPTR->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_BOTHINVSRCALPHA );
		//	break;
		default:assert(0);
		}

		mAlphaBlendCache.SetDstFunc(_state.GetDstFunc());
	}

}