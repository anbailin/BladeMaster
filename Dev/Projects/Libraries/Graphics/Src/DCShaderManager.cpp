#include "GraphicsPrivate.h"
#include "DCShaderManager.h"

namespace
{
	const u32 kBoneReg = 5;
	const u32 kBoneSize = 4;
	const u32 kRegMaxNum = 256;

	const u32 kBoneAvailableNum = (kRegMaxNum - kBoneReg)/kBoneSize;
}

bool DCShaderManager::DetermineShaderAnimation(u32 _BoneNum)
{
	return _BoneNum<kBoneAvailableNum;
}