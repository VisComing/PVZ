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
	SpriteFrameCache* _normalZombieCache;
	int _hp;
	int _position[2];//僵尸的位置,第一个表示第几列（共9列），第二个表示第几行（共5行）
};