#include <QtGui/QApplication>
#include <QTimer>
#include <QTextCodec>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    Widget w;
    Viewer *ogre;
    ogre=new Viewer;
    w.ogre=ogre;
    QObject::connect(w.refresh,SIGNAL(clicked()),ogre,SLOT(loadMeshList()));
    QObject::connect(ogre,SIGNAL(sendMeshName(QString)),&w,SLOT(addMesh(QString)));
    QObject::connect(w.meshs,SIGNAL(itemDoubleClicked(QListWidgetItem*)),ogre,SLOT(createMesh(QListWidgetItem*)));
    QObject::connect(w.animations,SIGNAL(itemDoubleClicked(QListWidgetItem*)),ogre,SLOT(startAnimation(QListWidgetItem*)));
    QObject::connect(w.animations,SIGNAL(itemDoubleClicked(QListWidgetItem*)),&w,SLOT(startAnim()));
    QObject::connect(ogre,SIGNAL(sendAnimName(QString)),&w,SLOT(addAnimation(QString)));
    QObject::connect(w.stopAnimation,SIGNAL(clicked()),ogre,SLOT(stopAnimation()));
    QObject::connect(w.stopAnimation,SIGNAL(clicked()),&w,SLOT(stopAnim()));
    QObject::connect(ogre,SIGNAL(clearAnim()),&w,SLOT(clearAnim()));
    QObject::connect(ogre,SIGNAL(clearMesh()),&w,SLOT(clearMesh()));
    w.mainLayout->addWidget(ogre,10);
    w.mainLayout->addLayout(w.controls,2);
    w.resize(800,600);
    w.show();
    QTimer timer;
    QObject::connect(&timer,SIGNAL(timeout()),ogre,SLOT(updateGL()));
    timer.start(10);
    return a.exec();
}
