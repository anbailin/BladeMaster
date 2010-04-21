#include "DCRenderHeader.h"


namespace
{
	const uint32 kBoneReg = 5;
	const uint32 kBoneSize = 4;
	const uint32 kRegMaxNum = 256;

	const uint32 kBoneAvailableNum = (kRegMaxNum - kBoneReg)/kBoneSize;
}

bool DCShaderManager::DetermineShaderAnimation(uint32 _BoneNum)
{
	return _BoneNum<kBoneAvailableNum;
}