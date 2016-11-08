#ifndef __EnemyTank_H__
#define __EnemyTank_H__

#include "Tank.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"

class EnemyTank :public Tank {
public:
	CREATE_FUNC(EnemyTank);
	EnemyTank();
	~EnemyTank();
	virtual bool init();
	void update(float dt);
	int getTankDirection();
	void hit(int num);
	bool isAlive();
	int getTankNum();
	void setTankNum(int num);
	void reset(int num);
	void shootFrom(EnemyTank* enemy_tank);
	void setNumLife(int num);
	void setTankSpeed(int spd);
	void setChangeFeq(int feq);

private:
	static int EnenmyTankNum;
	int numLife;
	TANK_KIND tankKind;
	TANK_DIRECTION tankDirection;
	int playTime;
	int tankNum;
	int tankSpeed;
	int changeFeq;

};

#endif