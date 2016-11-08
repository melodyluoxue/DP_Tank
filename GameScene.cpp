#include "GameScene.h"

bool haveWin;               //There are two external variables,
bool isGameOver;            //if player wins or game over, EnemyTank's update and GameScene's update need to stop.
Vector<Wall*> wallVec;
Vector<Bullet*> bulletVec;  //It just store the enemyTanks' bullets
Vector<EnemyTank*> skeletonVec;

Scene* GameScene::createScene() {
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init() {
	Size screenSize = Director::getInstance()->getVisibleSize();

	BulletManager* bulletMgr = BulletManager::create();        //Initiate the enemyBullets
	bulletMgr->createBullets(bulletVec);
	this->addChild(bulletMgr);

	WallManager* wallMgr = WallManager::create();              //Initiate the walls
	wallMgr->createWalls(wallVec, 96);
	this->addChild(wallMgr);
	wallMgr->setTag(4);

	Button* backBtn = Button::create("back.png");
	backBtn->setAnchorPoint(ccp(0, 0));
	backBtn->setPosition(Point(0, 0));
	backBtn->addTouchEventListener(this, toucheventselector(GameScene::backToHelloWorldScene));
	this->addChild(backBtn);

	isToughMode = false;
	Button* toughBtn = Button::create("tough.png");
	toughBtn->setAnchorPoint(ccp(1, 0));
	toughBtn->setPosition(Point(screenSize.width, 0));
	toughBtn->addTouchEventListener(this, toucheventselector(GameScene::toughMode));
	this->addChild(toughBtn);

	Wall* symbol = Wall::create();
	symbol->bindSprite(Sprite::create("symbol.png"));
	symbol->setAnchorPoint(ccp(0.5, 0.5));
	symbol->setPosition(Point(482 + 60 / 2, 45 / 2));   //The "symbol.png" is 60*45
	this->addChild(symbol);
	symbol->setTag(3);
	
	enemyTankLeft = EnemyTank::create();
	this->addChild(enemyTankLeft);
	tankBorn(1);
	
	enemyTankMiddle = EnemyTank::create();
	this->addChild(enemyTankMiddle);
	tankBorn(2);

	enemyTankRight = EnemyTank::create();
	this->addChild(enemyTankRight);
	tankBorn(3);

	playerTank = PlayerTank::create();
	this->addChild(playerTank);
	this->addChild(playerTank->getBullet());
	playerTank->setTag(2);

	playerBullet = playerTank->getBullet();
	playerBullet->setAnchorPoint(ccp(0.5, 0.5));
	haveWin = false;

	playTime = 0;
	skeletonVec.clear();        //If player has entered more than one time ,we need to clear the vector of skeleton
	isGameOver = false;

	this->scheduleUpdate();

	return true;
}

void GameScene::showScreen(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		Director::getInstance()->pushScene(GameScene::createScene());
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("start.wav", false);
	}
}

void GameScene::backToHelloWorldScene(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		Director::getInstance()->popScene();
	}
}

void GameScene::toughMode(Ref*, TouchEventType type) {
	if (type == TouchEventType::TOUCH_EVENT_ENDED) {
		if (!isToughMode){
			isToughMode = true;
			enemyTankLeft->reset(1);                  //The number "1" is uesd to represent enemyTankLeft
			enemyTankMiddle->reset(2);                //The number "2" is uesd to represent enemyTankMiddle
			enemyTankRight->reset(3);                 //The number "3" is uesd to represent enemyTankRight
			playerTank->reset();
			auto wallMag = (WallManager*)getChildByTag(4);
			this->removeChild(wallMag);
			WallManager* wallMgr = WallManager::create();   //ToughMode will recreate all walls except the walls around the symbol,
			wallMgr->createWalls(wallVec, 88);              //so that skeletens will bump the symbol more easily
			                                             
			this->addChild(wallMgr);
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("blast.wav");
		}
	}
}

void GameScene::tankBorn(int num) {
	Size screenSize = Director::getInstance()->getVisibleSize();

	Sprite* runSp = Sprite::create("born1.png");
	runSp->setAnchorPoint(ccp(0.5, 0.5));

	switch (num) {
	case 1:runSp->setPosition(Point(30, screenSize.height - 30)); break;                   //The "born.png" is 60*60
	case 2:runSp->setPosition(Point(screenSize.width / 2, screenSize.height - 30)); break; //The location is the same as the location of the enemyTank
	case 3:runSp->setPosition(Point(screenSize.width - 30, screenSize.height - 30)); break;
	}
	auto callbackFunc = [=]() {
		switch (num) {
		case 1:
			enemyTankLeft->bindSprite(Sprite::create("enemy1D.png"));
			enemyTankLeft->setPosition(Point(30, screenSize.height - 30));       //The enemytank's size is 60*60
			enemyTankLeft->setTankNum(1);
			break;
		case 2:
			enemyTankMiddle->bindSprite(Sprite::create("enemy2D.png"));
			enemyTankMiddle->setPosition(Point(screenSize.width / 2, screenSize.height - 30));
			enemyTankMiddle->setTankNum(2);
			break;
		case 3:
			enemyTankRight->bindSprite(Sprite::create("enemy3D.png"));
			enemyTankRight->setPosition(Point(screenSize.width - 30, screenSize.height - 30));
			enemyTankRight->setTankNum(3);
			break;
		}
	};
	RemoveSelf* removeSelf = RemoveSelf::create(true);
	CallFunc* callFunc = CallFunc::create(callbackFunc);
	auto act = Sequence::create(createAnimate(), callFunc, removeSelf, NULL); 
	runSp->runAction(act);
	this->addChild(runSp);
}

