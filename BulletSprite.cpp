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
	return true;
}
