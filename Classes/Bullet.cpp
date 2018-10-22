#include "Classes\Bullet.h"

Bullet::Bullet(Layer *layer)
{
	bulletSprite = Sprite::create("images/bullet.png");
	bulletSprite->setAnchorPoint(Vec2(0.5f,0.5f));
	bulletSprite->setScale(0.3f);
	layer->addChild(bulletSprite, 5);
}

void Bullet::setPosition(Vec2 position)
{
	bulletSprite->setPosition(position);
}

void Bullet::moveUp()
{
	Vec2 pos = bulletSprite->getPosition();
	pos.y += BULLET_SPEED;
	bulletSprite->setPosition(pos);
}
