#ifndef __Bullet_H__
#define __Bullet_H__

#include "cocos2d.h"
#include "Entity.h"
#include "DEFINE_TANK.h"

using namespace cocos2d;

class Bullet :public Entity {
public:
	Bullet();
	~Bullet();
	CREATE_FUNC(Bullet);
	virtual bool init();
	void show();
	void hide();
	bool isAlive();
	void setBulletDirection(int direction);
	void setBulletNum(int num);
	void setAlivefalse();
	int getBulletDirection();
	int getBulletNum();
	void update(float dt);

private:
	bool isalive;
	int bulletDirection;
	int bulletNum;
};

#endif