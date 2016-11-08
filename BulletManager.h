#ifndef __BulletManager_H__
#define __BulletManager_H__

#include "cocos2d.h"
#include "Bullet.h"
USING_NS_CC;

#define MAX_BULLET_NUM 3   //set the max count of bullet,but just enemy's bullet

class BulletManager : public Node {
public:
	CREATE_FUNC(BulletManager);
	virtual bool init();
	void createBullets(Vector<Bullet*>& bulletVec);

};

#endif