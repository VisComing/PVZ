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
	peaShooterCard->setName("PeaShooterCard");
	this->addChild(peaShooterCard);
	
	auto potatoMineCard = Sprite::create("res/PotatoMineCard.png");
	potatoMineCard->setPosition(Vec2(325 + 50, 557));
	potatoMineCard->setName("PotatoMineCard");
	this->addChild(potatoMineCard);

	
	auto WallNutCard = Sprite::create("res/WallNutCard.png");
	WallNutCard->setPosition(Vec2(325 + 100, 557));
	WallNutCard->setName("WallNutCard");
	this->addChild(WallNutCard);
	
	auto ChomperCard = Sprite::create("res/ChomperCard.png");
	ChomperCard->setPosition(Vec2(325 + 150, 557));
	ChomperCard->setName("ChomperCard");
	this->addChild(ChomperCard);
}
