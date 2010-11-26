#include "GraphicsPrivate.h"

u32 GetTypeSize(DCVertexType arg)
{
	switch(arg)
	{
	case VertexTypePosWNTC: return sizeof(DCVertPosWNTC);
	case VertexTypePosWNTC2: return sizeof(DCVertPosWNTC2);
	case VertexTypePosNorTex: return sizeof(DCVertPosNorTex);
    case VertexTypePosColor: return sizeof(DCVertPosColor);
	default:return 0;
	}
}