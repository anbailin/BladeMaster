#include "EnginePCH.h"

BM_SINGLETON_DEFINE(SceneRenderer);

SceneRenderer::SceneRenderer()
{

}

SceneRenderer::~SceneRenderer()
{

}

void SceneRenderer::RenderScene(const LevelInstance& instance)
{
    //models
    // For our world matrix, we will just rotate the object about the y-axis.
    D3DXMATRIXA16 mxWorld, mxViewProj;

    D3DXMatrixIdentity(&mxViewProj);

    BM_AssertHr(DEVICEPTR->BeginScene());	
    {        
        DCRenderer::Instance().BeginRender();
        DEVICEPTR->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,D3DCOLOR_COLORVALUE(85.0f/255.0f,101.0f/255.0f,215.0f/255.0f,1.0f), 1.0f, 0 );
    BM_AssertHr(DEVICEPTR->EndScene());    
        //models
        const std::vector<SceneNodePtr>& nodes = instance.GetNodes();
        const uint32 nodeNum = nodes.size();
        for(uint32 nodeIdx = 0; nodeIdx<nodeNum; nodeIdx++)
        {
            BM_AssertHr(DEVICEPTR->BeginScene());
            const SceneNodePtr& nodePtrRef = nodes[nodeIdx];
            const XMFLOAT3& translation = nodePtrRef->GetTranslation();
            D3DXMatrixTranslation(&mxWorld, translation.x, translation.y, translation.z);
            mxViewProj = mViewMatrix * mProjMatrix;

            DEVICEPTR->SetVertexShaderConstantF(0,(float*)&(mxWorld),4);
            DEVICEPTR->SetVertexShaderConstantF(4,(float*)&(mxViewProj),4);
            DEVICEPTR->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
            DEVICEPTR->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
            
            nodePtrRef->GetModel()->Draw(0);
            BM_AssertHr(DEVICEPTR->EndScene()); 
        }

        BM_AssertHr(DEVICEPTR->BeginScene());
        //terrain
        instance.GetTerrain()->Draw(&mxWorld, &mViewMatrix, &mProjMatrix);

        BMPostFXRenderer::Instance().Render();

        DCRenderer::Instance().EndRender();
        BM_AssertHr(DEVICEPTR->EndScene()); 
    }
    
}

void SceneRenderer::SetViewMatrix(const D3DXMATRIXA16& matrix)
{
    mViewMatrix = matrix;
}

void SceneRenderer::SetProjMatrix(const D3DXMATRIXA16& matrix)
{
    mProjMatrix = matrix;
}