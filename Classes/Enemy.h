#pragma once

#include "cocos2d.h"
#include "Definations.h"
#include <iostream>
#include "Bullet.h"

USING_NS_CC;
using namespace std;

class Enemy : public Sprite
{
public:
	static Enemy* create(string imgName);
	bool initWithFile(const string& fileName);
	void enable();
	void disable();
	bool alive();
	~Enemy();

private:
	bool isActive;
};