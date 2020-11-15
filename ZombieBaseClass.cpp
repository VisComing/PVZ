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
	return Rect();
}

Action * ZombieBaseClass::normalZombieMoveWay()
{
	return nullptr;
}

RepeatForever * ZombieBaseClass::walkAnimation()
{
	return nullptr;
}
