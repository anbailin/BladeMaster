
#pragma once

enum ShaderRegisterNdx
{
	SR_LocalToWorld = 0,
	SR_MaxNum
};

class RENDER_DLL DCShaderManager
{
public:
	static bool DetermineShaderAnimation(uint32 _BoneNum);
};