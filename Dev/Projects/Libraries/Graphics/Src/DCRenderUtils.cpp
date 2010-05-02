#include "GraphicsPrivate.h"

//void ColorAssign(D3DCOLORVALUE& outColor,const D3DXVECTOR4& inColor)
//{
//	outColor.r=inColor.x;
//	outColor.g=inColor.y;
//	outColor.b=inColor.z;
//	outColor.a=inColor.w;
//}
//
//void V4ToV3Assign(D3DXVECTOR3& vOut, const D3DXVECTOR4& vIn)
//{	
//	if(vIn.w!=0){
//		float rw=1.0f/vIn.w;
//		vOut.x=vIn.x*rw;
//		vOut.y=vIn.y*rw;
//		vOut.z=vIn.z*rw;
//	}else{
//		vOut.x=vIn.x;
//		vOut.y=vIn.y;
//		vOut.z=vIn.z;
//	}
//}

void fixname(char *name, size_t len)
{
	for (size_t i=0; i<len; i++) {
		if (i>0 && name[i]>='A' && name[i]<='Z' && isalpha(name[i-1])) {
			name[i] |= 0x20;
		} else if ((i==0 || !isalpha(name[i-1])) && name[i]>='a' && name[i]<='z') {
			name[i] &= ~0x20;
		}
	}
}

void fixname(std::string &name)
{
	for (size_t i=0; i<name.length(); i++) {
		if (i>0 && name[i]>='A' && name[i]<='Z' && isalpha(name[i-1])) {
			name[i] |= 0x20;
		} else if ((i==0 || !isalpha(name[i-1])) && name[i]>='a' && name[i]<='z') {
			name[i] &= ~0x20;
		}
	}
}