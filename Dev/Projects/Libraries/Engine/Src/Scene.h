#pragma once

class BMScene : public RefObject
{
public:
	BMScene();
	~BMScene();
	void Tick(float delta);

	//attribute access
public:
	void AddNode(SceneNodePtr& model);
	void SetTerrain(BMTerrainPtr& terrain);

	const std::vector<SceneNodePtr>& GetNodes()const   { return mSceneNodes; }
	const BMTerrainPtr& GetTerrain()const               { return mTerrain; }
	BMCameraPtr			GetCamera()						{ return mCamera; }

protected:
	std::vector<SceneNodePtr>   mSceneNodes;
	BMTerrainPtr                mTerrain;
	BMCameraPtr					mCamera;
};

typedef ComPtr<BMScene> BMScenePtr;