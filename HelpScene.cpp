#include "HelpScene.h"

Scene* HelpScene::createScene() {
	auto scene = Scene::create();
	auto layer = HelpScene::create();
	scene->addChild(layer);
	return scene;
}

bool HelpScene::init() {
	Size screenSize = Director::getInstance()->getVisibleSize();

	Sprite* helpScene = Sprite::create("HelpScene.png");
	helpScene->setAnchorPoint(ccp(0.5, 0.5));
	helpScene->setPosition(Point(screenSize.width / 2, screenSize.height / 2));
	this->addChild(helpScene);

	Button* backBtn = Button::create("backBtn.png");
	backBtn->setAnchorPoint(ccp(0, 0));
	backBtn->setPosition(Point(0, 0));
	backBtn->addTouchEventListener(this, toucheventselector(HelpScene::backToHelloWorldScene));
	this->addChild(backBtn);

	Button* toughTntro = Button::create("next.png");
	toughTntro->setAnchorPoint(ccp(0.5, 0.5));
	toughTntro->setPosition(Point(screenSize.width - 100, 100));
	toughTntro->addTouchEventListener(this, toucheventselector(HelpScene::goToNextPage));
	this->addChild(toughTntro);

	return true;
}

void HelpScene::comeToHelpScene(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		Director::getInstance()->pushScene(HelpScene::createScene());
	}
}

void HelpScene::backToHelloWorldScene(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		Director::getInstance()->popScene();
	}
}

void HelpScene::goToNextPage(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		Director::getInstance()->replaceScene(HelpScene2::createScene());
	}
}