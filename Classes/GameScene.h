#pragma once

#include "cocos2d.h"
#include"Player.h"
#include "Bullet.h"
#include "Enemy.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float delta) override;
	CREATE_FUNC(GameScene);
	void checkCollisions();

private :
	//PhysicsWorld *physicsWorld;
	Player * player;
	Bullet * bullet;
	Enemy *enemy;
	
	//Player control related variables
	bool moveLeft;
	bool moveRight;
	bool isShooting;
	bool playerCanShoot;

	void initPlayer();
	void initBullet();
	void setBulletPosition();
	void initEnemy();

	void updateGamePlay(float dt);

	void keyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void keyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	//void setPhysicsWorld(PhysicsWorld *world);
};

