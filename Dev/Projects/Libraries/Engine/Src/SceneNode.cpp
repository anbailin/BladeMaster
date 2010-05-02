#include "EnginePrivate.h"

SceneNode::SceneNode()
{

}

SceneNode::~SceneNode()
{

}

void SceneNode::SetModel(DCModelPtr model)
{
    mModel = model;
}

void SceneNode::SetTranslation(const XMFLOAT3& trans)
{
    mTranslation = trans;
}

void SceneNode::Tick(float delta)
{    
	BM_Assert(mAnimManager);
	mAnimManager->Animate(3);

	mModel->SetSkinningData(mAnimManager->GetMatrixPool());
}