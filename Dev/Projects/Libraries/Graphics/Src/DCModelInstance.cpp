#include "Graphics.h"

//void DCModelInstance::Init(const DCModelPtr &_model, const WMOMODDChunk &chunk)
//{
//	DCQuaternion quat(chunk.mAxis,chunk.mAngle);
//	//mTranslator.SetRotate(quat);
//	mTranslator.SetTranslation(chunk.mTranslation);
//	mTranslator.SetScale(chunk.mScale);
//
//	mModelPtr = _model;
//}
//
//void DCModelInstance::Init(const DCModelPtr &_model, const ADTMDDFChunk &chunk)
//{
//	DCMatrix33 mat;
//	mat.Rotation(chunk.mOrientation);
//
//	DCTranslator translator;
//	float scale = chunk.mScale/1024.0f;
//	translator.SetScale(scale);
//	translator.SetTranslation(chunk.mTranslation);
//	translator.SetRotate(mat);
//
//	mModelPtr = _model;
//}