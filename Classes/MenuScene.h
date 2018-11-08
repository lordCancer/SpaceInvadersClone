#pragma once

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include  "Definations.h"
#include"GameScene.h"
#include "SoundManager.h"

USING_NS_CC;
using namespace std;
using namespace ui;

class MenuScene : public Scene
{
public:
	CREATE_FUNC(MenuScene);
	bool init();
	void onEnterTransitionDidFinish();
	void onExitTransitionDidStart();

private:
	void loadGameScene();
	SoundManager *soundManager;
	void playButtonSound();
	int menuMusicId;
	int btnSoundId;
};
