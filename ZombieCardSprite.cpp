#include "ZombieCardSprite.h"

ZombieCardSprite::ZombieCardSprite()
{

}

ZombieCardSprite::~ZombieCardSprite()
{
}

bool ZombieCardSprite::init()
{

	if (!ZombieCardBaseSprite::initWithFile("res/NormalZombie.png"))
	{
		return false;
	}
	return true;
}
