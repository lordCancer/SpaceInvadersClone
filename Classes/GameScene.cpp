#include "GameScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	//scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
	//scene->getPhysicsWorld()->setGravity(Vect(0, 0));

	auto layer = GameScene::create();
	//layer->setPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto label = Label::createWithSystemFont("SPACE INVADERS", "Arial",40);
	//label->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	label->setPosition(SCREEN_SIZE.x * 0.5f, SCREEN_SIZE.y * 0.95f);
	this->addChild(label, 1);

	initPlayer();
	initBullet();
	initEnemy();

	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(GameScene::keyPressed, this);
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(GameScene::keyReleased, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener,this);

	this->scheduleUpdate();

	return true;
}

//void GameScene::setPhysicsWorld(PhysicsWorld *world)
//{
//	physicsWorld = world;
//}

void GameScene::keyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		moveLeft = true;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		moveRight = true;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		isShooting = true;
		break;
	default:
		break;
	}
}

void GameScene::keyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		moveLeft = false;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		moveRight = false;
		break;
	case EventKeyboard::KeyCode::KEY_SPACE:
		isShooting = false;
		break;
	default:
		break;
	}
}

void GameScene::update(float delta)
{
	Node::update(delta);

	updateGamePlay(delta);

	checkCollisions();
}

void GameScene::initPlayer()
{
	//player = new Player(this);
	player = Player::create("images/spaceship.png");
	addChild(player, 5);
	playerCanShoot = true;
}

void GameScene::initBullet()
{
	if (bullet == NULL)
	{
		bullet = Bullet::create("images/bullet.png");
		setBulletPosition();
		bullet->disable();
		addChild(bullet, 5);
	}
	
}

void GameScene::initEnemy()
{
	enemy = Enemy::create("images/enemy.png");
	enemy->setPosition(SCREEN_SIZE.x * 0.5f, SCREEN_SIZE.y * 0.8f);
	addChild(enemy, 5);
}

void GameScene::setBulletPosition()
{
	bullet->setPosition(player->getPosition());
}

void GameScene::checkCollisions()
{
	auto rect = enemy->getBoundingBox();

	if (rect.containsPoint(bullet->getPosition()))
	{
		bullet->disable();
		playerCanShoot = true;
	}
}

void GameScene::updateGamePlay(float dt)
{
	if (moveLeft)
	{
		player->moveLeft(dt);
	}
	if (moveRight)
	{
		player->moveRight(dt);
	}

	//We check if we are shooting and if playercanshoot is true
	//so that we can shoot 1 bullet at a time
	if (isShooting && playerCanShoot)
	{
		playerCanShoot = false;
		setBulletPosition();
		bullet->enable();
	}

	//If the bullet goes out of screen do this
	if (bullet->getPosition().y > SCREEN_SIZE.y)
	{
		bullet->disable();
		playerCanShoot = true;
	}
}