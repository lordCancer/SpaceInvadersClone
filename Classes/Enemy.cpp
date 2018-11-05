#include"Enemy.h"

Enemy *Enemy::create(string imgName)
{
	Enemy * enemy = new Enemy();

	if (enemy && enemy->initWithFile(imgName))
	{
		enemy->autorelease();
		return enemy;
	}

	CC_SAFE_DELETE(enemy);
	return nullptr;
}

bool Enemy::initWithFile(const string& fileName)
{
	if (!Sprite::initWithFile(fileName))
		return false;

	setContentSize(Size(SCREEN_SIZE.x / 10, SCREEN_SIZE.y / 10));
	return true;
}

Enemy::~Enemy()
{
}