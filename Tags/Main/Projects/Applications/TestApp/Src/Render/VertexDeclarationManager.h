#pragma once

class VertexDeclareManager
{
    BM_SINGLETON_DECLARE(VertexDeclareManager);

public:
    void CreateResource();
    void ReleaseResource();
    void ApplyVertexDeclaration(DCVertexType type);

protected:
    VertexDeclareManager();
    ~VertexDeclareManager();

    VertexDeclPtr mDeclarations[VertexTypeCount];
};