#include "WallNutSprite.h"

WallNutSprite::WallNutSprite()
{
	this->_plantHP = 1000;
}

WallNutSprite::~WallNutSprite()
{
}

bool WallNutSprite::init()
{
	if (!PlantBaseClass::init())
	{
		return false;
	}

	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 16; i++)
	{
		images.pushBack(_wallNutCache->getSpriteFrameByName(StringUtils::format("WallNut_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 16);
	this->runAction(RepeatForever::create(Animate::create(_animation)));

	return true;
}

RepeatForever * WallNutSprite::wallNutCracked1()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 11; i++)
	{
		images.pushBack(_wallNutCache->getSpriteFrameByName(StringUtils::format("Wallnut_cracked1_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f/11);
	this->wallNutCracked1Action = RepeatForever::create(Animate::create(_animation));
	return this->wallNutCracked1Action;
}

RepeatForever * WallNutSprite::wallNutCracked2()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 15; i++)
	{
		images.pushBack(_wallNutCache->getSpriteFrameByName(StringUtils::format("Wallnut_cracked2_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 15);
	this->wallNutCracked2Action = RepeatForever::create(Animate::create(_animation));
	return this->wallNutCracked2Action;
}
