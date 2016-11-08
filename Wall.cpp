#include"Wall.h"

Wall::Wall() {
}

Wall::~Wall() {
}

bool Wall::init() {
	return true;
}

void Wall::setWall(int num) {              //create walls one by one
	Size screenSize = Director::getInstance()->getVisibleSize();

	if (getSprite()) {
		if (num < 18) {
			setPosition(Point(screenSize.width / 5 + (num / 6) * 30 * 4 + 7, screenSize.height / 6 + (num % 6) * 30 + 50));
		}
		if (num >= 18 && num <= 21) {
			setPosition(Point(screenSize.width / 5 + 2 * 30 * 4 + 30 * (1 + num % 6) + 7, screenSize.height / 6 + 3 * 30 + 50));
		}
		if (num > 21 && num < 39) {
			setPosition(Point(screenSize.width / 5 + 3 * 30 * 4 + ((num - 21) / 6) * 30 * 4 + 7, screenSize.height / 6 + (num % 6) * 30 + 50));
		}
		if (num >= 39 && num <= 42) {
			setPosition(Point(screenSize.width / 5 + (num - 38) * 30 + 7, screenSize.height / 6 + 9 * 30 + 50));
		}
		if (43 == num) {
			setPosition(Point(screenSize.width / 5 + 2 * 30 * 4 + 7, screenSize.height / 6 + 9 * 30 + 50));
		}
		if (44 == num) {
			setPosition(Point(screenSize.width / 5 + 3 * 30 * 4 + 7, screenSize.height / 6 + 9 * 30 + 50));
		}
		if (num >= 45 && num <= 48) {
			setPosition(Point(screenSize.width / 5 + 4 * 30 * 4 + (num - 45) * 30 + 7, screenSize.height / 6 + 9 * 30 + 50));
		}
		int num_s = num - 49;
		if (num_s < 18 && num_s >= 0) {
			setPosition(Point(screenSize.width / 5 + (num_s / 6) * 30 * 4 + 7, screenSize.height / 6 + 12 * 30 + (num_s % 6) * 30 + 50));
		}
		if (num_s >= 18 && num_s <= 21) {
			setPosition(Point(screenSize.width / 5 + 2 * 30 * 4 + 30 * (1 + num_s % 6) + 7, screenSize.height / 6 + 15 * 30 + 50));
		}
		if (num_s> 21 && num_s < 39) {
			setPosition(Point(screenSize.width / 5 + 3 * 30 * 4 + ((num_s - 21) / 6) * 30 * 4 + 7, screenSize.height / 6 + 12 * 30 + (num_s % 6) * 30 + 50));
		}
		if (num >= 88 && num <= 91) {
			setPosition(Point(467 + (num - 88) * 30, 75));
		}
		if (num == 92 || num == 93) {
			setPosition(Point(467, 15 + 30 * (num - 92)));
		}
		if (num == 94 | num == 95) {
			setPosition(Point(557, 15 + 30 * (num - 94)));
		}
	}
}