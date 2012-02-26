#ifndef WIDGET_H
#define WIDGET_H

#include <QtGui/QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QDebug>
#include <QListWidget>
#include "viewer.h"

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    Viewer *ogre;
    QListWidget *meshs, *animations;
    QHBoxLayout *mainLayout, *controlAnimation;
    QVBoxLayout *controls, *meshLayout, *resourceLayout, *animationLayout;
    QGroupBox *meshBox, *animationBox, *resourceBox;
    QPushButton *setResourcesFolder, *refresh, *stopAnimation;
    ~Widget();
public slots:
    void addMesh(QString name);
    void addAnimation(QString name);
    void startAnim();
    void stopAnim();
    void clearAnim();
    void clearMesh();
};

#endif // WIDGET_H
