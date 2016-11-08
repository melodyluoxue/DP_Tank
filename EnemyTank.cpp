#include "EnemyTank.h"

extern Vector<Wall* > wallVec;
extern Vector<Bullet* > bulletVec;
extern bool isGameOver;
extern bool haveWin;

int EnemyTank::EnenmyTankNum = 0;

EnemyTank::EnemyTank()  {
	numLife = 3;
	tankKind = enemyTank;
	tankDirection = Down;
	playTime = 0;
	EnenmyTankNum += 1; 
	tankSpeed = 1;
	changeFeq = 60;
}

EnemyTank::~EnemyTank() {
}

bool EnemyTank::init() {
	Size screenSize = Director::getInstance()->getVisibleSize();
	this->setAnchorPoint(ccp(0.5, 0.5));
	this->scheduleUpdate();
	return true;
}

int EnemyTank::getTankDirection() {
	return tankDirection;
}

void EnemyTank::hit(int num) {
	if (numLife) {
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("hit.wav");
		--numLife;
		if (numLife == 0) {
			this->setVisible(false);
		}
		else {
			reset(num);
		}
	}
}

bool EnemyTank::isAlive() {
	return numLife > 0;
}

void EnemyTank::setTankNum(int num) {
	tankNum = num;
}

int EnemyTank::getTankNum() {
	return tankNum;
}

void EnemyTank::setTankSpeed(int spd) {
	tankSpeed = spd;
}

void EnemyTank::setChangeFeq(int feq) {
	changeFeq = feq;
}

void EnemyTank::setNumLife(int num) {
	numLife = num;
}

void EnemyTank::reset(int num) {
	Size screenSize = Director::getInstance()->getVisibleSize();
	
	switch (num) {
	case 1:  this->setPosition(30, screenSize.height - 30); break;
	case 2:  this->setPosition(screenSize.width / 2, screenSize.height - 30); break;
	case 3:  this->setPosition(screenSize.width - 30, screenSize.height - 30); break;
	default: break;
	}
}

void EnemyTank::shootFrom(EnemyTank* enemy_tank) {
	Size screenSize = Director::getInstance()->getVisibleSize();

	for (auto bullet : bulletVec) {
		if ((!bullet->isAlive()) && ((bullet->getBulletNum()) == (enemy_tank->getTankNum())) && (this->isAlive())) {

			bullet->setPosition(enemy_tank->getPositionX(), enemy_tank->getPositionY());
			bullet->setBulletDirection(enemy_tank->getTankDirection());
			bullet->show();
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("fire.wav");
		}
		else if (bullet->isAlive()) {
			int dx = 0, dy = 0;
			switch (bullet->getBulletDirection()) {
			case Left: dx = -1; break;
			case Right:dx = 1; break;
			case Up:   dy = 1; break;
			case Down: dy = -1; break;
			}
			bullet->setPositionX(bullet->getPositionX() + dx);
			bullet->setPositionY(bullet->getPositionY() + dy);
			if ((bullet->getPositionY() < 0) || (bullet->getPositionY() > screenSize.height) ||
				(bullet->getPositionX() < 0) || (bullet->getPositionX() > screenSize.width)){
				bullet->hide();
			}
		}
	}
}

void EnemyTank::update(float dt) {
	if ((!isGameOver) && (!haveWin)) {
		Size screenSize = Director::getInstance()->getVisibleSize();
		playTime += 1;
		if (this->isAlive()) {
			int flag = 0;
			for (auto wall : wallVec) {
				if (isCollideWithWall(wall)) {
					flag = 1; break;
				}
			}
			if (flag) {
				switch (tankDirection) {
				case Up:    this->turn(Up); tankDirection = Down;  break;     //The turnUp function regards the initial direction is Up, 
				case Down:  this->turn(Down); tankDirection = Up; break;      //but enemyTank's initial direction is Down, so we change the direction
				case Left:  this->turn(Left); tankDirection = Right; break;
				case Right: this->turn(Right); tankDirection = Left; break;
				}
			}

			if (!(playTime % changeFeq) && (!flag)) {
				int changeDirection = rand() % 4;
				switch (changeDirection) {
				case Up:    this->turn(Up); tankDirection = Down;  break;     //The turnUp function regards the initial direction is Up, 
				case Down:  this->turn(Down); tankDirection = Up; break;      //but enemyTank's initial direction is Down, so we change the direction
				case Left:  this->turn(Left); tankDirection = Right; break;
				case Right: this->turn(Right); tankDirection = Left; break;
				}
			}
			switch (tankDirection) {           //Don't let the tank goes out of the screen
			case Up:    if (this->getPositionY() + TANK_HEIGHT / 2<screenSize.height) { this->setPositionY(this->getPositionY() + tankSpeed); }break;
			case Down:  if (this->getPositionY() - TANK_HEIGHT / 2 > 0){ this->setPositionY(this->getPositionY() - tankSpeed); } break;
			case Right: if (this->getPositionX() + TANK_WIDTH / 2<screenSize.width) { this->setPositionX(this->getPositionX() + tankSpeed); }break;
			case Left:  if (this->getPositionX() - TANK_WIDTH / 2 > 0){ this->setPositionX(this->getPositionX() - tankSpeed); }break;
			}
		}
	}
}
