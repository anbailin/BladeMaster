#pragma once
#pragma warning (disable:4201)

struct DCQuater4
{
	union
	{
		struct
		{
			uint8 r,g,b,a;
		};
		struct 
		{
			uint8 x,y,z,w;
		};
		uint8  vData[4];
		uint32 data;
	};

	uint8 operator[] (uint8 _val){return vData[_val];}
};

typedef DCQuater4 DCRGBAColor8;
