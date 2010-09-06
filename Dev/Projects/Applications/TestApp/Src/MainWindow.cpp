#include "AppPrivate.h"
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
    : QMainWindow(parent, flags)
{
	//main window setup
	setWindowTitle(tr("BladeMaster"));

	//mdi area
	QMdiArea* mdiArea = new QMdiArea;
	mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	setCentralWidget(mdiArea);

	QTextEdit* textEdit = new QTextEdit;
	mdiArea->addSubWindow(textEdit);	

	////rendering window
	////m_renderParentWidget = new QDockWidget(tr("Rendering"), this);
	////m_renderParentWidget->setMinimumSize(1280,720);
	////m_renderParentWidget->setMaximumSize(1280,720);
	////m_renderParentWidget->setAllowedAreas(Qt::AllDockWidgetAreas);

	m_renderWidget = new BMWidget(mdiArea);
	m_renderWidget->setMinimumSize(1280,720);
	m_renderWidget->setMaximumSize(1280,720);
	setCentralWidget(m_renderWidget);
    //addWidget();
	
	//addDockWidget(Qt::TopDockWidgetArea, m_renderParentWidget);

    //------test for grabber&ogre code
    //QWidget* centralWidget = new QWidget;
    //setCentralWidget(centralWidget);

    //m_renderWidget = new BMWidget;
    //m_renderWidget->setMinimumSize(1280,720);
    //m_renderWidget->setMaximumSize(1280,720);

    //QScrollArea * glWidgetArea = new QScrollArea;
    //glWidgetArea->setWidget(m_renderWidget);
    //glWidgetArea->setWidgetResizable(true);
    //glWidgetArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //glWidgetArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //glWidgetArea->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    //glWidgetArea->setMinimumSize(50, 50);

    //QGridLayout *centralLayout = new QGridLayout;
    //centralLayout->addWidget(glWidgetArea, 0, 0);    
    //centralWidget->setLayout(centralLayout);
}

MainWindow::~MainWindow()
{

}


