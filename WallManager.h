#ifndef __WallManager_H__
#define __WallManager_H__

#include "cocos2d.h"
#include "Wall.h"
USING_NS_CC;

class WallManager : public Node {
public:
	CREATE_FUNC(WallManager);
	virtual bool init();
	void createWalls(Vector<Wall*>& wallVec, int num);

};

#endif