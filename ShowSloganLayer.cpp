#include "ShowSloganLayer.h"

ShowSloganLayer::ShowSloganLayer()
{
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
	scheduleUpdate();
	this->showPrepareInfo();
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

//��ô������ʧ����Ӧ����ʾ����Ȼ����ʧ��2020/11/19  ԭ����һֱ����������������Բ�����ʧ���Ժ������ת������
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
