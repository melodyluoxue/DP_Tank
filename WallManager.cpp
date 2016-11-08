#include "WallManager.h"

bool WallManager::init() {
	return true;
}

void WallManager::createWalls(Vector<Wall*>& wallVec,int num) {
	Wall* newWall = NULL;
	if (wallVec.size()) {                        //If player has entered more than one time ,we need to clear the vector of wall
		wallVec.clear();
	}
	for (int i = 0; i < num; i++) {                //create walls
		newWall = Wall::create();
		newWall->bindSprite(Sprite::create("wall.png"));
		newWall->setWall(wallVec.size());
		newWall->setAnchorPoint(ccp(0.5, 0.5));

		this->addChild(newWall);
		wallVec.pushBack(newWall);
	}
}

