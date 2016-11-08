#include "PlayerTank.h"

extern Vector<Wall* > wallVec;



PlayerTank::PlayerTank() {
	numLife = 3;
	tankKind = playerTank;
	tankDirection = Up;
	shoot = false;
	tankSpeed = 1;
	upSpeed = 0;
	downSpeed = 0;
	leftSpeed = 0;
	rightSpeed = 0;
}

PlayerTank::~PlayerTank() {
}

bool PlayerTank::init() {
	Size screenSize = Director::getInstance()->getVisibleSize();

	this->bindSprite(Sprite::create("Tank_up.png"));
	this->setAnchorPoint(ccp(0.5, 0.5));
	reset();

	newBullet = Bullet::create();
	newBullet->bindSprite(Sprite::create("bullet.png"));
	newBullet->setPosition(this->getPositionX(), this->getPositionY() + TANK_HEIGHT / 2);
	newBullet->hide();

	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(PlayerTank::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(PlayerTank::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	this->scheduleUpdate();
	newBullet->scheduleUpdate();

	return true;
}

Bullet* PlayerTank::getBullet(){
	return newBullet;
}

int PlayerTank::getTankDirection() {
	return tankDirection;
}

void PlayerTank::hit() {
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit.wav");
	--numLife;
	if (numLife == 0) {
		this->setVisible(false);
	}
	else {
		reset();
	}
}

int PlayerTank::getNumlife() {
	return numLife;
}

bool PlayerTank::isAlive() {
	return numLife > 0;
}

void PlayerTank::reset() {
	this->setPosition(421, 32);
}

void PlayerTank::setAliveFalse() {
	numLife = 0;
}

void PlayerTank::setNumLife(int num) {
	numLife = num;
}

void PlayerTank::setTankSpeed(int num) {
	tankSpeed = num;
}

int PlayerTank::getTankSpeed() {
	return tankSpeed;
}

void PlayerTank::update(float dt) {
	Size screenSize = Director::getInstance()->getVisibleSize();
	bool notup = false;
	bool notdown = false;
	bool notleft = false;
	bool notright = false;
	Rect tankup = Rect((this->getPositionX()) - 30, (this->getPositionY()) - 30 + tankSpeed, 60, 60);
	Rect tankdown = Rect((this->getPositionX()) - 30, (this->getPositionY()) - 30 - tankSpeed, 60, 60);
	Rect tankleft = Rect((this->getPositionX()) - 30 - tankSpeed, (this->getPositionY()) - 30, 60, 60);
	Rect tankright = Rect((this->getPositionX()) - 30 + tankSpeed, (this->getPositionY()) - 30, 60, 60);
	for (auto wall : wallVec)             //If playerTank bumps with the wall, it can't move towards the direction where there is a wall
	{
		Rect wallRect = wall->getBoundingBox();
		if (wallRect.intersectsRect(tankup)) {
			notup = true;
		}
		if (wallRect.intersectsRect(tankdown)) {
			notdown = true;
		}
		if (wallRect.intersectsRect(tankleft)) {
			notleft = true;
		}
		if (wallRect.intersectsRect(tankright)) {
			notright = true;
		}

	}
	if (this->isAlive()) {
		switch (tankDirection) {
		case Up:
			if ((this->getPositionY() + TANK_HEIGHT / 2<screenSize.height) && (upSpeed == 1) && (!notup)) {
				this->setPositionY(this->getPositionY() + tankSpeed);
			} break;
		case Down:
			if ((this->getPositionY() - TANK_HEIGHT / 2 > 0) && (downSpeed == 1) && (!notdown)) {
				this->setPositionY(this->getPositionY() - tankSpeed);
			} break;
		case Right:
			if ((this->getPositionX() + TANK_WIDTH / 2<screenSize.width) && (rightSpeed == 1) && (!notright)) {
				this->setPositionX(this->getPositionX() + tankSpeed);
			} break;
		case Left:
			if ((this->getPositionX() - TANK_WIDTH / 2 > 0) && (leftSpeed == 1) && (!notleft)) {
				this->setPositionX(this->getPositionX() - tankSpeed);
			} break;
		}
	}
}

void  PlayerTank::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_W: {this->turn(Up); tankDirection = Up; upSpeed = 1; break; }
	case EventKeyboard::KeyCode::KEY_S: {this->turn(Down); tankDirection = Down; downSpeed = 1; break; }
	case EventKeyboard::KeyCode::KEY_A: {this->turn(Left); tankDirection = Left; leftSpeed = 1; break; }
	case EventKeyboard::KeyCode::KEY_D: {this->turn(Right); tankDirection = Right; rightSpeed = 1; break; }
	case EventKeyboard::KeyCode::KEY_J: {
        if ((this->isAlive()) && (!newBullet->isAlive())) {
			shoot = true;
			newBullet->setBulletDirection(tankDirection);
			switch (newBullet->getBulletDirection()) {
			case Up:   newBullet->setPosition(Point(this->getPositionX(), this->getPositionY() + 1)); break;
			case Down: newBullet->setPosition(Point(this->getPositionX(), this->getPositionY() - 1)); break;
			case Right:newBullet->setPosition(Point(this->getPositionX() + 1, this->getPositionY())); break;
			case Left: newBullet->setPosition(Point(this->getPositionX() - 1, this->getPositionY())); break;
			}
		}
		newBullet->show();
	}
	default:break;
	}
}

void  PlayerTank::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
	switch (keyCode) {
	case EventKeyboard::KeyCode::KEY_W: { upSpeed = 0; break; }
	case EventKeyboard::KeyCode::KEY_S: { downSpeed = 0; break; }
	case EventKeyboard::KeyCode::KEY_A: { leftSpeed = 0; break; }
	case EventKeyboard::KeyCode::KEY_D: { rightSpeed = 0; break; }
	case EventKeyboard::KeyCode::KEY_J: { shoot = false; break; }
	}
}
