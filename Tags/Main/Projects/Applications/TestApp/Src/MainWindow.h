#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~MainWindow();

	//attr access
public:
	QWidget* GetRenderWidget() { return m_renderWidget; }

	//attr
protected:
    Ui::MainWindowClass ui;
	QWidget*			m_renderWidget;
	QDockWidget*		m_renderParentWidget;
};

#endif // MAINWINDOW_H
