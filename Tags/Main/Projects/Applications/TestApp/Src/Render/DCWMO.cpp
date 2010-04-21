#include "DCRenderHeader.h"

//namespace
//{
//	struct NamePair
//	{
//		char* name[5];
//		uint32 size;
//		uint32 nextpos;
//		void ReadIn(MPQFile& file)
//		{
//			file.read(name,4);
//			file.read(&size,4);
//			flipcc((char*)name);
//			name[4] = 0;
//			nextpos = file.getPos() + size;
//		}
//	};
//
//	struct DataPair
//	{
//		char*	addr;
//		uint32	num;
//		DataPair():addr(NULL),num(0){}
//	};
//
//}
////----wmo---------------------------------------------------------------------------------------
//void WMO::Init(std::string file_name)
//{
//	//MPQFile file(file_name.c_str());
//
//	//NamePair name;	
//	//
//	//DataPair tTexName;
//	//DataPair tGroupName;
//	//DataPair tModelName;
//
//	//std::vector<std::string> tModelNames;
//
//	//while(file.isEof() == false)
//	//{
//	//	name.ReadIn(file);
//	//	char* name_ptr = (char*)name.name;
//	//	if(!strcmp(name_ptr,"MOHD"))		//header
//	//	{
//	//		file.read(&mHeader,sizeof(WMOHeader));
//	//		SetWMOGroupNum(mHeader.mGroupNum);
//	//		SetMaterialNum(mHeader.mTextureNum);
//	//	}else if (!strcmp(name_ptr,"MOTX")) //texture name buffer
//	//	{
//	//		tTexName.num = name.size;
//	//		tTexName.addr = file.getPointer();
//	//	}else if (!strcmp(name_ptr,"MOMT")) //materials
//	//	{
//	//		const WMOMaterial* tMaterialPtr = (const WMOMaterial*)file.getPointer();
//	//		for(uint32 i=0;i<mHeader.mTextureNum;i++)
//	//		{
//	//			std::string tTexPath(tTexName.addr + tMaterialPtr[i].nameStart);
//	//			DCTexturePtr tTexPtr (DCWOWLoader::GetInstance()->LoadTexture(tTexPath));
//	//			DCMaterialPtr tMatPtr(new DCMaterial);
//	//			tMatPtr->SetTexturePtr(tTexPtr);
//	//			SetMaterial(tMatPtr,i);
//	//		}
//	//	}else if (!strcmp(name_ptr,"MOGN")) 
//	//	{
//	//		tGroupName.num = name.size;
//	//		tGroupName.addr = file.getPointer();
//	//	}else if (!strcmp(name_ptr,"MOGI")) // group info
//	//	{			
//	//		for(uint32 i=0;i<mHeader.mGroupNum;i++)
//	//		{
//	//			mGroups[i]->Init(this,file,i,tGroupName.addr);
//	//		}
//	//	}else if (!strcmp(name_ptr,"MODN")) //model names
//	//	{
//	//		if(name.size>0)
//	//		{
//	//			tModelName.addr = file.getPointer();
//	//			tModelName.num = 0;
//
//	//			fixname(tModelName.addr,name.size);
//
//	//			char* ptr = tModelName.addr;
//	//			char* end = ptr + name.size;
//
//	//			while (ptr<end) 
//	//			{
//	//				std::string tModelPath(ptr);
//	//				ptr += strlen(ptr) + 1;
//	//				while(ptr<end && *ptr==0) ptr++;
//	//				tModelNames.push_back(tModelPath);
//	//			}
//	//		}
//	//	}else if (!strcmp(name_ptr,"MODS"))//doodad set
//	//	{
//
//	//	}else if (!strcmp(name_ptr,"MODD"))//model instance setting
//	//	{
//	//		uint32 nModel = name.size/sizeof(WMOMODDChunk);
//
//	//		SetModelInstanceNum(nModel);
//
//	//		for(uint32 i=0;i<nModel;i++)
//	//		{
//	//			int ofs;
//	//			file.read(&ofs,sizeof(ofs));
//	//			char* tCharPtr = tModelName.addr + ofs;
//
//	//			DCFilePath tModelPath(tCharPtr);
//	//			
//	//			DCModelPtr tModelPtr(DCWOWLoader::GetInstance()->LoadModel(tModelPath));
//	//			WMOMODDChunk chunk;
//	//			file.read(&chunk,sizeof(WMOMODDChunk));
//
//	//			DCModelInstancePtr instance(new DCModelInstance);
//
//	//			instance->Init(tModelPtr,chunk);
//	//			
//	//			SetModelInstance(instance,i);
//	//		}
//	//	}else if (!strcmp(name_ptr ,"MOSB")) //sky boxes
//	//	{
//	//		
//	//	}else if (!strcmp(name_ptr ,"MOPV"))
//	//	{
//
//	//	}else if (!strcmp(name_ptr ,"MOPR"))
//	//	{
//
//	//	}else if (!strcmp(name_ptr ,"MFOG"))
//	//	{
//
//	//	}
//
//	//	file.seek(name.nextpos);
//	//}
//}
//
//void WMO::Draw()
//{
//	uint32 len = mGroups.size();
//	for (uint32 i=0;i<len;i++)
//	{
//		mGroups[i]->Draw();
//	}
//}
//
////----wmo instance------------------------------------------------------------------------------
//void WMOInstance::Init(const WMOPtr &ptr, const ADTMODFChunk &chunk)
//{
//	DCMatrix33 mat;
//	mat.Rotation(chunk.mOrientation);
//	mTranslator.SetRotate(mat);
//	mTranslator.SetScale(1);
//	mTranslator.SetTranslation(chunk.mTranslation);
//
//	mWMO = ptr;
//
//	mGUID = chunk.guid;
//	mDoodadSet = chunk.mDoodadSetIndex;
//}
//
//
////----wmo group---------------------------------------------------------------------------------
//
//
//
//void WMOGroup::Init(WMO* _wmo, MPQFile &file, int num, char *names)
//{
//	mWMO = _wmo;
//	mModelPtr = new WMOModel;
//	mNum = num;
//
//	WMOGroupInfo info;
//	file.read(&info,sizeof(WMOGroupInfo));
//	mBoundingBox = info.mBoundingBox;
//	mFlag = info.mFlag;
//}
//
//void WMOGroup::InitRender()
//{
//	/*
//	//--name---------------------------------------
//	char temp[256];
//	mWMO->GetName()._Copy_s(temp, 256, 256);
//	temp[mWMO->GetName().length() - 4] = 0;
//
//	char fname[256];
//	sprintf_s(fname,256,"%s_%03d.wmo",temp, mNum);
//
//	MPQFile file(fname);
//	file.seek(0x14);
//	//--info---------------------------------------
//	DataPair vertex;
//	DataPair normal;
//	DataPair index;
//	DataPair texcoord;
//	DataPair material;
//	//DataPair doodad;
//	DataPair batch;
//
//	while(file.isEof()==false)
//	{
//		NamePair name;
//		name.ReadIn(file);
//		char* name_ptr = (char*)name.name;
//		if(!strcmp(name_ptr,"MOPY"))//materials
//		{
//			material.num = name.size/2;
//			material.addr = file.getPointer();
//		}else if(!strcmp(name_ptr,"MOVI"))
//		{
//			index.num = name.size/2;
//			index.addr = file.getPointer();
//		}else if(!strcmp(name_ptr,"MOVT"))
//		{
//			vertex.num = name.size/2;
//			vertex.addr = file.getPointer();
//		}else if(!strcmp(name_ptr,"MONR"))
//		{
//			normal.num = name.size/2;
//			normal.addr = file.getPointer();
//		}else if(!strcmp(name_ptr,"MOTV"))
//		{
//			texcoord.num = name.size/2;
//			texcoord.addr = file.getPointer();
//		}else if(!strcmp(name_ptr, "MOLR"))
//		{
//			
//		}else if(!strcmp(name_ptr, "MODR"))
//		{
//
//		}else if(!strcmp(name_ptr, "MOBA"))
//		{
//
//		}else if(!strcmp(name_ptr, "MOCV"))
//		{
//
//		}else if(!strcmp(name_ptr, "MLIQ"))
//		{
//
//		}
//
//		file.seek(name.nextpos);
//	}
//
//	//--create render resource-----------------------------
//	assert( (vertex.num == normal.num)&&(vertex.num == texcoord.num));
//	uint32 tElementNum = vertex.num;
//	std::vector<DCVertPosNorTex> vtxbuffer(tElementNum);
//	const DCVector3* tPosPtr = (const DCVector3*) vertex.addr;
//	const DCVector3* tNorPtr = (const DCVector3*) normal.addr;
//	const DCVector2* tTexcoordPtr = (const DCVector2*) texcoord.addr;
//	for(uint32 i=0;i<tElementNum;i++)
//	{
//		vtxbuffer[i].pos = tPosPtr[i];
//		vtxbuffer[i].normal = tNorPtr[i];
//		vtxbuffer[i].tex = tTexcoordPtr[i];
//	}
//
//	mModelPtr->SetVertexInfo(&(vtxbuffer[0]),tElementNum,sizeof(DCVertPosNorTex));
//
//	const WMOBatch* tBatchPtr = (const WMOBatch*)batch.addr;
//	mModelPtr->SetGeometryNum(batch.num);
//	for(uint32 i=0;i<batch.num;i++)
//	{
//		WMOGeometryPtr geo(new WMOGeometry);
//		geo->SetBasicInfo(tBatchPtr[i]);
//
//		const DCMaterialPtr& material = mWMO->GetMaterial(tBatchPtr[i].texture);
//		geo->SetMaterialPtr(material);
//
//		mModelPtr->SetGeometryPtr(geo,i);
//	}
//	*/
//}
//
//void WMOGroup::Draw()
//{
//	mModelPtr->Draw();
//}
//
//
////----wmo model---------------------------------------------------------------------------------
//void WMOModel::SetVertexInfo(const void* addr, uint32 count,uint32 stride)
//{
//	VertexBufferPtr tVtxBufferPtr;
//	uint32 length = count*stride;
//	FAIL_ASSERT(DEVICEPTR->CreateVertexBuffer(length,0,0,D3DPOOL_MANAGED,&tVtxBufferPtr,0));
//
//	void* lockPtr;
//	FAIL_ASSERT(tVtxBufferPtr->Lock(0,0,&lockPtr,NULL));
//	memcpy(lockPtr,addr,length);
//	tVtxBufferPtr->Unlock();
//
//	mVertexCount = count;
//	mVtxBuffer = tVtxBufferPtr;
//}
//
//void WMOModel::Draw()
//{
//	DCSimpleCreatureShader::Get()->Apply();
//
//	FAIL_ASSERT( DEVICEPTR->SetStreamSource(mVertexCount*sizeof(DCVertPosNorTex), mVtxBuffer,0,sizeof(DCVertPosNorTex)));
//
//	FAIL_ASSERT( DEVICEPTR->SetIndices(mNdxBuffer) );	
//}
////----wmo geometry-------------------------------------------------------------------------------
//void WMOGeometry::SetBasicInfo(const WMOBatch& batch)
//{
//	mIndexStart = batch.indexStart;
//	mIndexCount = batch.indexCount;
//	mVertexStart = batch.vertexStart;
//	mVertexEnd = batch.vertexEnd;
//}
//
//void WMOGeometry::Draw()
//{
//	DCTexturePtr tex = mMaterial->GetTexturePtr();
//
//	DCRenderer::Get()->ApplyTexture(0, tex);
//
//	FAIL_ASSERT( DEVICEPTR->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,mVertexEnd - mVertexStart,mIndexStart,mIndexCount/3));
//}