/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "AppDelegate.h"
#include "GameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
	auto director = Director::getInstance();

	auto glview = director->getOpenGLView();
	if (!glview) {
		glview = GLViewImpl::create("Space Invaders");
		glview->setDesignResolutionSize(DESIGN_RESOLUTION, ResolutionPolicy::SHOW_ALL);
		glview->setFrameSize(DESIGN_RESOLUTION);
		director->setOpenGLView(glview);
	}

	screenSize.x = Director::getInstance()->getVisibleSize().width;
	screenSize.y = Director::getInstance()->getVisibleSize().height;
	screenMid.x = screenSize.x / 2;
	screenMid.y = screenSize.y / 2;

	auto scene = GameScene::createScene();
	director->runWithScene(scene);
	return true;
}

void AppDelegate::applicationDidEnterBackground() 
{
}

void AppDelegate::applicationWillEnterForeground() 
{
}

Vec2 AppDelegate::getScreenSize()
{
	return screenSize;
}

Vec2 AppDelegate::getScreenMid()
{
	return screenMid;
}