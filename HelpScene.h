#ifndef __HelpScene_H__
#define __HelpScene_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HelpScene2.h"

using namespace cocos2d::ui;
using namespace cocos2d;

class HelpScene :public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(HelpScene);
	void comeToHelpScene(Ref*, TouchEventType type);
	void backToHelloWorldScene(Ref*, TouchEventType type);
	void goToNextPage(Ref*, TouchEventType type);
};

#endif