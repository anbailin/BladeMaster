#pragma once

//-------------------------------------------------------------------------
//  SceneNode--basic element of scene graph
//  *tree structure
//  *contains models, other model info(pos, bounding box...)
//  *
//-------------------------------------------------------------------------
class DCAnimationManager;
class SceneNode : public RefObject
{
public:
    SceneNode();
    ~SceneNode();

    //funcs
public:
    void Tick(float delta);

    //attribute access
public:
    const DCModelPtr&   GetModel() { return mModel; }
    const XMFLOAT3&     GetTranslation()const { return mTranslation; }
    void SetModel(DCModelPtr model);
    void SetTranslation(const XMFLOAT3& trans);
	void SetAnimMgr(DCAnimationManager* animMgr) { mAnimManager = animMgr; }

    //attributes
protected:
    //tree structure
    std::vector<SceneNode*> mChildren;
    
    //content
    DCModelPtr              mModel;
    XMFLOAT3                mTranslation;
	DCAnimationManager*		mAnimManager;
};

typedef ComPtr<SceneNode> SceneNodePtr;