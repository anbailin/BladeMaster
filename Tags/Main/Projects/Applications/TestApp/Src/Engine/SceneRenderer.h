#pragma once

//-------------------------------------------------------------------------
//  SceneRenderer
//-------------------------------------------------------------------------
class LevelInstance;

class ENGINE_DLL SceneRenderer
{
    BM_SINGLETON_DECLARE(SceneRenderer);

public:
    SceneRenderer();
    ~SceneRenderer();

    //funcs
public:
    void RenderScene(const LevelInstance& instance);
    
    //attributes access    
public:
    void SetViewMatrix(const D3DXMATRIXA16& matrix);
    void SetProjMatrix(const D3DXMATRIXA16& matrix);

    //attributes
protected:
    D3DXMATRIXA16   mViewMatrix;
    D3DXMATRIXA16   mProjMatrix;
};