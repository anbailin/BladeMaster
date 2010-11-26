#pragma once
#pragma warning (disable:4201)

struct DCQuater4
{
	union
	{
		struct
		{
			u8 r,g,b,a;
		};
		struct 
		{
			u8 x,y,z,w;
		};
		u8  vData[4];
		u32 data;
	};

	u8 operator[] (u8 _val){return vData[_val];}
};

typedef DCQuater4 DCRGBAColor8;
