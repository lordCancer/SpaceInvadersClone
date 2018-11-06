#include "GameScene.h"

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
	Label *scoreLabel;
	EventListenerKeyboard *keyboardListener;
	visibleOrigin = Director::getInstance()->getVisibleOrigin();
	scoreLabel = Label::createWithTTF("SCORE: ", "fonts/thin_pixel-7.ttf", 70);
	scoreLabel->setPosition(SCREEN_SIZE.x * 0.1f, SCREEN_SIZE.y * 0.97f);
	this->addChild(scoreLabel, 1);

	enemyMoveInterval = 0.5f;
	isEnemyMoveDownPending = false;
	isEnemyBelowPlayer = false;
	enemyMoveElapsedTime = 0.0f;
	enemyDeltaY = ENEMY_COLUMN_DISTANCE_VALUE;
	
	initPlayer();
	initBullet();
	initEnemies();

	keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::keyReleased, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,this);

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

	updateEnemies(delta);

	checkCollisions();
}

void GameScene::initPlayer()
{
	if (player == NULL)
	{
		//player = new Player(this);
		player = Player::create("images/spaceship.png");
		addChild(player, 5);
		playerCanShoot = true;
	}
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

void GameScene::initEnemies()
{
	float rowDistance = ENEMY_ROW_DITANCE_VALUE;
	float columnDistance = ENEMY_COLUMN_DISTANCE_VALUE;

	for (int i = 0; i < ENEMY_ROW_COUNT; i++)
	{
		for (int j = 0; j < ENEMY_COLUMN_COUNT; j++)
		{
			Enemy *e = Enemy::create("images/enemy.png");
			e->setPosition(SCREEN_SIZE.x *  rowDistance, SCREEN_SIZE.y * columnDistance);
			addChild(e, 5);
			enemies[i][j] = e;
			rowDistance += 0.08;
		}
		columnDistance -= 0.08f;
		rowDistance = ENEMY_ROW_DITANCE_VALUE;
	}
}

void GameScene::setBulletPosition()
{
	bullet->setPosition(player->getPosition());
}

void GameScene::checkCollisions()
{	
	//Checks if the player bullet is colliding with an enemy
	for (int i = 0; i < ENEMY_ROW_COUNT; i++)
	{
		for (int j = 0; j < ENEMY_COLUMN_COUNT; j++)
		{
			Rect r = enemies[i][j]->getBoundingBox();
			if (enemies[i][j]->alive() && r.intersectsRect(bullet->getBoundingBox()))
			{
				enemies[i][j]->disable();
				bullet->disable();
				playerCanShoot = true;
			}
			/*if (r.containsPoint(bullet->getPosition()))
			{
				bullet->disable();
				playerCanShoot = true;
			}*/
		}
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
	//so that we shoot 1 bullet at a time
	if (isShooting && playerCanShoot)
	{
		playerCanShoot = false;
		setBulletPosition();//we set the bullet positions to players position before we fire the bullet
		bullet->enable();
	}

	//If the bullet goes out of screen do this
	if (bullet->getPosition().y > SCREEN_SIZE.y)
	{
		bullet->disable();
		playerCanShoot = true;
	}
}

void GameScene::updateEnemies(float dt)
{
	enemyMoveElapsedTime += dt;

	if (enemyMoveElapsedTime >= enemyMoveInterval)
	{
		for (int i = 0; i < ENEMY_ROW_COUNT; i++)
		{
			for (int j = 0; j < ENEMY_COLUMN_COUNT; j++)
			{

				enemies[i][j]->setPositionY(enemies[i][j]->getPositionY() - ENEMY_COLUMN_DISTANCE_VALUE);
				if (enemies[i][j]->getPositionY() < player->getPositionY())
				{
					isEnemyBelowPlayer = true;
				}
			}
		}
		enemyMoveElapsedTime -= enemyMoveInterval;
	}
	
	/*enemyMoveInterval += dt;

	if (enemyMoveElapsedTime >= enemyMoveInterval)
	{
		Enemy * rightMostEnemy = nullptr;
		Enemy * leftMostEnemy = nullptr;

		if (isEnemyMoveDownPending)
		{
			for (int i = 0; i < ENEMY_ROW_COUNT; i++)
			{
				for (int j = 0; j < ENEMY_COLUMN_COUNT; j++)
				{
					auto e = enemies[i][j];

					if (e->alive())
						continue;

					e->setPositionY(e->getPositionY() - ENEMY_COLUMN_DISTANCE_VALUE );

					if (e->getPositionY() < player->getPositionY())
					{
						isEnemyBelowPlayer = true;
					}
				}
			}
			isEnemyMoveDownPending = false;
		}
		else
		{
			for (int i = 0; i < ENEMY_ROW_COUNT; i++)
			{
				for (int j = 0; j < ENEMY_COLUMN_COUNT; j++)
				{
					auto e = enemies[i][j];

					if (e->alive())
						continue;

					e->setPositionX(e->getPositionX() - ENEMY_ROW_DITANCE_VALUE);

					rightMostEnemy = e;
					if (!leftMostEnemy)
						leftMostEnemy = e;
				}
			}
			if (std::ceil(rightMostEnemy->getPositionX() + rightMostEnemy->getContentSize().width / 2) >= visibleOrigin.x + SCREEN_SIZE.x ||
				std::floor(leftMostEnemy->getPositionX() - leftMostEnemy->getContentSize().width / 2) <= visibleOrigin.x)
			{
				enemyDeltaX *= -1;
				isEnemyMoveDownPending = true;
			}
		}
		enemyMoveElapsedTime -= enemyMoveInterval;
	}*/
}