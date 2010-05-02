#include "EnginePrivate.h"

LevelInstance::LevelInstance()
{

}

LevelInstance::~LevelInstance()
{
    SafeRelease(mTerrain);
    mSceneNodes.clear();
}

void LevelInstance::AddNode(SceneNodePtr& node)
{
    mSceneNodes.push_back(node);
}

void LevelInstance::SetTerrain(BMTerrainPtr& terrain)
{
    mTerrain = terrain; 
}

void LevelInstance::Tick(float delta)
{
    const uint32 num = mSceneNodes.size();

    for(uint32 i=0; i<num; i++)
    {
        mSceneNodes[i]->Tick(delta);
    }
}