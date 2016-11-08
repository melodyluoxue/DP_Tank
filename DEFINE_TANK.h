#ifndef __DEFINE_TANK_H__
#define __DEFINE_TANK_H__

#include "cocos2d.h"
using namespace cocos2d;
USING_NS_CC;

const float TANK_HEIGHT = 60;
const float TANK_WIDTH = 60;

typedef enum tankKind {
	enemyTank,
	playerTank
}TANK_KIND;

typedef enum tankDirection {
	Up,
	Down,
	Left,
	Right
}TANK_DIRECTION;

#endif
