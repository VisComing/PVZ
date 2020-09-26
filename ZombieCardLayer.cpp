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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->_zombieCardSprte = ZombieCardSprite::create();
	this->_zombieCardSprte->setAnchorPoint(Vec2::ANCHOR_TOP_RIGHT);
	this->_zombieCardSprte->setPosition(Vec2(1321, 593));
	this->addChild(_zombieCardSprte);



}
