#pragma once

class ENGINE_DLL BMEngine : public BM::GameEngine
{
    Q_OBJECT

    SINGLETON_DECLARE(BMEngine);

public:
    virtual void Init();
    virtual void Exit();
    virtual void Tick(float fDeltaTime);

    void ReleaseResource();
};

BM_CLASS_FACTORY_REGISTER(BMEngine);
