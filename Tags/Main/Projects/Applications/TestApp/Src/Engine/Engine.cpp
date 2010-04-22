
//#include "stdafx.h"
#include "EnginePCH.h"

BM_SINGLETON_DEFINE(BMEngine);

void BMEngine::Init()
{
    DCRenderer::CreateInstance();
    DCRenderer::Instance().Init();

    LevelManager::CreateInstance();   
    SceneRenderer::CreateInstance();
}

void BMEngine::Tick(float delta)
{
    LevelManager::Instance().GetLevelInstance()->Tick(delta);    
}

void BMEngine::ReleaseResource()
{
    LevelManager::Instance().ReleaseLevelInstance();
}