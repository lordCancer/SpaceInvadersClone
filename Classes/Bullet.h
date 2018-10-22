#pragma once

#include "cocos2d.h"
#include"proj.win32\Definations.h"
USING_NS_CC;

class Bullet
{
public:
	Bullet(Layer *layer);
	void moveUp();
	void setPosition(Vec2 position);

private:
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite* bulletSprite;	
};
