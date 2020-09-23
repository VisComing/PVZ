#pragma once
#include "cocos2d.h"
USING_NS_CC;

class ZombieBaseClass : public Sprite
{
public:
	CREATE_FUNC(ZombieBaseClass);
	ZombieBaseClass();
	~ZombieBaseClass();
	virtual bool init();
	int _hp;
};