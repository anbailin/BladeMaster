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

    const std::vector<SceneNodePtr>& GetNodes()const   { return mSceneNodes; }
    const BMTerrainPtr& GetTerrain()const               { return mTerrain; }

protected:
    std::vector<SceneNodePtr>   mSceneNodes;
    BMTerrainPtr                mTerrain;
};