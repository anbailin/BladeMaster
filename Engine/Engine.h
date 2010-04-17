#pragma once

class ENGINE_DLL BMEngine
{
public:
    SINGLETON_DECLARE(BMEngine);
    void Init();
    void Tick(float delta);
    void ReleaseResource();
};
