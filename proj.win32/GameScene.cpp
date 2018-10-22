#include "GameScene.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(0xffff);
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));

	auto layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());

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
	auto keyBoardListener = EventListenerKeyboard::create();
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(GameScene::keyPressed, this);
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(GameScene::keyReleased, this);

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(keyBoardListener,this);

	this->scheduleUpdate();

	return true;
}

void GameScene::setPhysicsWorld(PhysicsWorld *world)
{
	physicsWorld = world;
}

void GameScene::keyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		moveLeft = true;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		moveRight = true;
	case EventKeyboard::KeyCode::KEY_SPACE:
		isShooting = true;
	default:
		break;
	}
}

void GameScene::keyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		moveLeft = false;
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		moveRight = false;
	case EventKeyboard::KeyCode::KEY_SPACE:
		isShooting = false;
	default:
		break;
	}
}

void GameScene::update(float delta)
{
	Node::update(delta);

	if (moveLeft)
	{
		player->moveLeft();
	}
	if (moveRight)
	{
		player->moveRight();
	}

	//Bad way to shoot
	if (isShooting)
	{
		player->shoot(this);
	}
}
