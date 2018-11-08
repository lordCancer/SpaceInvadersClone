#include "GameScene.h"

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	EventListenerKeyboard *keyboardListener;

	initPlayer();
	initBullet();
	initEnemies();
	initShields();

	score = 0;
	totalEnemies = TOTAL_ENEMY;

	scoreLabel = Label::createWithTTF("SCORE: 00", "fonts/thin_pixel-7.ttf", 70);
	scoreLabel->setPosition(SCREEN_SIZE.x * 0.12f, SCREEN_SIZE.y * 0.97f);
	this->addChild(scoreLabel, 1);

	livesLabel = Label::createWithTTF("LIVES x " + to_string(player->getLives()), "fonts/thin_pixel-7.ttf", 70);
	livesLabel->setPosition(SCREEN_SIZE.x * 0.86f, SCREEN_SIZE.y * 0.97f);
	this->addChild(livesLabel, 1);

	keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(GameScene::keyPressed, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(GameScene::keyReleased, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,this);

	this->scheduleUpdate();

	return true;
}

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
		setPlayerBulletPosition();
		bullet->disable();
		addChild(bullet, 5);
	}
}

void GameScene::initEnemies()
{
	//initializing all the variables needed to control enemies
	enemyMoveInterval = ENEMY_MOVE_INTERVAL;
	isEnemyMoveDownPending = false;
	isEnemyBelowPlayer = false;
	enemyMoveElapsedTime = ENEMY_MOVE_ELAPSED_TIME;
	deltaX = ENEMY_DELTA_X;
	deltaY = ENEMY_DELTA_Y;

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

	initEnemyBullet();
}

void GameScene::setPlayerBulletPosition()
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
				updateScoreText();
				totalEnemies--;
				if (totalEnemies < 1)
					log("YOU WIN!");
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
	
	//enemy bullet and player collision
	Rect r = player->getBoundingBox();
	if (r.intersectsRect(enemybullet->getBoundingBox()))
	{
		setEnemyBulletPosition();
		updateLivesText();
		if (player->getLives() <= 0)
		{
			log("GAME OVER!!");
		}
	}

	//Shield collision detection with playerBullet and enemy bullets
	for (int i = 0; i < (int)shields.size(); i++)
	{
		Rect r = shields[i]->getBoundingBox();
		//Collision with enemy bullet
		if (r.intersectsRect(enemybullet->getBoundingBox()) && shields[i]->getIsActive())
		{
			setEnemyBulletPosition();
			shields[i]->setHealth(shields[i]->getHealth() - 1);
			if (shields[i]->getHealth() < 1)
				shields[i]->disable();
		}
		//Collision with player bullet
		if (r.intersectsRect(bullet->getBoundingBox()) && shields[i]->getIsActive())
		{
			bullet->disable();
			setPlayerBulletPosition();
			playerCanShoot = true;
			shields[i]->setHealth(shields[i]->getHealth() - 1);
			if (shields[i]->getHealth() < 1)
				shields[i]->disable();
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
		setPlayerBulletPosition();//we set the bullet positions to players position before we fire the bullet
		bullet->enable();
	}

	//If the bullet goes out of screen do this
	if (bullet->getPosition().y > SCREEN_SIZE.y)
	{
		bullet->disable();
		playerCanShoot = true;
	}

	//If enemy bullet goes out of screen do this
	if (enemybullet->getPosition().y < SCREEN_SIZE.y * 0.01)
	{
		setEnemyBulletPosition();
	}
}

void GameScene::updateEnemies(float dt)
{
	enemyMoveElapsedTime += dt;

	if (enemyMoveElapsedTime >= enemyMoveInterval)
	{
		Enemy *rightMostEnemy = nullptr;
		Enemy *leftMostEnemy = nullptr;

		if (isEnemyMoveDownPending)
		{
			for (int i = 0; i < ENEMY_ROW_COUNT; i++)
			{
				for (int j = 0; j < ENEMY_COLUMN_COUNT; j++)
				{
					enemies[i][j]->setPositionY(enemies[i][j]->getPositionY() - deltaY);

					if (enemies[i][j]->getPositionY() < player->getPositionY())
					{
						isEnemyBelowPlayer = true; //Game Over
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
					//Move all the enemies left or right until they reach the screen limit on both endpoints of x
					enemies[i][j]->setPositionX(enemies[i][j]->getPositionX() + deltaX);
					if (i == 0 && j == 0)
					{
						if (leftMostEnemy != NULL)
							return;
						leftMostEnemy = enemies[i][j];
					}

					if (i == 0 && j == 10)
					{
						if (rightMostEnemy != NULL)
							return;
						rightMostEnemy = enemies[i][j];
					}

				}
			}
			if (rightMostEnemy->getPosition().x  > SCREEN_SIZE.x * 0.95f || leftMostEnemy->getPosition().x < SCREEN_SIZE.x * 0.05f)
			{
				deltaX *= -1;
				isEnemyMoveDownPending = true;
			}
		}
		enemyMoveElapsedTime -= enemyMoveInterval;
	}
}

void GameScene::initEnemyBullet()
{
	enemybullet = Bullet::create("images/bullet.png");
	enemybullet->setIsEnemyBullet(true);
	enemybullet->setColor(Color3B(255, 215, 0));//gold color
	addChild(enemybullet, 5);
	setEnemyBulletPosition();
	enemybullet->enable();
}

void GameScene::setEnemyBulletPosition() //sets the bullet positon to a random enemy
{
	int randomRowNum = RandomHelper::random_int(0, 4);
	int randomColumnNum = RandomHelper::random_int(0, 10);

	if (!enemies[randomRowNum][randomColumnNum]->alive())
		return;

	enemybullet->setPosition(enemies[randomRowNum][randomColumnNum]->getPosition());
}

void GameScene::initShields()
{
	Shield *s;
	float xValue = 0.25f;
	for (int i = 0; i < SHIELD_TOTAL; i++)
	{
		s = Shield::create("images/shield.png");
		s->setPosition(Vec2(SCREEN_SIZE.x * xValue, SCREEN_SIZE.y * 0.28f));
		addChild(s, 5);
		shields.push_back(s);
		xValue += 0.25f;
	}
}

void GameScene::updateScoreText()
{
	score += ENEMY_SCORE_VALUE;
	scoreLabel->setString("SCORE: " + to_string(score));
}

void GameScene::updateLivesText()
{
	player->setLives(player->getLives() - 1);
	livesLabel->setString("LIVES x " + to_string(player->getLives()));
}