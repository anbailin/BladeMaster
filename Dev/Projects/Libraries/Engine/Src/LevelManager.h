#pragma once

class LevelInstance;

class ENGINE_DLL LevelManager
{
    SINGLETON_DECLARE(LevelManager);

public:
    LevelManager();
    virtual ~LevelManager();
    
    LevelInstance* CreateLevelInstance(const char* name);
    void LoadMap(const char* name);

    //attribute access
public:
    void SetLevelInstance(LevelInstance* instance)  { mLevelInstance = instance; }
    LevelInstance* GetLevelInstance()               { return mLevelInstance; }
    const LevelInstance* GetLevelInstance()const    { return mLevelInstance; }
    void ReleaseLevelInstance();

protected:
    LevelInstance* mLevelInstance;
};