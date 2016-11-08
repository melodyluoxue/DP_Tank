#include "Entity.h"

Entity::Entity() {
	mySprite = NULL;
}

Entity::~Entity() {
}

Sprite* Entity::getSprite() {
	return this->mySprite;
}

void Entity::bindSprite(Sprite* sprite) {
	this->mySprite = sprite;
	this->addChild(mySprite);

	Size size = mySprite->getContentSize();
	mySprite->setPosition(Point(size.width*0.5f, size.height*0.5f));
	this->setContentSize(size);
}