void GameScene::gameOver() {
	Size screenSize = Director::getInstance()->getVisibleSize();

	Sprite* gameover = Sprite::create("gameover.png");
	gameover->setAnchorPoint(ccp(0.5, 0.5));
	gameover->setPosition(Point(screenSize.width / 2, screenSize.height / 2));
	this->addChild(gameover);

	Button* closeBtn = Button::create("close.png");
	closeBtn->setAnchorPoint(ccp(1, 1));
	closeBtn->setPosition(Point(screenSize.width / 2 + 348 / 2, screenSize.height / 2 + 221 / 2));      //The "gameove.png" is 348*221
	closeBtn->addTouchEventListener(this, toucheventselector(GameScene::backToHelloWorldScene));
	this->addChild(closeBtn);

	isGameOver = true;

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("lose.wav", false);
}

void GameScene::win() {
	Size screenSize = Director::getInstance()->getVisibleSize();

	Sprite* win = Sprite::create("win.png");
	win->setAnchorPoint(ccp(0.5, 0.5));
	win->setPosition(Point(screenSize.width / 2, screenSize.height / 2));
	this->addChild(win);

	haveWin = true;
	playerTank->setAliveFalse();

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("win.wav", false);
}

void GameScene::update(float dt) {
	if ((!isGameOver) && (!haveWin)) {        //if player wins or game over, EnemyTank's update and GameScene's update need to stop.
		Size screenSize = Director::getInstance()->getVisibleSize();

		Rect playerrect = playerTank->getBoundingBox();
		Rect playbullet = playerBullet->getBoundingBox();
		Point playbulletp = playerBullet->getPosition();
		auto symbol = getChildByTag(3);
		Rect symrect = symbol->getBoundingBox();

		playTime++;
		enemyTankLeft->shootFrom(enemyTankLeft);
		enemyTankMiddle->shootFrom(enemyTankMiddle);
		enemyTankRight->shootFrom(enemyTankRight);

		bulletHitTheWall();
		bulletHitTheTank();

		if ((!enemyTankLeft->isAlive()) && (!enemyTankMiddle->isAlive()) && (!enemyTankRight->isAlive()) && (!haveWin)) {   //All enemeyTank die ,then the player wins
			win();
		}
		for (auto enemyBullet : bulletVec) {
			Point bulletRect = enemyBullet->getPosition();

			if ((symrect.containsPoint(playbulletp) && (playerBullet->isAlive())) ||      //Bullet hits the symbol
				(symrect.containsPoint(bulletRect)) && (enemyBullet->isAlive())) {
				playerBullet->hide();
				enemyBullet->hide();
				Sprite* symbolDie = Sprite::create("symbolDie.png");
				symbolDie->setAnchorPoint(ccp(0.5, 0.5));
				symbolDie->setPosition(Point(482 + 60 / 2, 45 / 2));   //The "symbolDie.png" is 60*45
				this->addChild(symbolDie);
				gameOver();
				playerTank->setAliveFalse();
			}
			if (playbullet.containsPoint(bulletRect) && (enemyBullet->isAlive())) {           //Player's bullet hits enemyTank's bullet
				playerBullet->hide();
				enemyBullet->hide();
			}
		}

		if (isToughMode&&playerTank->isAlive()) {                 //ToughMode
			skeletonBorn();

			Vector<EnemyTank*> ::iterator iterSkeleton = skeletonVec.begin();
			while (iterSkeleton != skeletonVec.end()) {
				auto remove = RemoveSelf::create(true);
				Rect skeletonRect = (*iterSkeleton)->getBoundingBox();
				if (playerrect.intersectsRect(skeletonRect)) {               //PlayerTank bumped with skeleton
					playerTank->hit();
					(*iterSkeleton)->hit(4);
					(*iterSkeleton)->runAction(remove);
					skeletonVec.erase(iterSkeleton);
					if (!playerTank->isAlive()) {
						gameOver();
					}
					break;
				}
				if (symrect.intersectsRect(skeletonRect)) {                  //The symbol bumped with skeleton,
					Sprite* symbolDie = Sprite::create("symbolDie.png");     //then game over;
					symbolDie->setAnchorPoint(ccp(0.5, 0.5));
					symbolDie->setPosition(Point(482 + 60 / 2, 45 / 2));     //The "symbolDie.png" is 60*45
					this->addChild(symbolDie);
					(*iterSkeleton)->hit(4);                                 //The number "4" is uesd to represent skeleton
					(*iterSkeleton)->hit(4);
					(*iterSkeleton)->runAction(remove);
					skeletonVec.erase(iterSkeleton);
					gameOver();
					break;
				}
				if ((skeletonRect.containsPoint(playbulletp)) && (playerBullet->isAlive())) {      //PlayerTank shoot the skeleton
					(*iterSkeleton)->hit(4);
					(*iterSkeleton)->runAction(remove);
					skeletonVec.erase(iterSkeleton);
					playerBullet->hide();
					break;
				}
				iterSkeleton++;
			}
		}
	}
}

