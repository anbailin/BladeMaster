#pragma once

#include <QtGui>

class BMWidget : public QWidget
{
    Q_OBJECT

public:
    BMWidget(QWidget *parent = 0);
    ~BMWidget();

    // Override QWidget::paintEngine to return NULL
    QPaintEngine* paintEngine() const; // Turn off QTs paint engine for the Ogre widget.

    public slots:
        void setBackgroundColor(QColor c);
        //void setCameraPosition(const Ogre::Vector3 &pos);

signals:
        //void cameraPositionChanged(const Ogre::Vector3 &pos);

protected:
    virtual void keyPressEvent(QKeyEvent *e);
    virtual void moveEvent(QMoveEvent *e);
    virtual void mouseDoubleClickEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void paintEvent(QPaintEvent *e);
    virtual void resizeEvent(QResizeEvent *e);
    virtual void showEvent(QShowEvent *e);
    virtual void wheelEvent(QWheelEvent *e);

private:
    void initOgreSystem();
    void setupNLoadResources();
    void createScene();

private:    
    static const QPoint invalidMousePoint;
};