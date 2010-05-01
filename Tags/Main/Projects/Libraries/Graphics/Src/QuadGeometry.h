#pragma once

/**
*   full screen quad utitliy
*   for screen space render vertex buffer usage
*/
class QuadGeometry
{
public:
    QuadGeometry();
    ~QuadGeometry();

    void Init();
    void Render()const;
    void ReleaseResource();

protected:
    VertexBufferPtr	mVertexBuffer;
    VertexDeclPtr   mVertexDelcaration;
};
