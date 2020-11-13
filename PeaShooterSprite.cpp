#include "PeaShooterSprite.h"

PeaShooterSprite::PeaShooterSprite()
{
	this->_plantHP = 300;
}

PeaShooterSprite::~PeaShooterSprite()
{
}

bool PeaShooterSprite::init()
{
	if (!PlantBaseClass::init())
	{
		return false;
	}

	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 13; i++)
	{
		images.pushBack(_peaShooterCache->getSpriteFrameByName(StringUtils::format("Peashooter_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 13);
	this->runAction(RepeatForever::create(Animate::create(_animation)));

	return true;
}
