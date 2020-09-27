#include "BulletSprite.h"

BulletSprite::BulletSprite()
{
}

BulletSprite::~BulletSprite()
{
}

bool BulletSprite::init()
{
	if (!Sprite::initWithFile("res/BulletPea.png"))
	{
		return false;
	}
	/*Vector<SpriteFrame*> broken;
	SpriteFrame* brokenFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName("res/PeaBulletHit.png");
	
	broken.pushBack(brokenFrame);
	Animation* brokenAnimation = Animation::createWithSpriteFrames(broken, 0.2f);
	this->_bulletBroken = Animate::create(brokenAnimation);*/
	return true;
}


