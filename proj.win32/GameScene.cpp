#include "GameScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto label = Label::createWithSystemFont("SPACE INVADERS", "Arial",22);
	label->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	label->setPosition(Vec2(100, 460));
	this->addChild(label, 1);

	player = new Player(this);

	auto eventListener = EventListenerKeyboard::create();
	
	eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {

		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		case EventKeyboard::KeyCode::KEY_A:
			log("Left Arrow");
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_D:
			log("Right Arrow");
			break;
		
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,this);

	this->scheduleUpdate();

	return true;
}

bool GameScene::isKeyPressed(EventKeyboard::KeyCode code) 
{
	if (code == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		return true;
	return false;
}

void GameScene::update(float delta)
{
	Node::update(delta);

	if (isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW))
	{
		player->moveLeft();
	}
}
