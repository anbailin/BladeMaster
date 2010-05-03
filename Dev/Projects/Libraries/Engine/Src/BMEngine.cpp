#include "EnginePrivate.h"

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
    DXUTTimer::SetElapsedTime(fDeltaTime);

    LevelManager::Instance().GetLevelInstance()->Tick(fDeltaTime);    

	//add scene nodes into renderer
	const LevelInstance* instance = LevelManager::Instance().GetLevelInstance();
	BMScenePtr scene = instance->GetScene();
	const std::vector<SceneNodePtr>& nodes =  scene->GetNodes();
	const uint32 size = nodes.size();
	for(uint32 i=0; i<size; i++)
	{
		const SceneNodePtr& node = nodes[i];
		DCRenderer::Instance().AddSceneNode(node->GetModel(), node->GetTranslation());
	}	

	DCRenderer::Instance().AddSceneTerrain(scene->GetTerrain());

	BMCameraPtr camPtr = scene->GetCamera();
	DCRenderer::Instance().SetViewProjMatrix(camPtr->GetViewMatrix(), camPtr->GetProjMatrix(), camPtr->GetViewProjMatrix());
}

void BMEngine::ReleaseResource()
{
    LevelManager::Instance().ReleaseLevelInstance();
}