#pragma once

class ENGINE_DLL BMEngine
{
    BM_SINGLETON_DECLARE(BMEngine);

public:
    void Init();
    void Tick(float delta);
    void ReleaseResource();
};
