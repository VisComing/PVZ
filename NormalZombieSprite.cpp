#include "NormalZombieSprite.h"

NormalZombieSprite::NormalZombieSprite()
{
	this->_hp = 100;
	attacting = false;
}
NormalZombieSprite::~NormalZombieSprite()
{

}

bool NormalZombieSprite::init()
{
	if (!ZombieBaseClass::initWithSpriteFrameName("Zombie_1.png"))
	{
		return false;
	}
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 22; i++)
	{
		images.pushBack(_normalZombieCache->getSpriteFrameByName(StringUtils::format("Zombie_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 22);
	this->runAction(RepeatForever::create(Animate::create(_animation)));
	return true;
}

Rect NormalZombieSprite::NormalZombieBounding()
{
	Rect originRect = this->getBoundingBox();
	this->_normalZombieRect.origin.x = originRect.origin.x + 90;
	this->_normalZombieRect.origin.y = originRect.origin.y;
	this->_normalZombieRect.size.width = originRect.size.width - 90;
	this->_normalZombieRect.size.height = originRect.size.height - 90;
	return this->_normalZombieRect;
}

FiniteTimeAction* NormalZombieSprite::headAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 12; i++)
	{
		images.pushBack(_normalZombieCache->getSpriteFrameByName(StringUtils::format("ZombieHead_%d.png", i)));
	}
	Animation* headAnimation = Animation::createWithSpriteFrames(images, 0.07f);
	this->_headAction = Animate::create(headAnimation);

	return this->_headAction;
}

FiniteTimeAction* NormalZombieSprite::noHeadAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 18; i++)
	{
		images.pushBack(_normalZombieCache->getSpriteFrameByName(StringUtils::format("ZombieLostHead_%d.png", i)));
	}
	Animation* noHeadAnimation = Animation::createWithSpriteFrames(images, 0.2f);
	this->_noHeadAction = Repeat::create(Animate::create(noHeadAnimation), 50);

	return this->_noHeadAction;
}
FiniteTimeAction* NormalZombieSprite::downTheGround()//½©Ê¬µ¹µØ
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 10; i++)
	{
		images.pushBack(_normalZombieCache->getSpriteFrameByName(StringUtils::format("ZombieDie_%d.png", i)));
	}
	Animation* downAnimation = Animation::createWithSpriteFrames(images, 0.1f);
	this->_downAction = Animate::create(downAnimation);

	return this->_downAction;
}

FiniteTimeAction * NormalZombieSprite::explodAction()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 20; i++)
	{
		images.pushBack(_boomDie1->getSpriteFrameByName(StringUtils::format("BoomDie1_%d.png", i)));
	}
	Animation* downAnimation = Animation::createWithSpriteFrames(images, 0.1f);
	this->_explodAction = Animate::create(downAnimation);

	return this->_explodAction;
}

RepeatForever * NormalZombieSprite::attackAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 21; i++)
	{
		images.pushBack(_boomDie1->getSpriteFrameByName(StringUtils::format("ZombieAttack_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 0.1f);
	this->_attackAction = RepeatForever::create(Animate::create(_animation));
	_attackAction->setTag(2368);
	return this->_attackAction;
}
