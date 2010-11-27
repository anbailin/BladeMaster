#pragma once

class ENGINE_DLL GameEngine : public QObject
{
    Q_OBJECT

public:
    GameEngine(){}
    ~GameEngine(){}

public:
    virtual void Init(){}
    virtual void Exit(){}
    virtual void Tick(f32 fDeltaTime){}
};

BM_CLASS_FACTORY_REGISTER(GameEngine);
