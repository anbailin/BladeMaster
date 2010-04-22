#include "Core.h"
#include "EnginePCH.h"
#include "DCWOWLoader.h"

//--------tinyxml-------------------
#define TIXML_USE_STL
#include "TinyXML/tinyxml.h"
#include "TinyXML/tinystr.h"

BM_SINGLETON_DEFINE(LevelManager);

#pragma optimize("",off)

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
    const char* LevelMapPath = "..\\Data\\Map\\";
}
LevelInstance* LevelManager::CreateLevelInstance(const char* name)
{
    //
    LevelInstance* levelInstance = new LevelInstance;

    //parse xml to readin models->init nodes->add into level instance
    QDir dir("AppData:Map");
    std::string fullPath(dir.absolutePath().toStdString() + "\\");
    fullPath+=name;
    fullPath+=".xml";
    
    TiXmlDocument *levelDoc = new TiXmlDocument();
    levelDoc->LoadFile(fullPath.c_str());

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
        DCModelPtr modelPtr = DCWOWLoader::Instance().LoadModel(file); 
        SceneNodePtr nodePtr = new SceneNode;
        nodePtr->SetModel(modelPtr);
        XMFLOAT3 translation(nodeInfo.x, 0.0f, nodeInfo.y);
        nodePtr->SetTranslation(translation);

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