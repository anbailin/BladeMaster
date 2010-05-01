#pragma once

//-------------------------------------------------------------------------
//  SceneNode--basic element of scene graph
//  *tree structure
//  *contains models, other model info(pos, bounding box...)
//  *
//-------------------------------------------------------------------------

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

    //attributes
protected:
    //tree structure
    std::vector<SceneNode*> mChildren;
    
    //content
    DCModelPtr              mModel;
    XMFLOAT3                mTranslation;
};

typedef ComPtr<SceneNode> SceneNodePtr;