#include "Classes\Bullet.h"

Bullet* Bullet::create(string imgName)
{
	Bullet *b = new Bullet();

	if (b && b->initWithFile(imgName))
	{
		b->autorelease();
		return b;
	}
	CC_SAFE_DELETE(b);
	return nullptr;
}

bool Bullet::initWithFile(const string& fileName)
{
	if (!Sprite::initWithFile(fileName))
		return false;
	setContentSize(Size(SCREEN_SIZE.x / 250, SCREEN_SIZE.y / 30));
	isEnemyBullet = false;
	this->scheduleUpdate();
	return true;
}

void Bullet::update(float delta)
{
	if (isEnabled)
	{
		if (isEnemyBullet)
			moveDown(delta);
		else
			moveUp(delta);
	}
}

void Bullet::moveUp(float delta)
{
	Vec2 pos = this->getPosition();
	pos.y += BULLET_SPEED * delta;
	setPosition(pos);
}

void Bullet::moveDown(float delta)
{
	Vec2 pos = this->getPosition();
	pos.y -= BULLET_SPEED * delta;
	setPosition(pos);
}

void Bullet::enable()
{
	setVisible(true);
	isEnabled = true;
}

void Bullet::disable()
{
	setVisible(false);
	isEnabled = false;
}

void Bullet::setIsEnemyBullet(bool enemyBullet)
{
	isEnemyBullet = enemyBullet;
}
bool Bullet::getIsEnabled()
{
	return isEnabled;
}

Bullet::~Bullet()
{
}