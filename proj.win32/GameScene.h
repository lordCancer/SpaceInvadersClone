#pragma once

#include "cocos2d.h"
#include"proj.win32\Player.h"
#include "Bullet.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float delta) override;
	CREATE_FUNC(GameScene);

private :
	PhysicsWorld *physicsWorld;
	Player * player;
	Bullet * bullet;
	
	bool moveLeft;
	bool moveRight;
	bool isShooting;

	void initBullet();
	void setBulletPosition();

	void keyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void keyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	void setPhysicsWorld(PhysicsWorld *world);
};

