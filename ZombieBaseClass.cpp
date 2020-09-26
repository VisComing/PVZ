#include "ZombieBaseClass.h"
ZombieBaseClass::ZombieBaseClass()
{
	_normalZombieCache = SpriteFrameCache::getInstance();
	_normalZombieCache->addSpriteFramesWithFile("res/zombie.plist");
}
ZombieBaseClass::~ZombieBaseClass()
{

}
bool ZombieBaseClass::init()
{
	if (!Sprite::init()) return false;

	return true;
}