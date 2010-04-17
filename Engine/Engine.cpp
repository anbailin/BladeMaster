
//#include "stdafx.h"
#include "EnginePCH.h"

SINGLETON_DEFINE(BMEngine);

void BMEngine::Init()
{
    DCRenderer::CreateInstance();
    DCRenderer::GetInstance()->Init();

    LevelManager::CreateInstance();   
    SceneRenderer::CreateInstance();
}

void BMEngine::Tick(float delta)
{
    LevelManager::GetInstance()->GetLevelInstance()->Tick(delta);    
}

void BMEngine::ReleaseResource()
{
    LevelManager::GetInstance()->ReleaseLevelInstance();
}