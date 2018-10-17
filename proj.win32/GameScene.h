#pragma once

#include "cocos2d.h"
#include"proj.win32\Player.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	bool isKeyPressed(EventKeyboard::KeyCode);
	virtual void update(float delta) override;
	
	CREATE_FUNC(GameScene);

private :
	Player *player;
	bool moveLeft;
};

