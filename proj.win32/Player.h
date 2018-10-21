#pragma once

#include "cocos2d.h"
#include "proj.win32\Definations.h"
USING_NS_CC;

class Player 
{
public:
	Player(Layer *layer);
	void moveRight();
	void moveLeft();

private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite* playerSprite;
	
	void displayPlayerPosition();

	void displayMoveLeftValue();
	void displayMoverightValue();
};

