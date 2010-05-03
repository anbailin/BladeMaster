#include "EnginePrivate.h"

void BMScene::AddNode(SceneNodePtr& node)
{
	mSceneNodes.push_back(node);
}

void BMScene::SetTerrain(BMTerrainPtr& terrain)
{
	mTerrain = terrain; 
}

BMScene::BMScene()
{
	mCamera = new BMCamera;
}

BMScene::~BMScene()
{
	SafeDelete(mTerrain);
}

void BMScene::Tick(float delta)
{
	mCamera->Tick(delta);

	const uint32 num = mSceneNodes.size();
	
	for(uint32 i=0; i<num; i++)
	{
		mSceneNodes[i]->Tick(delta);
	}
}