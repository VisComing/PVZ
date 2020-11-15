#include "ChomperSprite.h"

ChomperSprite::ChomperSprite()
{
	this->_plantHP = 400;
	this->_eatingZombie = false;
	this->_ateTime = 0;
}

ChomperSprite::~ChomperSprite()
{
}

bool ChomperSprite::init()
{
	if (!PlantBaseClass::init())
	{
		return false;
	}

	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 13; i++)
	{
		images.pushBack(_chomperCache->getSpriteFrameByName(StringUtils::format("Chomper_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.5f / 13);
	this->runAction(RepeatForever::create(Animate::create(_animation)));

	return true;
}

FiniteTimeAction* ChomperSprite::chomperAttack()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 9; i++)
	{
		images.pushBack(_chomperCache->getSpriteFrameByName(StringUtils::format("ChomperAttack_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.0f / 9);
	this->chomperAttackAction = Animate::create(_animation);

	return this->chomperAttackAction;
}

//RepeatForever * ChomperSprite::chomperAttack()
//{
//	Vector<SpriteFrame*> images;
//	for (int i = 1; i <= 9; i++)
//	{
//		images.pushBack(_chomperCache->getSpriteFrameByName(StringUtils::format("ChomperAttack_%d.png", i)));
//	}
//	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 9);
//	this->chomperAttackAction = RepeatForever::create(Animate::create(_animation));
//	return this->chomperAttackAction;
//}
RepeatForever * ChomperSprite::chomperNormal()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 13; i++)
	{
		images.pushBack(_chomperCache->getSpriteFrameByName(StringUtils::format("Chomper_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.5f / 13);
	this->chomperNormalAction = RepeatForever::create(Animate::create(_animation));
	return this->chomperNormalAction;
}
RepeatForever * ChomperSprite::chomperDigest()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 6; i++)
	{
		images.pushBack(_chomperCache->getSpriteFrameByName(StringUtils::format("ChomperDigest_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 6);
	this->chomperDigestAction = RepeatForever::create(Animate::create(_animation));
	return this->chomperDigestAction;
}


Rect ChomperSprite::plantBounding()
{
	Rect originRect = this->getBoundingBox();
	this->_chomperRect.origin.x = originRect.origin.x;
	this->_chomperRect.origin.y = originRect.origin.y;
	this->_chomperRect.size.width = originRect.size.width - 30;
	this->_chomperRect.size.height = originRect.size.height - 30;
	return this->_chomperRect;
}