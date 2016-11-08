#include "Tank.h"

Tank::Tank() {
}

Tank::~Tank() {
}

bool Tank::init() {
	return true;
}

void Tank::turn(int tankdirection) {
	switch (tankdirection) {
	case Up:   this->setRotation(0); break;
	case Down: this->setRotation(180); break;
	case Left: this->setRotation(-90); break;
	case Right:this->setRotation(90); break;
	}
}

bool Tank::isCollideWithWall(Wall* wall) {
	Rect entityRect = wall->getBoundingBox();
	Rect tankPos = this->getBoundingBox();
	return tankPos.intersectsRect(entityRect);
}