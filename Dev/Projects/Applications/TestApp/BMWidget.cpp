#include "AppPrivate.h"
#include "BMWidget.h"

const QPoint     BMWidget::invalidMousePoint(-1,-1);
//const Ogre::Real BMWidget::turboModifier(10);

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

//void BMWidget::setCameraPosition(const Ogre::Vector3 &pos)
//{
//    ogreCamera->setPosition(pos);
//    ogreCamera->lookAt(0,50,0);
//    update();
//    emit cameraPositionChanged(pos);
//}

void BMWidget::keyPressEvent(QKeyEvent *e)
{
    //assert(0);
    //static QMap<int, Ogre::Vector3> keyCoordModificationMapping;
    //static bool mappingInitialised = false;

    //if(!mappingInitialised)
    //{
    //    keyCoordModificationMapping[Qt::Key_W]         = Ogre::Vector3( 0, 0,-5);
    //    keyCoordModificationMapping[Qt::Key_S]         = Ogre::Vector3( 0, 0, 5);
    //    keyCoordModificationMapping[Qt::Key_A]         = Ogre::Vector3(-5, 0, 0);
    //    keyCoordModificationMapping[Qt::Key_D]         = Ogre::Vector3( 5, 0, 0);
    //    keyCoordModificationMapping[Qt::Key_PageUp]   = Ogre::Vector3( 0, 5, 0);
    //    keyCoordModificationMapping[Qt::Key_PageDown] = Ogre::Vector3( 0,-5, 0);

    //    mappingInitialised = true;
    //}

    //QMap<int, Ogre::Vector3>::iterator keyPressed =
    //    keyCoordModificationMapping.find(e->key());
    //if(keyPressed != keyCoordModificationMapping.end() && ogreCamera)
    //{
    //    const Ogre::Vector3 &actualCamPos = ogreCamera->getPosition();
    //    setCameraPosition(actualCamPos + keyPressed.value());

    //    e->accept();
    //}
    //else
    //{
    //    e->ignore();
    //}
}

void BMWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    //assert(0);
    //if(e->buttons().testFlag(Qt::LeftButton))
    //{
    //    Ogre::Real x = e->pos().x() / (float)width();
    //    Ogre::Real y = e->pos().y() / (float)height();

    //    Ogre::Ray ray = ogreCamera->getCameraToViewportRay(x, y);
    //    Ogre::RaySceneQuery *query = ogreSceneManager->createRayQuery(ray);
    //    Ogre::RaySceneQueryResult &queryResult = query->execute();
    //    Ogre::RaySceneQueryResult::iterator queryResultIterator = queryResult.begin();

    //    if(queryResultIterator != queryResult.end())
    //    {
    //        if(queryResultIterator->movable)
    //        {
    //            selectedNode = queryResultIterator->movable->getParentSceneNode();
    //            selectedNode->showBoundingBox(true);
    //        }
    //    }
    //    else
    //    {
    //        selectedNode->showBoundingBox(false);
    //        selectedNode = 0;
    //    }

    //    ogreSceneManager->destroyQuery(query);

    //    update();
    //    e->accept();
    //}
    //else
    //{
    //    e->ignore();
    //}
}

void BMWidget::mouseMoveEvent(QMouseEvent *e)
{
    //assert(0);
    //if(e->buttons().testFlag(Qt::LeftButton) && oldPos != invalidMousePoint)
    //{
    //    const QPoint &pos = e->pos();
    //    Ogre::Real deltaX = pos.x() - oldPos.x();
    //    Ogre::Real deltaY = pos.y() - oldPos.y();

    //    if(e->modifiers().testFlag(Qt::ControlModifier))
    //    {
    //        deltaX *= turboModifier;
    //        deltaY *= turboModifier;
    //    }

    //    Ogre::Vector3 camTranslation(deltaX, deltaY, 0);
    //    const Ogre::Vector3 &actualCamPos = ogreCamera->getPosition();
    //    setCameraPosition(actualCamPos + camTranslation);

    //    oldPos = pos;
    //    e->accept();
    //}
    //else
    //{
    //    e->ignore();
    //}
}

void BMWidget::mousePressEvent(QMouseEvent *e)
{
    //assert(0);
    //if(e->buttons().testFlag(Qt::LeftButton))
    //{
    //    oldPos = e->pos();
    //    e->accept();
    //}
    //else
    //{
    //    e->ignore();
    //}
}

void BMWidget::mouseReleaseEvent(QMouseEvent *e)
{
    //assert(0);
    //if(!e->buttons().testFlag(Qt::LeftButton))
    //{
    //    oldPos = QPoint(invalidMousePoint);
    //    e->accept();
    //}
    //else
    //{
    //    e->ignore();
    //}
}

void BMWidget::moveEvent(QMoveEvent *e)
{
    //assert(0);
    //QWidget::moveEvent(e);

    //if(e->isAccepted() && ogreRenderWindow)
    //{
    //    ogreRenderWindow->windowMovedOrResized();
    //    update();
    //}
}

