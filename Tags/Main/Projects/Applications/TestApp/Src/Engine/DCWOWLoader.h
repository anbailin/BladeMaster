#pragma once

//#include "MDX.h"
//#include "BLP.h"

class DCModel;
class DCTexture;
class DCMaterial;
class CreatureDisplayData;
class CreatureModelData;
class DCFilePath;

class ENGINE_DLL DCWOWLoader
{
    BM_SINGLETON_DECLARE(DCWOWLoader);

public:
	DCModel*							LoadModel(DCFilePath& path);
	DCModel*							LoadModel(uint32 creatureID);
	DCTexture*							LoadTexture(const std::string& _filename);

	void Init();

    //attribtues
private:
	CreatureDisplayData*				mCreatureDisplay;
	CreatureModelData*					mCreatureModel;
	std::vector<MPQArchive*>			mArchives;
};
