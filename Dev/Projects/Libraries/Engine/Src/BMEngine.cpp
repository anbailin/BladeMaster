#include "EnginePrivate.h"

SINGLETON_DEFINE(BMEngine);

void BMEngine::Init()
{
    LevelManager::CreateInstance();   
    SceneRenderer::CreateInstance();

    LevelManager::GetInstance()->LoadMap("map");
}

void BMEngine::Exit()
{
    ReleaseResource();
}

void BMEngine::Tick(float fDeltaTime)
{
	//blan
    //DXUTTimer::SetTime(App::GetInstance()->GetTimer().Seconds());
	DXUTTimer::SetTime(DXUTTimer::GetTime()+fDeltaTime);	
    DXUTTimer::SetElapsedTime(fDeltaTime);

    LevelManager::GetInstance()->GetLevelInstance()->Tick(fDeltaTime);    

	//add scene nodes into renderer
	const LevelInstance* instance = LevelManager::GetInstance()->GetLevelInstance();
	BMScenePtr scene = instance->GetScene();
	const std::vector<SceneNodePtr>& nodes =  scene->GetNodes();
	const uint32 size = nodes.size();
	for(uint32 i=0; i<size; i++)
	{
		const SceneNodePtr& node = nodes[i];
		DCRenderer::GetInstance()->AddSceneNode(node->GetModel(), node->GetTranslation());
	}	

	DCRenderer::GetInstance()->AddSceneTerrain(scene->GetTerrain());

	BMCameraPtr camPtr = scene->GetCamera();
	DCRenderer::GetInstance()->SetViewProjMatrix(camPtr->GetViewMatrix(), camPtr->GetProjMatrix(), camPtr->GetViewProjMatrix());
}

void BMEngine::ReleaseResource()
{
    LevelManager::GetInstance()->ReleaseLevelInstance();
}