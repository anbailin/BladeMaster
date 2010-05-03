#pragma once


//-------------------------------------------------------------------------
//  LevelInstance--simple desc of level
//-------------------------------------------------------------------------
class LevelInstance
{
public:
    LevelInstance();
    ~LevelInstance();
    
    void Tick(float delta);

    //attribute access
public:
    void AddNode(SceneNodePtr& model);
    void SetTerrain(BMTerrainPtr& terrain);
	BMScenePtr& GetScene()					{	return mScene; }
	const BMScenePtr& GetScene()const		{	return mScene; }

protected:    
	BMScenePtr					mScene;
};