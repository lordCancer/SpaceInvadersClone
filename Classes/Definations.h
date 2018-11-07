#pragma once

#include "cocos2d.h"
#include"AppDelegate.h"

USING_NS_CC;

#define DESIGN_RESOLUTION 1024,768

#define APP_DELEGATE ((AppDelegate *) (Application::getInstance()))

#define SCREEN_SIZE  APP_DELEGATE->getScreenSize()
#define SCREEN_MID   APP_DELEGATE->getScreenMid()

#define PLAYER_SPEED 300
#define BULLET_SPEED 550

#define ENEMY_ROW_COUNT 5
#define ENEMY_COLUMN_COUNT 11

#define ENEMY_ROW_DITANCE_VALUE 0.08
#define ENEMY_COLUMN_DISTANCE_VALUE 0.9
#define ENEMY_MOVE_INTERVAL 0.5
#define ENEMY_DELTA_X 10.0
#define ENEMY_DELTA_Y 20.0
#define ENEMY_MOVE_ELAPSED_TIME 0.0
