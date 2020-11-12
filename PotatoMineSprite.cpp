#include "PotatoMineSprite.h"

PotatoMineSprite::PotatoMineSprite()
{
	this->_plantHP = 80;
	_potatoMineTime = 0;
}

PotatoMineSprite::~PotatoMineSprite()
{
}

bool PotatoMineSprite::init()
{
	if (!PlantBaseClass::initWithSpriteFrameName("PotatoMineNotReady.png"))
	{
		return false;
	}

	
	for (int i = 1; i <= 8; i++)
	{
		images.pushBack(_potatoMineCache->getSpriteFrameByName(StringUtils::format("PotatoMine_%d.png", i)));
	}
	//_potatoMineGrow = RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(images, 1.f / 13)));


	//this->runAction(RepeatForever::create(Animate::create(_animation)));

	return true;
}
