#include "ZombieBaseClass.h"
ZombieBaseClass::ZombieBaseClass()
{
	_normalZombieCache = SpriteFrameCache::getInstance();
	_normalZombieCache->addSpriteFramesWithFile("res/zombie.plist");
	_boomDie1 = SpriteFrameCache::getInstance();
	_boomDie1->addSpriteFramesWithFile("res/boomdie1.plist");
	_armedNormalZombieCache = SpriteFrameCache::getInstance();
	_armedNormalZombieCache->addSpriteFramesWithFile("res/armednormalzombie.plist");
}
ZombieBaseClass::~ZombieBaseClass()
{

}
bool ZombieBaseClass::init()
{
	if (!Sprite::init()) return false;

	return true;
}

Rect ZombieBaseClass::zombieBounding()
{
	Rect originRect = this->getBoundingBox();
	this->_zombieRect.origin.x = originRect.origin.x + 90;
	this->_zombieRect.origin.y = originRect.origin.y + 20;
	this->_zombieRect.size.width = originRect.size.width - 90;
	this->_zombieRect.size.height = originRect.size.height - 50;
	return this->_zombieRect;
}



FiniteTimeAction * ZombieBaseClass::explodAnimation()
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

FiniteTimeAction * ZombieBaseClass::headAnimation()
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

FiniteTimeAction * ZombieBaseClass::downTheGround()
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

Action * ZombieBaseClass::zombieMoveWay()
{
	_moveWayAction = MoveTo::create(this->getPositionX() / 40, Vec2(0, this->getPositionY()));
	return _moveWayAction;
}
