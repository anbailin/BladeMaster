#include "AppPrivate.h"
#include "BMWidget.h"

const QPoint BMWidget::invalidMousePoint(-1,-1);

BMWidget::BMWidget(QWidget *parent)
:QWidget(parent)
{
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_PaintOnScreen);
    setMinimumSize(240,240);
    setFocusPolicy(Qt::ClickFocus);
    QWidget::setMouseTracking(true);
}

BMWidget::~BMWidget()
{
}

void BMWidget::setBackgroundColor(QColor c)
{

}

void BMWidget::keyPressEvent(QKeyEvent *e)
{
    LogToDebug("keyPressEvent\n");
}

void BMWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    LogToDebug("mouseDoubleClickEvent\n");
}

void BMWidget::mouseMoveEvent(QMouseEvent *e)
{
    LogToDebug("mouseMoveEvent\n");
}

void BMWidget::mousePressEvent(QMouseEvent *e)
{
    LogToDebug("mousePressEvent\n");
}

void BMWidget::mouseReleaseEvent(QMouseEvent *e)
{
    LogToDebug("mouseReleaseEvent\n");
}

void BMWidget::moveEvent(QMoveEvent *e)
{
}

QPaintEngine* BMWidget::paintEngine() const
{
    return NULL;
}

void BMWidget::paintEvent(QPaintEvent *e)
{
    e->accept();
}

void BMWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

void BMWidget::showEvent(QShowEvent *e)
{
    QWidget::showEvent(e);
}

void BMWidget::wheelEvent(QWheelEvent *e)
{
    e->accept();
}



