#include "EnginePCH.h"
//#include "App.h"

BM_SINGLETON_DEFINE(BMEngine);

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
	//blan
    //DXUTTimer::SetTime(App::Instance().GetTimer().Seconds());
	DXUTTimer::SetTime(DXUTTimer::GetTime()+fDeltaTime);
	//DXUTTimer::SetTime(0.0);
    DXUTTimer::SetElapsedTime(fDeltaTime);

    LevelManager::Instance().GetLevelInstance()->Tick(fDeltaTime);    

	//add scene nodes into renderer
	const LevelInstance* instance = LevelManager::Instance().GetLevelInstance();
	const std::vector<SceneNodePtr>& nodes =  instance->GetNodes();
	const uint32 size = nodes.size();
	for(uint32 i=0; i<size; i++)
	{
		const SceneNodePtr& node = nodes[i];
		DCRenderer::Instance().AddSceneNode(node->GetModel(), node->GetTranslation());
	}	
}

void BMEngine::ReleaseResource()
{
    LevelManager::Instance().ReleaseLevelInstance();
}