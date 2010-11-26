#include "EnginePrivate.h"

LevelInstance::LevelInstance()
{
	mScene = new BMScene;
}

LevelInstance::~LevelInstance()
{
    SAFE_RELEASE(mScene);
}

void LevelInstance::AddNode(SceneNodePtr& node)
{
    mScene->AddNode(node);
}

void LevelInstance::SetTerrain(BMTerrainPtr& terrain)
{
    mScene->SetTerrain(terrain); 
}

void LevelInstance::Tick(float delta)
{
	mScene->Tick(delta);
}