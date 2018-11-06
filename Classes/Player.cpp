#include "Player.h"

Player* Player::create(string imgName)
{
	Player *p;
	p = new Player();

	if (p && p->initWithFile(imgName))
	{
		p->autorelease();
		return p;
	}
	CC_SAFE_DELETE(p);
	return nullptr;
}

bool Player::initWithFile(const string& filename)
{
	if (!Sprite::initWithFile(filename))
		return false;

	setAnchorPoint(Vec2(0.5f, 0.5f));
	setContentSize(Size(SCREEN_SIZE.x/18, SCREEN_SIZE.y/18));
	setPosition(Vec2(SCREEN_SIZE.x * 0.5f, SCREEN_SIZE.y * 0.1f ));
	
	return true;
}

void Player::moveLeft(float delta)
{
	if (this->getPosition().x > SCREEN_SIZE.x *0.05f)
	{
		//displayMoveLeftValue();
		auto position = this->getPosition();
		position.x -= PLAYER_SPEED * delta;
		this->setPosition(position);
	}
}
void Player::moveRight(float delta)
{
	if (this->getPosition().x < SCREEN_SIZE.x * 0.95f)
	{
		//displayMoverightValue();
		auto position = this->getPosition();
		position.x += PLAYER_SPEED * delta;
		this->setPosition(position);
	}
}

Player::~Player()
{
}

//void Player::createBullet(Layer *layer)
//{
//	if (b != NULL)
//		return;
//	b = Bullet::create("images/bullet.png");
//	b->setPosition(this->getPosition());
//	layer->addChild(b, 5);
//}

//Player::Player(Layer *layer)
//{
//	playerSprite = Sprite::create("images/spaceship.png");
//	playerSprite->setAnchorPoint(Vec2(0.5, 0.5));
//	playerSprite->setContentSize(Size(35, 35));
//	playerSprite->setPosition(Vec2(visibleSize.height / 2  ,80));
//	layer->addChild(playerSprite, 5);
//	/*log("Initial Position of the player(%0.0f) ", playerSprite->getPosition().x);
//	log("Initial Visible visible origin x (%0.0f)", origin.x);
//	log("Initial Visiblesize width (%0.0f)", visibleSize.width);*/
//}
//
//void Player::moveLeft()
//{
//	if (playerSprite->getPosition().x > playerSprite->getContentSize().width )
//	{
//		//displayMoveLeftValue();
//		auto position = playerSprite->getPosition();
//		position.x -= PLAYER_SPEED;
//		playerSprite->setPosition(position);
//	}
//	//displayPlayerPosition();
//}
//
//void Player::moveRight()
//{
//	if (playerSprite->getPosition().x < visibleSize.width- playerSprite->getPosition().x+ 250)
//	{
//		//displayMoverightValue();
//		auto position = playerSprite->getPosition();
//		position.x += PLAYER_SPEED;
//		playerSprite->setPosition(position);
//	}
//	//displayPlayerPosition();
//}
//
////Incomplete function
//void Player::shoot(Layer *layer)
//{
//	Bullet *bullet = new Bullet(layer);
//	bullet->setPosition(playerSprite->getPosition());
//}
//
//void Player::displayPlayerPosition()
//{
//	log("Position x of the player(%0.0f) ", playerSprite->getPosition().x);
//	log("Visible origin x(%0.0f)", origin.x);
//	log("Visiblesize width (%0.0f)", visibleSize.width);
//}
//
//void Player::displayMoveLeftValue()
//{
//	log("Move left value: (%0.0f)", visibleSize.width + origin.x - playerSprite->getContentSize().width - 5);
//}
//
//void Player::displayMoverightValue()
//{
//	log("Move right value: (%0.0f)",visibleSize.width - playerSprite->getPosition().x + 250);
//}
