#include "EnginePCH.h"
#include "App.h"

//BM_SINGLETON_DEFINE(BMEngine);

void BMEngine::Init()
{
    //DCRenderer::CreateInstance();
    //DCRenderer::Instance().Init();

    LevelManager::CreateInstance();   
    SceneRenderer::CreateInstance();

    LevelManager::Instance().LoadMap("map");
}

void BMEngine::Exit()
{
    ReleaseResource();
}

void BMEngine::Tick(float fDeltaTime)
{
    DXUTTimer::SetTime(App::Instance().GetTimer().Seconds());
    DXUTTimer::SetElapsedTime(fDeltaTime);

    LevelManager::Instance().GetLevelInstance()->Tick(fDeltaTime);    
}

void BMEngine::ReleaseResource()
{
    LevelManager::Instance().ReleaseLevelInstance();
}