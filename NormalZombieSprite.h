#pragma once
#include "cocos2d.h"
#include "ZombieBaseClass.h"
USING_NS_CC;

class NormalZombieSprite : public ZombieBaseClass
{
public:
	CREATE_FUNC(NormalZombieSprite);
	NormalZombieSprite();
	~NormalZombieSprite();
	virtual bool init();

};
