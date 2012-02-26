#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{


    mainLayout = new QHBoxLayout;

    controls = new QVBoxLayout;

    resourceLayout = new QVBoxLayout;
    setResourcesFolder = new QPushButton(tr("Список папок"));
    refresh = new QPushButton(tr("Обновить"));
    resourceLayout->addWidget(setResourcesFolder);
    resourceLayout->addWidget(refresh);
    resourceBox = new QGroupBox(tr("Управление ресурсами"));
    resourceBox->setLayout(resourceLayout);

    meshs = new QListWidget;
    meshLayout = new QVBoxLayout;
    meshBox = new QGroupBox(tr("Список мэшей"));
    meshLayout->addWidget(meshs);
    meshBox->setLayout(meshLayout);

    animations = new QListWidget;
    animationLayout = new QVBoxLayout;
    animationBox = new QGroupBox(tr("Список анимаций"));
    controlAnimation = new QHBoxLayout;
    stopAnimation = new QPushButton(tr("Остановить"));
    stopAnimation->setEnabled(false);
    animationLayout->addWidget(animations);
    controlAnimation->addWidget(stopAnimation);
    animationLayout->addLayout(controlAnimation);
    animationBox->setLayout(animationLayout);

    controls->addWidget(meshBox);
    controls->addWidget(animationBox);
    controls->addWidget(resourceBox);
    this->setLayout(mainLayout);

}

Widget::~Widget()
{
    delete meshs;
    delete meshLayout;
    delete meshBox;

    delete animations;
    delete stopAnimation;
    delete controlAnimation;
    delete animationLayout;
    delete animationBox;

    delete setResourcesFolder;
    delete refresh;
    delete resourceLayout;
    delete resourceBox;

    delete controls;
    delete mainLayout;
}

void Widget::addMesh(QString name)
{
    meshs->addItem(name);
}

void Widget::addAnimation(QString name)
{
    animations->addItem(name);
}

void Widget::clearAnim()
{
    animations->clear();
}

void Widget::clearMesh()
{
    meshs->clear();
}

void Widget::startAnim()
{
    stopAnimation->setEnabled(true);
}
void Widget::stopAnim()
{
    stopAnimation->setEnabled(false);
}
