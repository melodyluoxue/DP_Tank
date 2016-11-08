#ifndef __PlayerTank_H__
#define __PlayerTank_H__

#include "Tank.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"

class PlayerTank :public Tank {
public:
	CREATE_FUNC(PlayerTank);
	PlayerTank();
	~PlayerTank();
	virtual bool init();
	void update(float dt);
	int getTankDirection();
	void hit();
	bool isAlive();
	void reset();
	Bullet* getBullet();
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void setAliveFalse();
	int getNumlife();
	void setNumLife(int num);
	void setTankSpeed(int num);
	int getTankSpeed();

private:
	int numLife;
	TANK_KIND tankKind;
	TANK_DIRECTION tankDirection;
	Bullet* newBullet;
	bool shoot;
	int tankSpeed;
	int upSpeed;
	int downSpeed;
	int leftSpeed;
	int rightSpeed;

};

#endif