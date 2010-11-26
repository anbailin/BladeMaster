#ifndef DCRENDERTYPE_H
#define DCRENDERTYPE_H


//--------------------------------------------------------------------------------------------
enum DCVertexType
{
	VertexTypePosWNTC,
	VertexTypePosWNTC2,
	VertexTypePosNorTex,
    VertexTypePosColor,
    VertexTypePosNorColor,
	VertexTypeCount
};

enum TexWrapState
{
	kTexWrapUWrapV,
	TexWrapCount
};

enum TexFilterState
{
	kTexFilterLinear,
	TexFilterCount
};

//--------------------------------------------------------------------------------------------
u32 GetTypeSize(DCVertexType arg);

#endif