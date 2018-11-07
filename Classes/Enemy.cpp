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
	isActive = true;
	setContentSize(Size(SCREEN_SIZE.x / 15, SCREEN_SIZE.y / 15));
	
	return true;
}

void Enemy::enable()
{
	setVisible(true);
	isActive = true;
}

void Enemy::disable()
{
	setVisible(false);
	isActive = false;
}

bool Enemy::alive()
{
	return isActive;
}

Enemy::~Enemy()
{
}