Animate* GameScene::createAnimate() {     //Make the animation before the enemyTanks born
	int iFrameNum = 5;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameVec;

	for (int i = 1; i <= iFrameNum; i++) {
		frame = SpriteFrame::create(StringUtils::format("born%d.png", i), Rect(0, 0, 60, 60));
		frameVec.pushBack(frame);
	}

	Animation* animation = Animation::createWithSpriteFrames(frameVec);
	animation->setLoops(1);
	animation->setDelayPerUnit(0.1f);

	Animate* action = Animate::create(animation);

	return action;
}

void GameScene::bulletHitTheWall() {
	Size screenSize = Director::getInstance()->getVisibleSize();

	for (auto enemyBullet : bulletVec) {
		Vector<Wall*> ::iterator it = wallVec.begin();
		while (it != wallVec.end()) {
			Rect wallrect = (*it)->getBoundingBox();
			Rect bulletrect = enemyBullet->getBoundingBox();
			if (wallrect.intersectsRect(bulletrect) && (enemyBullet->isAlive())) {        //EnemtTanks' bullets hit the wall
				enemyBullet->hide();
				auto remove = RemoveSelf::create(true);
				(*it)->runAction(remove);
				wallVec.erase(it);
				break;
			}
			it++;
		}
		it = wallVec.begin();
		if (playerBullet->isAlive()) {
			if ((playerBullet->getPositionX() < 0) ||
				(playerBullet->getPositionX() > screenSize.width) ||
				(playerBullet->getPositionY() > screenSize.height) ||
				(playerBullet->getPositionY() < 0)) {

				playerBullet->hide();
			}
			while (it != wallVec.end()) {
				Rect wallrect = (*it)->getBoundingBox();
				Rect playrect = playerBullet->getBoundingBox();
				if (playrect.intersectsRect(wallrect)) {     //PlayerTank's bullet hits the wall
					playerBullet->hide();
					auto remove = RemoveSelf::create(true);
					(*it)->runAction(remove);
					wallVec.erase(it);
					break;
				}
				it++;
			}
		}
	}
}

void GameScene::bulletHitTheTank() {
	Point playbulletp = playerBullet->getPosition();
	Rect playerRect = playerTank->getBoundingBox();
	Rect tank[3] = { enemyTankLeft->getBoundingBox(), enemyTankMiddle->getBoundingBox(), enemyTankRight->getBoundingBox() };   //Bullet hits the enemyTank
	for (int i = 0; i < 3; i++) {
		if (tank[i].containsPoint(playbulletp) && (playerBullet->isAlive())) {
			if ((i + 1 == 1) && (enemyTankLeft->isAlive()))       { enemyTankLeft->hit(1); playerBullet->hide(); }     //The number "1" is uesd to represent enemyTankLeft
			else if ((i + 1 == 2) && (enemyTankMiddle->isAlive())){ enemyTankMiddle->hit(2); playerBullet->hide(); }   //The number "2" is uesd to represent enemyTankMiddle
			else if ((i + 1 == 3) && (enemyTankRight->isAlive())) { enemyTankRight->hit(3); playerBullet->hide(); }    //The number "3" is uesd to represent enemyTankRight
			break;
		}
	}
	for (auto enemyBullet : bulletVec) {      //Bullet hits the playerTank
		Point bulletrect = enemyBullet->getPosition();
		if (playerRect.containsPoint(bulletrect) && (enemyBullet->isAlive())) {
			enemyBullet->hide();
			playerTank->hit();
			if (playerTank->getNumlife() == 0) {
				gameOver();
			}
		}
	}
}

void GameScene::skeletonBorn() {
	Size screenSize = Director::getInstance()->getVisibleSize();

	if (!(playTime % 700)) {
		playTime = 0;
		playerTank->setTankSpeed(playerTank->getTankSpeed() + 1);
	}
	if (!(playTime % 200)) {
		auto skeleton = EnemyTank::create();
		skeleton->bindSprite(Sprite::create("Skeleton.png"));
		if (skeletonVec.size() % 2) {
			skeleton->setPosition((Point(30, screenSize.height / 2)));
		}
		else {
			skeleton->setPosition((Point(screenSize.width - 30, screenSize.height / 2)));
		}
		skeleton->setChangeFeq(30);
		skeleton->setTankSpeed(3);
		skeleton->setNumLife(1);
		this->addChild(skeleton);
		skeletonVec.pushBack(skeleton);
	}
}