#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene() {
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init() {   //CHANGED
    if ( !Layer::init() ) {
        return false;
    }
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* backGround = Sprite::create("GameScene.png");
	backGround->setAnchorPoint(ccp(0.5, 0.5));
	backGround->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(backGround);

	Button* startBtn = Button::create("startBtn.png");
	startBtn->setAnchorPoint(ccp(0.5, 0.5));
	startBtn->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 50));
	startBtn->addTouchEventListener(this, toucheventselector(GameScene::showScreen));
	this->addChild(startBtn);

	Button* helpBtn = Button::create("helpBtn.png");
	helpBtn->setAnchorPoint(ccp(0.5, 0.5));
	helpBtn->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2 - 150));
	helpBtn->addTouchEventListener(this, toucheventselector(HelpScene::comeToHelpScene));
	this->addChild(helpBtn);

    return true;
}