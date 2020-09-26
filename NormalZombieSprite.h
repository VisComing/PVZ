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
	Rect NormalZombieBounding();//重置僵尸的boundingBox
	Rect _normalZombieRect;//重置后的

	FiniteTimeAction* _walkAction;
	FiniteTimeAction* _headAction;//头落地的动画
	FiniteTimeAction* _noHeadAction;
	FiniteTimeAction* headAnimation();
	FiniteTimeAction* noHeadAnimation();
	FiniteTimeAction* downTheGround();
	FiniteTimeAction* _downAction;
};
