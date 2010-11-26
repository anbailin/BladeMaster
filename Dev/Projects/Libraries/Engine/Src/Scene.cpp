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
	SAFE_DELETE(mTerrain);
}

void BMScene::Tick(float delta)
{
	mCamera->Tick(delta);

	const u32 num = mSceneNodes.size();
	
	for(u32 i=0; i<num; i++)
	{
		mSceneNodes[i]->Tick(delta);
	}
}