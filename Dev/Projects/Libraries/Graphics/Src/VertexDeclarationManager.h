#pragma once

class VertexDeclareManager
{
    SINGLETON_DECLARE(VertexDeclareManager);

public:
    void CreateResource();
    void ReleaseResource();
    void ApplyVertexDeclaration(DCVertexType type);

protected:
    VertexDeclareManager();
    ~VertexDeclareManager();

    VertexDeclPtr mDeclarations[VertexTypeCount];
};