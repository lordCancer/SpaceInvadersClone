#include "MenuScene.h"

bool MenuScene::init()
{
	if (!Scene::init())
		return false;

	Sprite * logoImg = Sprite::create("images/logo.png");
	logoImg->setPosition(Vec2(SCREEN_MID.x, SCREEN_SIZE.y *0.8));
	logoImg->setScale(2.0f);
	this->addChild(logoImg, 1);

	Label * textLabel = Label::createWithTTF("         CLONE\n by DUGE LOLLEN (BCA-19)", "fonts/thin_pixel-7.ttf", 65);
	textLabel->setPosition(SCREEN_MID.x, SCREEN_SIZE.y * 0.59f);
	this->addChild(textLabel, 1);

	Label * instructionlbl = Label::createWithTTF("MOVEMENT: Arrow keys/A,D \nSHOOT: space", "fonts/thin_pixel-7.ttf", 50);
	instructionlbl->setPosition(SCREEN_MID.x, SCREEN_SIZE.y * 0.2f);
	this->addChild(instructionlbl, 1);

	Button * playButton = Button::create("images/button.png", "images/button_pressed.png", "images/button_pressed.png");
	playButton->setTitleText("START!");
	playButton->setTitleFontName("fonts/thin_pixel-7.ttf");
	playButton->setTitleFontSize(55.0f);
	playButton->setTitleColor(Color3B(0, 0, 0));
	playButton->setTitleAlignment(TextHAlignment::CENTER);
	playButton->setPosition(Vec2(SCREEN_MID.x, SCREEN_SIZE.y * 0.35));
	playButton->addTouchEventListener([&](Ref * sender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::ENDED:
			loadGameScene();
			break;
		default:
			break;
		}
	});
	this->addChild(playButton,1);

	return true;
}

void MenuScene::loadGameScene()
{
	Scene *gameScene = GameScene::create();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, gameScene, Color3B(0, 255, 255)));
}