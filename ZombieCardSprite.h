#pragma once
#include "cocos2d.h"
#include "ZombieCardBaseSprite.h"
USING_NS_CC;

class ZombieCardSprite : public ZombieCardBaseSprite
{
public:
	CREATE_FUNC(ZombieCardSprite);
	ZombieCardSprite();
	~ZombieCardSprite();
	virtual bool init();
};