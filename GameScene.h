#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

#include "BulletManager.h"
#include "WallManager.h"
#include "HelloWorldScene.h"
#include "EnemyTank.h"
#include "PlayerTank.h"

using namespace cocos2d::ui;
using namespace cocos2d;
using namespace cocos2d::extension;

class GameScene :public Layer {
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameScene);
	void showScreen(Ref*,TouchEventType type);
	void backToHelloWorldScene(Ref*, TouchEventType type);
	void toughMode(Ref*, TouchEventType type);
	void update(float dt);
	void gameOver();
	void win();
	void tankBorn(int num);
	Animate* createAnimate();
	void bulletHitTheWall();
	void bulletHitTheTank();
	void skeletonBorn();

private:
	PlayerTank* playerTank;
	Bullet* playerBullet;
	EnemyTank* enemyTankLeft;
	EnemyTank* enemyTankMiddle;
	EnemyTank* enemyTankRight;
	bool isToughMode;
	int playTime;
	
};

#endif