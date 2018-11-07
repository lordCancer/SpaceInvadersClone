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
	//PhysicsWorld *physicsWorld;
	Player * player;
	Bullet * bullet;
	Enemy *enemies[ENEMY_ROW_COUNT][ENEMY_COLUMN_COUNT];
	
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
	Point visibleOrigin;
	float deltaX;
	float deltaY;

	//functions that initializes the elements of the Game scene 
	void initPlayer();
	void initBullet();
	void setBulletPosition();
	void initEnemies();

	void updateGamePlay(float dt);
	void checkCollisions();
	void updateEnemies(float dt);

	void keyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void keyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	//void setPhysicsWorld(PhysicsWorld *world);
};

