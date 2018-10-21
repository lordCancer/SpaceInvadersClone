#pragma once

#include "cocos2d.h"
#include"proj.win32\Player.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	virtual void update(float delta) override;
	CREATE_FUNC(GameScene);

private :
	Player * player;
	bool moveLeft;
	bool moveRight;

	void keyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void keyReleased(EventKeyboard::KeyCode keyCode, Event* event);
};

