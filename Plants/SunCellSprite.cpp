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
	Sprite::createWithSpriteFrameName("Sun_1.png");
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 22; i++)
	{
		images.pushBack(cache->getSpriteFrameByName(StringUtils::format("Sun_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 22);
	this->runAction(RepeatForever::create(Animate::create(_animation)));
	return true;
}

Rect SunCellSprite::getRect(Node* pNode)
{
	Rect rc;
	rc.origin = pNode->getPosition();
	rc.size = pNode->getContentSize();
	rc.origin.x -= rc.size.width*0.5;
	rc.origin.y -= rc.size.height*0.5;
	return  rc;
}