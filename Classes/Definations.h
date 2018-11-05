#pragma once

#include "cocos2d.h"
#include"AppDelegate.h"

USING_NS_CC;

#define DESIGN_RESOLUTION 1024,768

#define APP_DELEGATE ((AppDelegate *) (Application::getInstance()))

#define SCREEN_SIZE  APP_DELEGATE->getScreenSize()
#define SCREEN_MID   APP_DELEGATE->getScreenMid()

#define PLAYER_SPEED 300
#define BULLET_SPEED 450
