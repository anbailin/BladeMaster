#pragma once

class RENDER_DLL Renderer : public QObject
{
    Q_OBJECT

public:
    Renderer();
    ~Renderer();

public:
    virtual void Init(QWidget* pRenderWidget);
    virtual void Exit();
    virtual void Tick(f32 fDeltaTime);

    QWidget* GetRenderWidget() const { return m_pRenderWidget; }

protected:
    QPointer<QWidget> m_pRenderWidget;
};
