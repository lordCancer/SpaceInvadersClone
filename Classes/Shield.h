#pragma once

#include "cocos2d.h"
#include "Definations.h"

USING_NS_CC;
using namespace std;

class Shield : public Sprite
{
public:
	static Shield * create(string fileName);
	bool initWithFile(const string &imgName);
	void enable();
	void disable();
	bool getIsActive();
	void setHealth(int damage);
	int getHealth();
	~Shield();

private:
	bool isActive;
	int health;
};
