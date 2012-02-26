#include "viewer.h"

Viewer::Viewer(QWidget *parent) :
    OgreWidget(parent)
{
    clickMidButton=animationed=false;
    count=camAngle=0;
    scale=1000;
    mainEnt = 0;
    dt=curTime=oldTime=0;
    animState=0;
    timeFrame.start();
}

void Viewer::createScene()
{
    ogreRoot->loadPlugin("Plugin_BSPSceneManager");
    ogreRoot->loadPlugin("Plugin_CgProgramManager");
    ogreRoot->loadPlugin("Plugin_OctreeSceneManager");
//    ogreRoot->loadPlugin("Plugin_OctreeZone");
    ogreRoot->loadPlugin("Plugin_ParticleFX");
    ogreRoot->loadPlugin("Plugin_PCZSceneManager");
    loadResourses();
    Ogre::Vector3 lightdir(-0.55, -0.3, -0.75);
    lightdir.normalise();
    Ogre::Light* light = ogreSceneManager->createLight("tstLight");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(lightdir);
    light->setDiffuseColour(Ogre::ColourValue::White);
    light->setSpecularColour(Ogre::ColourValue(0.4, 0.4, 0.4));
    ogreSceneManager->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
    ogreCamera = ogreSceneManager->createCamera("myCamera");
    ogreCamera->setPosition(Ogre::Vector3(0,0,0));
    ogreCamera->lookAt(Ogre::Vector3(0,0,0));
    ogreCamera->setNearClipDistance(0.1);
    ogreCamera->setFarClipDistance(50000);


if (ogreRoot->getRenderSystem()->getCapabilities()->hasCapability(Ogre::RSC_INFINITE_FAR_PLANE))
    {
        ogreCamera->setFarClipDistance(0);   // enable infinite far clip distance if we can
    }
ogreViewport = ogreRenderWindow->addViewport(ogreCamera);
setBackgroundColor(QColor(100,100,100));

ogreCamera->setAspectRatio(Ogre::Real(this->parentWidget()->width()) / Ogre::Real(this->parentWidget()->height()));
    Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);

    Ogre::MeshManager::getSingleton().createPlane("ground", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
        plane, 1500, 1500, 5, 5, true, 1, 30, 30, Ogre::Vector3::UNIT_Z);

    Ogre::Entity* entGround = ogreSceneManager->createEntity("GroundEntity", "ground");
    ogreSceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(entGround);

    entGround->setMaterialName("Examples/Rockwall");
    entGround->setCastShadows(false);
    ogreCamNode = ogreSceneManager->getRootSceneNode()->createChildSceneNode("CamNode1");
    ogreCamNode->attachObject(ogreCamera);
    mainNode = ogreSceneManager->getRootSceneNode()->createChildSceneNode("MainNode");
    updateCamPos();

//    Ogre::ResourceGroupManager::getSingleton().unloadUnreferencedResourcesInGroup("General",true);
//    Ogre::ResourceGroupManager::getSingleton().unloadUnreferencedResourcesInGroup("Popular",true);
//    Ogre::ResourceGroupManager::getSingleton().unloadUnreferencedResourcesInGroup("Essential",true);
}

void Viewer::loadResourses()
{
#if defined(Q_WS_WIN)
      Ogre::ConfigFile cf;
      cf.load("resources.cfg");
#endif

#if defined(Q_WS_X11)
      Ogre::ConfigFile cf;
      cf.load("/usr/share/OGRE/resources.cfg");
#endif

      // Go through all sections & settings in the file
      Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
      Ogre::String secName, typeName, archName;
      while (seci.hasMoreElements())
      {
          secName = seci.peekNextKey();
          Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
          Ogre::ConfigFile::SettingsMultiMap::iterator i;
          for (i = settings->begin(); i != settings->end(); ++i)
          {
              typeName = i->first;
              archName = i->second;
              Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                  archName, typeName, secName);
          }
      }
      Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void Viewer::updateCamPos()
{
    ogreCamNode->setPosition(Ogre::Vector3(0, 0, 0));
    ogreCamera->setPosition(Ogre::Vector3(1, 1, 1)*scale);
    ogreCamera->lookAt(ogreCamNode->getPosition());

}

