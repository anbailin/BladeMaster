#include "DCRenderHeader.h"

DCMaterial::DCMaterial()
{
	mColor.data = 0xffffffff;//white color;

	mAlphaBlend.SetAlphaBlendingState(kAlphaBlendOn);
	mAlphaBlend.SetDstFunc(kAlphaBlendInverseSourceAlpha);
	mAlphaBlend.SetSrcFunc(kAlphaBlendSourceAlpha);

	mAlphaTest.SetAlphaTestState(kAlphaTestOn);
	mAlphaTest.SetAlphaTestFunc(kAlphaTestGreaterEqual);
	mAlphaTest.SetReference(1);
}