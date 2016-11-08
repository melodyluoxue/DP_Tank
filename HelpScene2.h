#ifndef __HelpScene2_H__
#define __HelpScene2_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HelpScene.h"

using namespace cocos2d::ui;
using namespace cocos2d;

class HelpScene2 :public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelpScene2);
};

#endif