#pragma once

#include "cocos2d.h"
#include"Player.h"
#include "Bullet.h"
#include "Enemy.h"

USING_NS_CC;
using namespace std;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float delta) override;
	CREATE_FUNC(GameScene);
	

private :
	Player * player;
	Bullet * bullet;
	Enemy *enemies[ENEMY_ROW_COUNT][ENEMY_COLUMN_COUNT];
	Bullet *enemybullet;
	int score;
	Label *scoreLabel;
	Label *livesLabel;

	//Player control related variables
	bool moveLeft;
	bool moveRight;
	bool isShooting;
	bool playerCanShoot;

	//enemy control related variables
	float enemyMoveElapsedTime;
	float enemyMoveInterval;
	bool isEnemyBelowPlayer;
	bool isEnemyMoveDownPending;
	float deltaX;
	float deltaY;

	//Game scene functions
	void initPlayer();
	void initBullet();
	void setPlayerBulletPosition();
	void initEnemies();
	void initEnemyBullet();
	void updateGamePlay(float dt);
	void checkCollisions();
	void updateEnemies(float dt);
	void setEnemyBulletPosition();
	void updateScoreText();
	void updateLivesText();

	void keyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void keyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	//void setPhysicsWorld(PhysicsWorld *world);
};

