#include "SunFlowerSprite.h"

SunFlowerSprite::SunFlowerSprite()
{
	this->_plantHP = 70;
	this->_sunCellTime = 0;
}

SunFlowerSprite::~SunFlowerSprite()
{
}

bool SunFlowerSprite::init()
{
	if (!PlantBaseClass::init())
	{
		return false;
	}

	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 18; i++)
	{
		images.pushBack(_sunFlowerCache->getSpriteFrameByName(StringUtils::format("SunFlower_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 18);
	this->runAction(RepeatForever::create(Animate::create(_animation)));

	return true;
}
