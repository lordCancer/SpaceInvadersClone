#include"Shield.h"

Shield * Shield::create(string fileName)
{
	Shield *s = new Shield();

	if (s && s->initWithFile(fileName))
	{
		s->autorelease();
		return s;
	}

	CC_SAFE_DELETE(s);
	return nullptr;
}

bool Shield::initWithFile(const string & imgName)
{
	if (!Sprite::initWithFile(imgName))
		return false;

	isActive = true;
	health = SHIELD_HEALTH;
	setContentSize(Size(SCREEN_SIZE.x / 10, SCREEN_SIZE.y / 10));

	return true;
}

void Shield::enable()
{
	setVisible(true);
	isActive = true;
}

void Shield::disable()
{
	setVisible(false);
	isActive = false;
}

bool Shield::getIsActive()
{
	return isActive;
}

void Shield::setHealth(int damage)
{
	health = damage;
}

int Shield::getHealth() 
{
	return health;
}

Shield::~Shield()
{
}