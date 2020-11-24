#include "ShowSloganLayer.h"
#include "global.h"
#include"ui/CocosGUI.h"
ShowSloganLayer::ShowSloganLayer()
{
	_num = SpriteFrameCache::getInstance();
	_num->addSpriteFramesWithFile("res/num.plist");
}

ShowSloganLayer::~ShowSloganLayer()
{
}

bool ShowSloganLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//scheduleUpdate();
	if (_iAmPlantSideGolbalVariable == true || isSinglePlayerGameMode == true)
	{
		this->showPrepareInfo();
	}
	return true;
}

void ShowSloganLayer::showPrepareInfo()
{
	Sprite* prepare = Sprite::create();
	this->addChild(prepare);
	prepare->setPosition(700, 300);
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/prepare.plist");
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 3; i++)
	{
		images.pushBack(cache->getSpriteFrameByName(StringUtils::format("PrepareGrowPlants_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 2.5f / 3);
	FiniteTimeAction* t = Animate::create(_animation);
	//prepare->runAction(FiniteTimeAction::create(_animation));
	prepare->runAction(Sequence::createWithTwoActions(t, CallFunc::create([prepare]() {
			prepare->removeFromParent();
			})));
}

//怎么不会消失，不应该显示三秒然后消失吗？2020/11/19  原因是一直调用这个函数，所以不会消失。以后添加上转换场景
void ShowSloganLayer::showZombieEnterYourHome()
{
	auto returnBtn = ui::Button::create("res/returnToMainScene.png");
	Sprite* gameOver = Sprite::create("res/ZombiesWon.png");
	this->addChild(gameOver);
	gameOver->setPosition(700, 300);
	returnBtn->setPosition(Vec2(1000, 200));
	this->addChild(returnBtn);
	returnBtn->addClickEventListener([&](Ref* ref) {
		Director::getInstance()->popScene();
		});
}

void ShowSloganLayer::winInSingleMode()
{
	auto returnBtn = ui::Button::create("res/returnToMainScene.png");
	Sprite* winSprite = Sprite::create("res/winInSingleMode.png");
	this->addChild(winSprite);
	winSprite->setPosition(700, 300);
	returnBtn->setPosition(Vec2(1000, 200));
	this->addChild(returnBtn);
	returnBtn->setVisible(false);
	returnBtn->addClickEventListener([&](Ref* ref) {
		Director::getInstance()->popScene();
		});
	winSprite->runAction(Sequence::create(Spawn::createWithTwoActions(FadeIn::create(1), ScaleBy::create(2, 2)), 
		CallFunc::create([returnBtn]()
			{
				returnBtn->setVisible(true);
			}), NULL));
}

void ShowSloganLayer::showZombieLose()
{
	Sprite* winSprite = Sprite::create("res/zombieLose.png");
	auto returnBtn = ui::Button::create("res/returnToMainScene.png");
	returnBtn->setPosition(Vec2(1000, 200));
	this->addChild(returnBtn);
	this->addChild(winSprite);
	returnBtn->setVisible(false);
	winSprite->setPosition(700, 300);
	returnBtn->addClickEventListener([&](Ref* ref) {
		Director::getInstance()->popScene();
		});
	winSprite->runAction(Spawn::create(Sequence::create(FadeIn::create(1), ScaleBy::create(2, 2),
		CallFunc::create([returnBtn]() {
		returnBtn->setVisible(true);
	}), NULL)));
}

void ShowSloganLayer::showRemainingTime()
{
	Vector<SpriteFrame*> images;
	for (int i = 9; i >= 0; i--)
	{
		images.pushBack(_num->getSpriteFrameByName(StringUtils::format("num_%d.png", i)));
	}
	Animation* downAnimation = Animation::createWithSpriteFrames(images, 1.f);
	this->_remainingTime = Animate::create(downAnimation);
	Sprite* numSprite = Sprite::create();
	this->addChild(numSprite);
	numSprite->setPosition(700, 300);
	numSprite->runAction(Sequence::createWithTwoActions(this->_remainingTime, CallFunc::create([numSprite]()
		{
			numSprite->removeFromParent();
		})));
	//numSprite->runAction(this->_remainingTime);
}
