#pragma once

#include "cocos2d.h"
#include"Definations.h"
#include <iostream>

USING_NS_CC;
using namespace std;

class Bullet : public Sprite
{
public:
	static Bullet *create(string imgName);
	bool initWithFile(const string& fileName);
	void moveUp(float delta);
	void moveDown(float delta);
	void enable();
	void disable();
	virtual void update(float delta);
	void setIsEnemyBullet(bool enemyBullet);
	bool getIsEnabled();
	~Bullet();

private:
	bool isEnabled;
	bool isEnemyBullet;
};
