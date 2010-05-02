#include "EnginePrivate.h"

//-------------------------------------------------------------------------
//--------------Type and Const---------------------------------------------
//-------------------------------------------------------------------------

typedef std::vector<DCVertPosWNTC>	VertVector;
typedef std::vector<uint16>			IndexVector;

namespace
{
	void ByteAssign(uint32& v0,const uint8* v1)
	{
		v0 = v1[0]<<24 | v1[1]<<16 | v1[2]<<8 | v1[3];
	}

	const char* texturePosName = ".blp";
}

//-------------------------------------------------------------------------
//--------------FunctionImpl-----------------------------------------------
//-------------------------------------------------------------------------

BM_SINGLETON_DEFINE(DCWOWLoader);


void DCWOWLoader::Init()
{
	mCreatureDisplay = new CreatureDisplayData;
	mCreatureModel = new CreatureModelData;
}

//todo_safe:when fail, release the resource
DCModel* DCWOWLoader::LoadModel(DCFilePath& _path, DCAnimationManager*& animMgr)
{
	int32 ReplacementId[32];
	int32 ReplacementRecord[32];
	uint32 replaceTexIndex = 0;
	for(uint32 i=0;i<32;i++)
	{
		ReplacementId[i] = ReplacementRecord[i] = -1;
	}

	DCModel* result;
	const std::string& _filename = _path.GetWholeName();
	char tempname[256];
	strcpy_s(tempname, 256, _filename.c_str());

	if (tempname[_filename.length()-1] != '2') 
	{
		tempname[_filename.length()-2] = '2';
		tempname[_filename.length()-1] = 0;
	}

	MPQFile mpq(tempname);

	//headers
	MDXModelHeader header;
	mpq.read(&header,0,sizeof(MDXModelHeader));

	//decide if gpu skinning-----------------------------------------------
	bool bShaderAnim = DCShaderManager::DetermineShaderAnimation(header.mBone.number);	
	result = bShaderAnim? new DCModel : new DCModelSys;

	//init the vertex buffer-----------------------------------------------
	uint32 vtxCount = header.mVertex.number;
	DCVertPosWNTC* orignal = (DCVertPosWNTC*)(mpq.getBuffer() + header.mVertex.offset);
	result->InitVertexBuffer(orignal,VertexTypePosWNTC,vtxCount);

	//Texture--------------------------------------------------------------
	const uint32 texCount = header.mTexture.number;
	MDXModelTextureDef* texs = (MDXModelTextureDef*)(mpq.getBuffer() + header.mTexture.offset);
	result->SetTextureTableSize(texCount);

	std::vector<int32> texDBCRecord(texCount);
	for(uint32 i=0;i<texCount;i++)
	{
		texDBCRecord[i] = -1;
	}
	
	for(uint32 i=0;i<texCount;i++)
	{
		char texname[256];
	
		if(texs[i].mType == TEXTURE_FILENAME)
		{
			strcpy_s(texname, texs[i].mNameLength, (const char*)(mpq.getBuffer() + texs[i].mNameOffset));
			texname[texs[i].mNameLength] = 0;

		}		
		else
		{
			DBCFile::Record modelRec = mCreatureModel->GetByFileName(_filename);
			uint32 modelID = modelRec.GetUInt(CreatureModelData::sModelID);
			DBCFile::Record displayRec = mCreatureDisplay->GetByModelID(modelID);
			const char* replaceTexStr = displayRec.GetString(CreatureDisplayData::sSkin1 + replaceTexIndex);
			char texname2[256];
			strcpy_s(texname2,256,_path.GetPath().c_str());
			strcat_s(texname2,256,replaceTexStr);
			strcat_s(texname2,256,texturePosName);
			strcpy_s(texname,256,texname2);
			ReplacementId[replaceTexIndex] = i;
			ReplacementRecord[i] = texs[i].mType - 11;
			replaceTexIndex++;			
		}

		std::string path(texname);

		DCTexturePtr texptr = DCWOWLoader::LoadTexture(path);

		result->SetTexture(texptr,i);
	}

	//sub models-----------------------------------------------------------
	assert(header.nViews>0);
	const std::string fileName = _path.GetWholeName();
	std::string lodName = fileName.substr(0,fileName.length()-4);
	lodName.append("00.skin");

	MPQFile lodMPQFile(lodName.c_str());
	MDXModelLOD* modelLOD = (MDXModelLOD*)lodMPQFile.getBuffer();

	//the prt will be deleted in the model class
	DCSubModel* subModels = new DCSubModel;

	//indices--------------------------------------------------------------
	const uint16* ndxTable = (const uint16*)(lodMPQFile.getBuffer()+modelLOD->mIdxTable.offset);
	const uint16* ndxLookup = (const uint16*)(lodMPQFile.getBuffer()+modelLOD->mIdxLookup.offset);
	const uint32& ndxNum = modelLOD->mIdxLookup.number;
	
	IndexVector ndxBuffer(ndxNum);
	for(uint32 i=0; i<ndxNum; i++)
	{
		ndxBuffer[i] = ndxTable[ndxLookup[i]];
	}

	subModels->InitIndexBuffer(&ndxBuffer[0],ndxNum);

	//meshes---------------------------------------------------------------
	const MDXGeometry *geoData = (MDXGeometry*)(lodMPQFile.getBuffer() + modelLOD->mSub.offset);
	const uint32& geoNum = modelLOD->mSub.number;
	subModels->SetGeometryTableSize(geoNum);
	for(uint32 i_geo=0;i_geo<geoNum;i_geo++)
	{
		DCGeometryPtr geometryptr(new DCGeometry);
		geometryptr->Init(geoData[i_geo]);
		subModels->SetGeometry(geometryptr,i_geo);
	}

	//material-------------------------------------------------------------
	const uint32& materialNum = modelLOD->mTex.number;
	subModels->SetMaterialNum(materialNum);

	const MDXMaterial* materials = (MDXMaterial*)(lodMPQFile.getBuffer()+modelLOD->mTex.offset);

	const uint16* texLookupTable = (uint16*)(mpq.getBuffer() + header.mTexLookup.offset);
	for(uint32 i_mat =0; i_mat<materialNum; i_mat++)
	{
		DCMaterialPtr materialPtr(new DCMaterial);
		materialPtr->SetGeometryPtr(subModels->GetGeometry(materials[i_mat].op));
		uint32 tid = materials[i_mat].textureid;
		uint16 lookup = texLookupTable[tid];
		uint32 texID;
		if(ReplacementRecord[lookup]!=-1)
		{
			texID = ReplacementId[ReplacementRecord[lookup]];
		}
		else
		{
			texID = lookup;
		}

		//texID = 2;
		Clamp<uint32>(texID,0,2);
		materialPtr->SetTexturePtr(result->GetTexture(texID));
		subModels->SetMaterial(materialPtr,i_mat);
	}

	result->SetSubModel(subModels,1);

	//animations-----------------------------------------------------------
	const MDXAnimSequenceWLK* seqWLK = (MDXAnimSequenceWLK*)(mpq.getBuffer() + header.mAnim.offset);
	const uint32 seqNum = header.mAnim.number;

	MPQFile* animFiles = new MPQFile[seqNum];	
	for(uint32 i=0; i<header.mAnim.number; i++)
	{
		char animFileName[256];
		sprintf_s(animFileName, sizeof(animFileName), "%s%04d-%02d.anim", fileName.c_str(), seqWLK[i].mAnimID, seqWLK[i].mSubAnimID);

		animFiles[i].openFile(animFileName);
	}

	DCAnimationManager* anim = new DCAnimationManager;
	
	anim->SetAnimSeqInfo(seqWLK, seqNum);
	anim->SetBoneInfo(header,mpq, animFiles);
	//result->SetAnimManager(anim);
	animMgr = anim;

	SafeDeleteArray(animFiles);
	return result;
}


//----------------------LoadTexture---------------------------------------------------------------------

DCTexture* DCWOWLoader::LoadTexture(const std::string& _filename)
{	
	DCSurface* surface = DCSurface::Create(_filename);

	if(surface!=NULL)
	{
		DCSurfacePtr ptr(surface);
		return new DCTexture(ptr);
	}
	else
	{
		return NULL;
	}
}