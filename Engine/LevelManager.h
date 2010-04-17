#pragma once

class LevelInstance;

class ENGINE_DLL LevelManager
{
public:
    SINGLETON_DECLARE(LevelManager);
    LevelManager();
    ~LevelManager();
    
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