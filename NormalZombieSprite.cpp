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

Rect NormalZombieSprite::zombieBounding()
{
	Rect originRect = this->getBoundingBox();
	this->_normalZombieRect.origin.x = originRect.origin.x + 90;
	this->_normalZombieRect.origin.y = originRect.origin.y + 20;
	this->_normalZombieRect.size.width = originRect.size.width - 90;
	this->_normalZombieRect.size.height = originRect.size.height - 50;
	return this->_normalZombieRect;
}

RepeatForever * NormalZombieSprite::walkAnimation()
{

	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 22; i++)
	{
		images.pushBack(_normalZombieCache->getSpriteFrameByName(StringUtils::format("Zombie_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 22);
	this->_walkAction = RepeatForever::create(Animate::create(_animation));
	return this->_walkAction;
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

FiniteTimeAction* NormalZombieSprite::noHeadWalkAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 18; i++)
	{
		images.pushBack(_normalZombieCache->getSpriteFrameByName(StringUtils::format("ZombieLostHead_%d.png", i)));
	}
	Animation* noHeadAnimation = Animation::createWithSpriteFrames(images, 0.2f);
	this->_noHeadWalkAction = Repeat::create(Animate::create(noHeadAnimation), 50);

	return this->_noHeadWalkAction;
}
FiniteTimeAction* NormalZombieSprite::downTheGround()//僵尸倒地
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

//FiniteTimeAction * NormalZombieSprite::explodAction()
//{
//	Vector<SpriteFrame*> images;
//	for (int i = 1; i <= 20; i++)
//	{
//		images.pushBack(_boomDie1->getSpriteFrameByName(StringUtils::format("BoomDie1_%d.png", i)));
//	}
//	Animation* downAnimation = Animation::createWithSpriteFrames(images, 0.1f);
//	this->_explodAction = Animate::create(downAnimation);
//
//	return this->_explodAction;
//}

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

Action * NormalZombieSprite::normalZombieMoveWay()//在此修改僵尸移速
{
	_moveWayAction = MoveTo::create(this->getPositionX() / 40,  Vec2(0, this->getPositionY()));
	return _moveWayAction;
}

RepeatForever * NormalZombieSprite::zombieLostHeadAttackAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 9; i++)
	{
		images.pushBack(_normalZombieCache->getSpriteFrameByName(StringUtils::format("ZombieLostHeadAttack_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 9);
	this->_zombieLostHeadAttackAction = RepeatForever::create(Animate::create(_animation));
	return this->_zombieLostHeadAttackAction;
}
