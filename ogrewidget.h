#ifndef OGREWIDGET_H
#define OGREWIDGET_H

#include <Ogre.h>
#include <OgreConfigFile.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>
#include <QGLWidget>
#include <QTime>
#include <iostream>

#ifdef Q_WS_X11
  #include <QtGui/QX11Info>
#endif

#include <QDebug>

class OgreWidget : public QGLWidget
{
    Q_OBJECT

public:
    OgreWidget(QWidget *parent = 0);
    ~OgreWidget();
    Ogre::SceneNode *ogreCamNode;
    Ogre::SceneNode *ogreCamNodeLook;
    Ogre::Root          *ogreRoot;
    Ogre::SceneManager *ogreSceneManager;
    Ogre::RenderWindow *ogreRenderWindow;
    Ogre::Viewport      *ogreViewport;
    Ogre::Camera        *ogreCamera;

public slots:
    void setBackgroundColor(QColor c);

protected:
//    virtual void moveEvent(QMoveEvent *e);
//    virtual QPaintEngine* paintEngine() const;
//    virtual void paintEvent(QPaintEvent *e);
//    virtual void resizeEvent(QResizeEvent *e);
//    virtual void showEvent(QShowEvent *e);
    virtual void createScene();
    virtual void initializeGL();
    virtual void resizeGL( int, int );
    virtual void paintGL();
virtual void renderFrame();

private:
    virtual void createOgreRoot();


private:


signals:


};

#endif // OGREWIDGET_H
