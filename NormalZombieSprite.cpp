#include "NormalZombieSprite.h"

NormalZombieSprite::NormalZombieSprite()
{
	this->_hp = 100;

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