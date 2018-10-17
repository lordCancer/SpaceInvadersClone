#include "Player.h"

Player::Player(Layer *layer)
{
	playerSprite = Sprite::create("images/spaceship.png");
	playerSprite->setAnchorPoint(Vec2(0.5, 0.5));
	playerSprite->setContentSize(Size(35, 35));
	playerSprite->setPosition(Vec2(visibleSize.height / 2  ,80));
	layer->addChild(playerSprite, 5);
}

void Player::moveLeft()
{
	if (playerSprite->getPosition().x > origin.x + playerSprite->getContentSize().width + 5)
	{
		auto position = playerSprite->getPosition();
		position.x -= PLAYER_SPEED;
		playerSprite->setPosition(position);
	}
}

void Player::moveRight()
{
	if (playerSprite->getPosition().x < visibleSize.width + origin.x - playerSprite->getContentSize().width - 5)
	{
		auto position = playerSprite->getPosition();
		position.x += PLAYER_SPEED;
		playerSprite->setPosition(position);
	}
}