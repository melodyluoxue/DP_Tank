#ifndef __Tank_H__
#define __Tank_H__

#include "DEFINE_TANK.h"
#include "cocos2d.h"
#include "Entity.h"
#include "Wall.h"

using namespace cocos2d;

class Tank :public Entity {
public:
	Tank();
	~Tank();
	virtual bool init();
	void turn(int tankdirection);
	bool isCollideWithWall(Wall* wall);

};

#endif