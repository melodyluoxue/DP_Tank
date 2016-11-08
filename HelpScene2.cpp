#include "HelpScene2.h"

Scene* HelpScene2::createScene() {
	auto scene = Scene::create();
	auto layer = HelpScene2::create();
	scene->addChild(layer);
	return scene;
}

bool HelpScene2::init() {
	Size screenSize = Director::getInstance()->getVisibleSize();

	Sprite* helpScene2 = Sprite::create("HelpScene2.png");
	helpScene2->setAnchorPoint(ccp(0.5, 0.5));
	helpScene2->setPosition(Point(screenSize.width / 2, screenSize.height / 2));
	this->addChild(helpScene2);

	Button* backBtn = Button::create("backBtn.png");
	backBtn->setAnchorPoint(ccp(0, 0));
	backBtn->setPosition(Point(0, 0));
	backBtn->addTouchEventListener(this, toucheventselector(HelpScene::backToHelloWorldScene));
	this->addChild(backBtn);

	return true;
}