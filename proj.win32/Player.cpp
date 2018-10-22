#include "Player.h"

Player::Player(Layer *layer)
{
	playerSprite = Sprite::create("images/spaceship.png");
	playerSprite->setAnchorPoint(Vec2(0.5, 0.5));
	playerSprite->setContentSize(Size(35, 35));
	playerSprite->setPosition(Vec2(visibleSize.height / 2  ,80));
	layer->addChild(playerSprite, 5);
	/*log("Initial Position of the player(%0.0f) ", playerSprite->getPosition().x);
	log("Initial Visible visible origin x (%0.0f)", origin.x);
	log("Initial Visiblesize width (%0.0f)", visibleSize.width);*/
}

void Player::moveLeft()
{
	if (playerSprite->getPosition().x > playerSprite->getContentSize().width )
	{
		//displayMoveLeftValue();
		auto position = playerSprite->getPosition();
		position.x -= PLAYER_SPEED;
		playerSprite->setPosition(position);
	}
	//displayPlayerPosition();
}

void Player::moveRight()
{
	if (playerSprite->getPosition().x < visibleSize.width- playerSprite->getPosition().x+ 250)
	{
		//displayMoverightValue();
		auto position = playerSprite->getPosition();
		position.x += PLAYER_SPEED;
		playerSprite->setPosition(position);
	}
	//displayPlayerPosition();
}

void Player::shoot(Layer *layer)
{
	Bullet *bullet = new Bullet(layer);
	bullet->setPosition(playerSprite->getPosition());
}

void Player::displayPlayerPosition()
{
	log("Position x of the player(%0.0f) ", playerSprite->getPosition().x);
	log("Visible origin x(%0.0f)", origin.x);
	log("Visiblesize width (%0.0f)", visibleSize.width);
}

void Player::displayMoveLeftValue()
{
	log("Move left value: (%0.0f)", visibleSize.width + origin.x - playerSprite->getContentSize().width - 5);
}

void Player::displayMoverightValue()
{
	log("Move right value: (%0.0f)",visibleSize.width - playerSprite->getPosition().x + 250);
}