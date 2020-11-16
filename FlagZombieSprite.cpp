#include "FlagZombieSprite.h"

FlagZombieSprite::FlagZombieSprite()
{
	this->_hp = 100;
	attacting = false;
}

FlagZombieSprite::~FlagZombieSprite()
{
}

bool FlagZombieSprite::init()
{
	if (!ZombieBaseClass::initWithSpriteFrameName("FlagZombie_1.png"))
	{
		return false;
	}
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 12; i++)
	{
		images.pushBack(_flagZombieCache->getSpriteFrameByName(StringUtils::format("FlagZombie_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 12);
	this->runAction(RepeatForever::create(Animate::create(_animation)));
	return true;
}

Rect FlagZombieSprite::zombieBounding()
{
	Rect originRect = this->getBoundingBox();
	this->_flagZombieRect.origin.x = originRect.origin.x + 90;
	this->_flagZombieRect.origin.y = originRect.origin.y + 20;
	this->_flagZombieRect.size.width = originRect.size.width - 90;
	this->_flagZombieRect.size.height = originRect.size.height - 50;
	return this->_flagZombieRect;
}

RepeatForever * FlagZombieSprite::walkAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 12; i++)
	{
		images.pushBack(_flagZombieCache->getSpriteFrameByName(StringUtils::format("FlagZombie_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 12);
	this->_walkAction = RepeatForever::create(Animate::create(_animation));
	return this->_walkAction;
}

FiniteTimeAction * FlagZombieSprite::noHeadWalkAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 12; i++)
	{
		images.pushBack(_flagZombieCache->getSpriteFrameByName(StringUtils::format("FlagZombieLostHead_%d.png", i)));
	}
	Animation* noHeadAnimation = Animation::createWithSpriteFrames(images, 1.f / 12);
	this->_noHeadWalkAction = RepeatForever::create(Animate::create(noHeadAnimation));

	return this->_noHeadWalkAction;
}

RepeatForever * FlagZombieSprite::attackAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 21; i++)
	{
		images.pushBack(_flagZombieCache->getSpriteFrameByName(StringUtils::format("ZombieAttack_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 0.1f);
	this->_attackAction = RepeatForever::create(Animate::create(_animation));
	_attackAction->setTag(2368);
	return this->_attackAction;
}

RepeatForever * FlagZombieSprite::flagZombieLostHeadAttackAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 11; i++)
	{
		images.pushBack(_flagZombieCache->getSpriteFrameByName(StringUtils::format("FlagZombieLostHeadAttack_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 11);
	this->_flagZombieLostHeadAttackAction = RepeatForever::create(Animate::create(_animation));
	return this->_flagZombieLostHeadAttackAction;
}
