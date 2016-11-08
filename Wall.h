#ifndef __Wall_H__
#define __Wall_H__

#include "cocos2d.h"
#include "Entity.h"
using namespace cocos2d;

class Wall :public Entity{
public:
	Wall();
	~Wall();
	CREATE_FUNC(Wall);
	virtual bool init();
	void setWall(int num);

};

#endif