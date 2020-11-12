#include "CardLayer.h"

CardLayer::CardLayer()
{
}

CardLayer::~CardLayer()
{
}

bool CardLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	Sprite* seedBank = Sprite::create("res/SeedBank.png");
	seedBank->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	seedBank->setPosition(Vec2(225,visibleSize.height));
	this->addChild(seedBank);
	this->initCardSprite();
	return true;
}

void CardLayer::initCardSprite()
{
	auto peaShooterCard = Sprite::create("res/Peashooter.png");
	peaShooterCard->setPosition(Vec2(325, 557));
	peaShooterCard->setName("peaShooterCard");
	this->addChild(peaShooterCard);
	
	auto potatoMineCard = Sprite::create("res/PotatoMineCard.png");
	potatoMineCard->setPosition(Vec2(325 + 50, 557));
	potatoMineCard->setName("potatoMineCard");
	this->addChild(potatoMineCard);
	
	

}