void Viewer::mousePressEvent(QMouseEvent *e)
{
//    if(e->button()==Qt::LeftButton)
//    {
//        Ogre::Ray ray;
//        ogreCamera->getCameraToViewportRay((Ogre::Real)e->x()/this->width(),(Ogre::Real)e->y()/this->height(),&ray);
//        Ogre::Vector3 finishPos=mTerrainGroup->rayIntersects(ray).position;
//        ogreCamNode->lookAt(Ogre::Vector3(finishPos.x,ogreCamNode->getPosition().y,finishPos.z),Ogre::SceneNode::TS_PARENT);
//        mainChar->finishPos=finishPos;
//        updateCamPos();
//    }
//    else
    if(e->button()==Qt::MidButton)
    {
        oldMouseX=e->x();
        clickMidButton=true;
    }
    updateGL();
    e->accept();
}

void Viewer::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button()==Qt::MidButton)
    {
        clickMidButton=false;
    }
}

void Viewer::wheelEvent(QWheelEvent *e)
{
    if(scale>10 || (scale<=10 && e->delta()<0))
    {
        scale-=10*e->delta()/abs(e->delta());
        updateCamPos();
    }
    updateGL();
}

void Viewer::mouseMoveEvent(QMouseEvent *e)
{
    if(clickMidButton)
    {
        int mouseX=e->x();
        if((oldMouseX-mouseX)<0)
        {
            camAngle=-2*3.14/90.0;
        }
        else
            if((oldMouseX-mouseX)>0)
            {
                camAngle=2*3.14/90.0;
            }
        ogreCamNode->rotate(Ogre::Vector3(0,1,0),Ogre::Radian(camAngle));
        oldMouseX=mouseX;
        updateCamPos();
        updateGL();
    }

}

void Viewer::loadMeshList()
{
    emit clearMesh();
    Ogre::StringVector groups = Ogre::ResourceGroupManager::getSingleton().getResourceGroups();
    for (size_t i = 0; i < groups.size(); i++)
    {
        Ogre::StringVector names = *Ogre::ResourceGroupManager::getSingleton().listResourceNames(groups[i]).get();
        for (size_t j=0; j < names.size(); j++)
        {
            size_t pos = names[j].find(".mesh");
            if (pos <= names[j].size())
            {
                emit sendMeshName(names[j].c_str());
            }
        }
    }
}

void Viewer::createMesh(QListWidgetItem *item)
{
    animationed=false;
    if(animState != 0)
    {
        animState->setEnabled(false);
        animState=0;
    }
    mainNode->detachAllObjects();
    if(mainEnt != 0)
    {
        ogreSceneManager->destroyEntity(mainEnt->getName());
        mainEnt=0;
    }
    mainEnt = ogreSceneManager->createEntity(item->text().toAscii().constData(), item->text().toAscii().constData());
    mainEnt->setCastShadows(true);
    mainNode->attachObject(mainEnt);
    Ogre::Real CHAR_HEIGHT=mainEnt->getBoundingBox().getMinimum().y;
    Ogre::Vector3 pos = mainNode->getPosition();
    if (CHAR_HEIGHT < 0)
    {
        // if we've hit the ground, change to landing state
        pos.y = -CHAR_HEIGHT;
        mainNode->setPosition(pos);
    }
    else
    {
        pos.y = CHAR_HEIGHT;
        mainNode->setPosition(pos);
    }
    emit clearAnim();
    Ogre::AnimationStateSet *set=mainEnt->getAllAnimationStates();
    if(set != 0)
    {
        Ogre::AnimationStateIterator seci = set->getAnimationStateIterator();
        while (seci.hasMoreElements())
        {
            Ogre::AnimationState *anim=seci.getNext();
            emit sendAnimName(anim->getAnimationName().c_str());
        }
        set=0;
    }
    updateGL();
}

void Viewer::startAnimation(QListWidgetItem *item)
{
    if(animState != 0)
        animState->setEnabled(false);
    QString name=item->text();
    if(!name.isEmpty())
    {
        animState=mainEnt->getAnimationState(name.toAscii().constData());
        animState->setEnabled(true);
        animState->setLoop(true);
        animationed=true;
    }
}

void Viewer::renderFrame()
{
    curTime=timeFrame.elapsed();
    dt=curTime-oldTime;
    if(animationed)
    {
        animState->addTime((double)dt/1000);
    }
    oldTime=curTime;
}

void Viewer::stopAnimation()
{
    if(animState != 0)
        animState->setEnabled(false);
    animationed=false;
    animState=0;
}
