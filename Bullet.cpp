#include "Bullet.h"

Bullet::Bullet() {
	this->hide();
}

Bullet::~Bullet() {
}

bool Bullet::init() {
	return true;
}

void Bullet::show() {
	setVisible(true);
	isalive = true;
}

void Bullet::hide() {
	setVisible(false);
	isalive = false;
}

void Bullet::setAlivefalse(){
	isalive = false;
}

bool Bullet::isAlive() {
	return isalive;
}

int Bullet::getBulletDirection() {
	return bulletDirection;
}

int Bullet::getBulletNum() {
	return bulletNum;
}

void Bullet::setBulletDirection(int direction) {
	bulletDirection = direction;
}

void Bullet::setBulletNum(int num) {
	bulletNum = num;
}

void Bullet::update(float dt){
	Size screenSize = Director::getInstance()->getVisibleSize();

	switch (getBulletDirection()) {      //Here just limit the tank in the screen, the bump with wall or tank is wrote in the GameScene's update
	case Up:   if (this->getPositionY() < screenSize.height + 17) { this->setPositionY(this->getPositionY() + 10); }
			   else{ this->setAlivefalse(); }break;
	case Down: if (this->getPositionY() > -17){ this->setPositionY(this->getPositionY() - 10); }
			   else{ this->setAlivefalse(); }break;
	case Right:if (this->getPositionX() < screenSize.width + 17){ this->setPositionX(this->getPositionX() + 10); }
			   else{ this->setAlivefalse(); }break;
	case Left: if (this->getPositionX() > -17){ this->setPositionX(this->getPositionX() - 10); }
			   else{ this->setAlivefalse(); }break;
	}
	
}
