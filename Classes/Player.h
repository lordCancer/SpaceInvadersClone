#pragma once

#include "cocos2d.h"
#include "Definations.h"
#include "Bullet.h"
#include <iostream>

USING_NS_CC;
using namespace std;

class Player : public Sprite
{
public:
	static Player * create(string imgName);
	bool initWithFile(const string& filename);
	void moveRight(float delta);
	void moveLeft(float delta);
	//void createBullet(Layer *layer);
	~Player();
	void dead();
	int getLives();
	void setLives(int lives);

private:
	int currentLives;
};

//class Player 
//{
//public:
//	Player(Layer *layer);
//	void moveRight();
//	void moveLeft();
//	void shoot(Layer *layer);
//
//private:
//	Size visibleSize = Director::getInstance()->getVisibleSize();
//	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//
//	Sprite *playerSprite;  
//	void displayPlayerPosition();
//
//	void displayMoveLeftValue();
//	void displayMoverightValue();
//};



