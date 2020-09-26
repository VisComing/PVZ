#pragma once
#include "cocos2d.h"
USING_NS_CC;

class ZombieCardBaseSprite : public Sprite
{
public:
	CREATE_FUNC(ZombieCardBaseSprite);
	ZombieCardBaseSprite();
	~ZombieCardBaseSprite();
	virtual bool init();
};