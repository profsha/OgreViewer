#ifndef VIEWER_H
#define VIEWER_H

#include <QtGui>
#include "ogrewidget.h"

class Viewer : public OgreWidget
{
    Q_OBJECT
public:
    explicit Viewer(QWidget *parent = 0);
    Ogre::Entity* mainEnt;
    Ogre::SceneNode *mainNode;

protected:
    virtual void createScene();
    int scale, oldMouseX;
    double camAngle;
    int count;
    bool clickMidButton, animationed;
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *e);
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void wheelEvent(QWheelEvent *e);
    virtual void renderFrame();
    Ogre::AnimationState *animState;
    QTime timeFrame;
    int curTime, oldTime, dt;
    
signals:
    void sendMeshName(QString name);
    void sendAnimName(QString name);
    void clearAnim();
    void clearMesh();
    
public slots:
    void loadResourses();
    void createMesh(QListWidgetItem * item);
    void startAnimation(QListWidgetItem * item);
    void stopAnimation();
    void loadMeshList();
    void updateCamPos();
    
};

#endif // VIEWER_H
