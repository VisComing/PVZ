#include "ShowSloganLayer.h"
#include "global.h"
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

//��ô������ʧ����Ӧ����ʾ����Ȼ����ʧ��2020/11/19  ԭ����һֱ����������������Բ�����ʧ���Ժ�������ת������
void ShowSloganLayer::showZombieEnterYourHome()
{
	Sprite* gameOver = Sprite::create("res/ZombiesWon.png");
	this->addChild(gameOver);
	gameOver->setPosition(700, 300);
}

void ShowSloganLayer::winInSingleMode()
{
	Sprite* winSprite = Sprite::create("res/winInSingleMode.png");
	this->addChild(winSprite);
	winSprite->setPosition(700, 300);
	winSprite->runAction(Spawn::createWithTwoActions(FadeIn::create(1), ScaleBy::create(2, 2)));
}

void ShowSloganLayer::showZombieLose()
{
	Sprite* winSprite = Sprite::create("res/zombieLose.png");
	this->addChild(winSprite);
	winSprite->setPosition(700, 300);
	winSprite->runAction(Spawn::createWithTwoActions(FadeIn::create(1), ScaleBy::create(2, 2)));
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