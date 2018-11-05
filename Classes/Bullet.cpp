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
	setAnchorPoint(Vec2(0.5f, 0.5f));
	setScale(0.3f);
	this->scheduleUpdate();
	return true;
}

void Bullet::update(float delta)
{
	if (isActive)
		moveUp(delta);
}

void Bullet::moveUp(float delta)
{
	Vec2 pos = this->getPosition();
	pos.y += BULLET_SPEED * delta;
	setPosition(pos);
}

void Bullet::enable()
{
	setVisible(true);
	isActive = true;
}

void Bullet::disable()
{
	setVisible(false);
	isActive = false;
}

Bullet::~Bullet()
{
}