#pragma once

#include "cocos2d.h"
#include "Definations.h"
#include <iostream>

USING_NS_CC;
using namespace std;

class Enemy : public Sprite
{
public:
	static Enemy* create(string imgName);
	bool initWithFile(const string& fileName);
	~Enemy();

private:

};