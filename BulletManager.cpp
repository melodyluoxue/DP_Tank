#include "BulletManager.h"

bool BulletManager::init() {
	this->scheduleUpdate();
	return true;
}

void BulletManager::createBullets(Vector<Bullet*>& bulletVec) {
	Size screen_size = Director::getInstance()->getVisibleSize();
	Bullet* bullet = NULL;
	Sprite* sprite = NULL;
	if (bulletVec.size()) {          //If player has entered more than one time ,we need to clear the vector of bullet
		bulletVec.clear();
	}
	for (int i = 0; i < MAX_BULLET_NUM; i++) {
		bullet = Bullet::create();
		bullet->bindSprite(Sprite::create("bullet.png"));
		bullet->setAnchorPoint(ccp(0.5, 0.5));
		bullet->setBulletNum(i + 1);
		this->addChild(bullet);
		bulletVec.pushBack(bullet);
	}
}