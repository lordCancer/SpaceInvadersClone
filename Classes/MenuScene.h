#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include  "Definations.h"
#include"GameScene.h"

USING_NS_CC;
using namespace std;
using namespace ui;

class MenuScene : public Scene
{
public:
	CREATE_FUNC(MenuScene);
	bool init();

private:
	void loadGameScene();
};
