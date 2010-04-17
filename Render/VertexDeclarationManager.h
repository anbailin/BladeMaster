#pragma once

class VertexDeclareManager
{
public:
    SINGLETON_DECLARE(VertexDeclareManager);

    void CreateResource();
    void ReleaseResource();
    void ApplyVertexDeclaration(DCVertexType type);

protected:
    VertexDeclareManager();
    ~VertexDeclareManager();

    VertexDeclPtr mDeclarations[VertexTypeCount];
};