QPaintEngine* BMWidget::paintEngine() const
{
    // We don't want another paint engine to get in the way for our Ogre based paint engine.
    // So we return nothing.
    return NULL;
}

void BMWidget::paintEvent(QPaintEvent *e)
{
    //ogreRoot->_fireFrameStarted();
    //ogreRenderWindow->update();
    //ogreRoot->_fireFrameEnded();

    e->accept();
}

void BMWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    //if(e->isAccepted())
    //{
    //    const QSize &newSize = e->size();
    //    if(ogreRenderWindow)
    //    {
    //        ogreRenderWindow->resize(newSize.width(), newSize.height());
    //        ogreRenderWindow->windowMovedOrResized();
    //    }
    //    if(ogreCamera)
    //    {
    //        Ogre::Real aspectRatio = Ogre::Real(newSize.width()) / Ogre::Real(newSize.height());
    //        ogreCamera->setAspectRatio(aspectRatio);
    //    }
    //}
}

void BMWidget::showEvent(QShowEvent *e)
{
    //if(!ogreRoot)
    //{
    //    initOgreSystem();
    //}

    QWidget::showEvent(e);
}

void BMWidget::wheelEvent(QWheelEvent *e)
{
    //Ogre::Vector3 zTranslation(0,0, -e->delta() / 60);

    //if(e->modifiers().testFlag(Qt::ControlModifier))
    //{
    //    zTranslation.z *= turboModifier;
    //}

    //const Ogre::Vector3 &actualCamPos = ogreCamera->getPosition();
    //setCameraPosition(actualCamPos + zTranslation);

    e->accept();
}

void BMWidget::initOgreSystem()
{
//    ogreRoot = new Ogre::Root();
//
//    Ogre::RenderSystem *renderSystem = ogreRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
//    ogreRoot->setRenderSystem(renderSystem);
//    ogreRoot->initialise(false);
//
//    ogreSceneManager = ogreRoot->createSceneManager(Ogre::ST_GENERIC);
//
//    Ogre::NameValuePairList viewConfig;
//    Ogre::String widgetHandle;
////#ifdef Q_WS_WIN
//    widgetHandle = Ogre::StringConverter::toString((size_t)((HWND)winId()));
////#else
////    QWidget *q_parent = dynamic_cast <QWidget *> (parent());
////    QX11Info xInfo = x11Info();
////
////    widgetHandle = Ogre::StringConverter::toString ((unsigned long)xInfo.display()) +
////        ":" + Ogre::StringConverter::toString ((unsigned int)xInfo.screen()) +
////        ":" + Ogre::StringConverter::toString ((unsigned long)q_parent->winId());
////#endif
//    viewConfig["externalWindowHandle"] = widgetHandle;
//    ogreRenderWindow = ogreRoot->createRenderWindow("Ogre rendering window",
//        width(), height(), false, &viewConfig);
//
//    ogreCamera = ogreSceneManager->createCamera("myCamera");
//    Ogre::Vector3 camPos(0, 50,150);
//    ogreCamera->setPosition(camPos);
//    ogreCamera->lookAt(0,50,0);
//    emit cameraPositionChanged(camPos);
//
//    ogreViewport = ogreRenderWindow->addViewport(ogreCamera);
//    ogreViewport->setBackgroundColour(Ogre::ColourValue(0,0,0));
//    ogreCamera->setAspectRatio(Ogre::Real(width()) / Ogre::Real(height()));
//
//    setupNLoadResources();
//    createScene();
}

void BMWidget::setupNLoadResources()
{
    // Load resource paths from config file
//    Ogre::ConfigFile cf;
//    cf.load("resources.cfg");
//
//    // Go through all sections & settings in the file
//    Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
//
//    Ogre::String secName, typeName, archName;
//    while (seci.hasMoreElements())
//    {
//        secName = seci.peekNextKey();
//        Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
//        Ogre::ConfigFile::SettingsMultiMap::iterator i;
//        for (i = settings->begin(); i != settings->end(); ++i)
//        {
//            typeName = i->first;
//            archName = i->second;
//#if OGRE_PLATFORM == OGRE_PLATFORM_APPLE
//            // OS X does not set the working directory relative to the app,
//            // In order to make things portable on OS X we need to provide
//            // the loading with it's own bundle path location
//            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
//                Ogre::String(macBundlePath() + "/" + archName), typeName, secName);
//#else
//            Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
//                archName, typeName, secName);
//#endif
//        }
//    }
//
//    // Initialise, parse scripts etc
//    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void BMWidget::createScene()
{
    //ogreSceneManager->setAmbientLight(Ogre::ColourValue(1,1,1));

    //Ogre::Entity *robotEntity = ogreSceneManager->createEntity("Robot", "robot.mesh");
    //Ogre::SceneNode *robotNode = ogreSceneManager->getRootSceneNode()->createChildSceneNode("RobotNode");
    //robotNode->attachObject(robotEntity);
    //robotNode->yaw(Ogre::Radian(Ogre::Degree(-90)));
}


