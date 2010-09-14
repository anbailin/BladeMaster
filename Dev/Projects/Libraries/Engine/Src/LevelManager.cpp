#include "EnginePrivate.h"

SINGLETON_DEFINE(LevelManager);

LevelManager::LevelManager()
:   mLevelInstance(NULL)
{

}

LevelManager::~LevelManager()
{
    SafeDelete(mLevelInstance);
}

namespace
{
    const char* LevelMapPath = "..\\Engine\\Map\\";
}
LevelInstance* LevelManager::CreateLevelInstance(const char* name)
{
    //
    LevelInstance* levelInstance = new LevelInstance;

	//blan todo
    //parse xml to readin models->init nodes->add into level instance
    //QDir dir("AppData:Map");
    //std::string fullPath(dir.absolutePath().toStdString() + "\\");

	std::string fullPath = LevelMapPath;
    fullPath+=name;
    fullPath+=".xml";    
    
    TiXmlDocument *levelDoc = new TiXmlDocument();
    bool result = levelDoc->LoadFile(fullPath.c_str());
	assert(result);

    TiXmlElement *RootElement = levelDoc->RootElement();        

    for(TiXmlElement* ele_it = RootElement->FirstChildElement(); ele_it; ele_it = (TiXmlElement*)ele_it->NextSibling())
    {
        struct NodeInfo
        {
            const char* path;
            const char* name;
            float x,y;
            NodeInfo():path(NULL),name(NULL){}
        };
        const char* path_name = "path";
        const char* name_name = "name";
        const char* posx_name = "posx";
        const char* posy_name = "posy";
        
        NodeInfo nodeInfo;
        for(TiXmlAttribute* attr_it = ele_it->FirstAttribute(); attr_it; attr_it = attr_it->Next())
        {
            const char* name = attr_it->Name();
            
            if(strcmp(path_name, name)==0)
            {
                nodeInfo.path = attr_it->Value();
            }
            else if(strcmp(name_name, name)==0)
            {
                nodeInfo.name = attr_it->Value();
            }
            else if(strcmp(posx_name, name)==0)
            {
                nodeInfo.x = (float)attr_it->DoubleValue();
            }
            else if(strcmp(posy_name, name)==0)
            {
                nodeInfo.y = (float)attr_it->DoubleValue();
            }
        }     

        DCFilePath file(nodeInfo.path,nodeInfo.name);
		DCAnimationManager* animMgr = NULL;
        DCModelPtr modelPtr = DCWOWLoader::GetInstance()->LoadModel(file, animMgr); 
        SceneNodePtr nodePtr = new SceneNode;
        nodePtr->SetModel(modelPtr);
        XMFLOAT3 translation(nodeInfo.x, 0.0f, nodeInfo.y);
        nodePtr->SetTranslation(translation);
		nodePtr->SetAnimMgr(animMgr);

        levelInstance->AddNode(nodePtr);
    }
    
    //init levelinstance's terrain
    BMTerrainPtr terrainPtr = new BMTerrain;
    levelInstance->SetTerrain(terrainPtr);

    return levelInstance;
}

void LevelManager::LoadMap(const char* name)
{
    mLevelInstance = CreateLevelInstance(name);
}

void LevelManager::ReleaseLevelInstance()
{
    SafeDelete(mLevelInstance);
}