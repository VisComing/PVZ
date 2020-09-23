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
	if (!Sprite::init())	return false;
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/zombie.plist");
	Sprite::createWithSpriteFrameName("Zombie_1.png");
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 22; i++)
	{
		images.pushBack(cache->getSpriteFrameByName(StringUtils::format("Zombie_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 22);
	this->runAction(RepeatForever::create(Animate::create(_animation)));
	return true;
}