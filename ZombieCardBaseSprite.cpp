#include "ZombieCardBaseSprite.h"

ZombieCardBaseSprite::ZombieCardBaseSprite()
{
}

ZombieCardBaseSprite::~ZombieCardBaseSprite()
{
}

bool ZombieCardBaseSprite::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}
