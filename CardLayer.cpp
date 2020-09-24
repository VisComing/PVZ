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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->_cardSprte = CardSprite::create();
	this->_cardSprte->setPosition(Vec2(325, 557));
	this->addChild(_cardSprte);
	
	

}
