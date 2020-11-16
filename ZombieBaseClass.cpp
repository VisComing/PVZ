#include "ZombieBaseClass.h"
ZombieBaseClass::ZombieBaseClass()
{
	_normalZombieCache = SpriteFrameCache::getInstance();
	_normalZombieCache->addSpriteFramesWithFile("res/zombie.plist");
	_boomDie1 = SpriteFrameCache::getInstance();
	_boomDie1->addSpriteFramesWithFile("res/boomdie1.plist");
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
	return this->getBoundingBox();
}

Action * ZombieBaseClass::normalZombieMoveWay()
{
	return nullptr;
}

RepeatForever * ZombieBaseClass::walkAnimation()
{
	return nullptr;
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