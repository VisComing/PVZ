#include "ZombieCardLayer.h"
#include "global.h"
ZombieCardLayer::ZombieCardLayer()
{
}

ZombieCardLayer::~ZombieCardLayer()
{
}

bool ZombieCardLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	//只有当我是僵尸方的时候才显示僵尸卡片
	if (isSinglePlayerGameMode == false && _iAmPlantSideGolbalVariable == false)
	{
		Sprite* seedBank = Sprite::create("res/SeedBank.png");
		seedBank->setFlipX(true);
		seedBank->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
		auto visibleSize = Director::getInstance()->getVisibleSize();
		seedBank->setPosition(visibleSize);

		this->addChild(seedBank);
		this->initZombieCardSprite();
	}
	return true;
}

void ZombieCardLayer::initZombieCardSprite()
{
	auto normalZombieCard = Sprite::create("res/NormalZombie.png");
	normalZombieCard->setPosition(Vec2(1298, 557));
	normalZombieCard->setName("NormalZombieCard");
	this->addChild(normalZombieCard);

	auto flagZombieCard = Sprite::create("res/FlagZombieCard.png");
	flagZombieCard->setPosition(Vec2(1298 - 50, 557));
	flagZombieCard->setName("FlagZombieCard");
	this->addChild(flagZombieCard);

	auto coneheadZombieCard = Sprite::create("res/ConeheadZombieCard.png");
	coneheadZombieCard->setPosition(Vec2(1298 - 100, 557));
	coneheadZombieCard->setName("ConeheadZombieCard");
	this->addChild(coneheadZombieCard);

	auto bucketheadZombieCard = Sprite::create("res/BucketheadZombieCard.png");
	bucketheadZombieCard->setPosition(Vec2(1298 - 150, 557));
	bucketheadZombieCard->setName("BucketheadZombieCard");
	this->addChild(bucketheadZombieCard);
}
