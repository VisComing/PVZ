#include "SunCellSprite.h"

SunCellSprite::SunCellSprite()
{

}

SunCellSprite::~SunCellSprite()
{

}

bool SunCellSprite::init()
{
	if(!Sprite::init())	return false;
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/sun.plist");
	_sunSprite = Sprite::createWithSpriteFrameName("Sun_1.png");
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 22; i++)
	{
		images.pushBack(cache->getSpriteFrameByName(StringUtils::format("Sun_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 22);
	_sunSprite->runAction(RepeatForever::create(Animate::create(_animation)));
	return true;
}