#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h" //ADDED
#include "GameScene.h"
#include "HelpScene.h"

using namespace cocos2d::ui;
using namespace cocos2d;

class HelloWorld : public Layer {
public:
    static Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(HelloWorld);

};

#endif
