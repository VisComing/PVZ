#include "ZombieCardLayer.h"

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

	Sprite* seedBank = Sprite::create("res/SeedBank.png");
	seedBank->setFlipX(true);
	seedBank->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	seedBank->setPosition(visibleSize);
	
	this->addChild(seedBank);
	this->initZombieCardSprite();
	return true;
}

void ZombieCardLayer::initZombieCardSprite()
{
	auto peaShooterCard = Sprite::create("res/NormalZombie.png");
	peaShooterCard->setPosition(Vec2(1298, 557));
	peaShooterCard->setName("NormalZombieCard");
	this->addChild(peaShooterCard);

}
