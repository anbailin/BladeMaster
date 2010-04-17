
//#include <systemm.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "DCUtils.h"



D3DXVECTOR3 FixCoordSystem(const D3DXVECTOR3 v)
{
	return D3DXVECTOR3(v.x, v.z, -v.y);
}

D3DXVECTOR3 FixCoordSystem2(const D3DXVECTOR3 v)
{
	return D3DXVECTOR3(v.x, v.z, v.y);
}

D3DXQUATERNION FixCoordSystemQuat(D3DXQUATERNION v)
{
	return D3DXQUATERNION(-v.x, -v.z, v.y, v.w);
}

void ColorAssign(D3DCOLORVALUE& outColor,const D3DXVECTOR4& inColor)
{
	outColor.r=inColor.x;
	outColor.g=inColor.y;
	outColor.b=inColor.z;
	outColor.a=inColor.w;
}

void V4ToV3Assign(D3DXVECTOR3& vOut, const D3DXVECTOR4& vIn)
{	
	if(vIn.w!=0){
		float rw=1.0f/vIn.w;
		vOut.x=vIn.x*rw;
		vOut.y=vIn.y*rw;
		vOut.z=vIn.z*rw;
	}else{
		vOut.x=vIn.x;
		vOut.y=vIn.y;
		vOut.z=vIn.z;
	}
}