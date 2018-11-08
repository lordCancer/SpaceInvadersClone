#pragma once

#include "cocos2d.h"
#include"Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Shield.h"
#include "Definations.h"
#include "MenuScene.h"
#include "SoundManager.h"

USING_NS_CC;
using namespace std;

enum GameState
{
	GamePlay,
	GameOver,
	GameWin
};

class GameScene : public Scene
{
public:
	virtual bool init();
	virtual void update(float delta) override;
	CREATE_FUNC(GameScene);
	
private :
	Player * player;
	Bullet * bullet;
	Enemy *enemies[ENEMY_ROW_COUNT][ENEMY_COLUMN_COUNT];
	Bullet *enemybullet;
	vector<Shield *>shields;
	int score;
	Label *scoreLabel;
	Label *livesLabel;
	Label *gameOverText;
	GameState gameState;
	float sceneTransitionInterval;

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
	int totalEnemies;

	//Game scene functions
	void initPlayer();
	void initBullet();
	void setPlayerBulletPosition();
	void initEnemies();
	void initEnemyBullet();
	void initShields();
	void updateGamePlay(float dt);
	void checkCollisions();
	void updateEnemies(float dt);
	void setEnemyBulletPosition();
	void updateScoreText();
	void updateLivesText();
	void loadMainMenu(float dt);
	void onEnterTransitionDidFinish();
	void onExitTransitionDidStart();

	//sound variables and functions
	SoundManager *soundManager;
	int gamePlayMusicId;
	void playShootSFX();
	void playInvaderHitSFX();
	void playEnemyShootSFX();
	void playPlayerExplosionSFX();
	void PlayGameOverSFX();
	void PlayGameWinSFX();

	void keyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void keyReleased(EventKeyboard::KeyCode keyCode, Event* event);
};

