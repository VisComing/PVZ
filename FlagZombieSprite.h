#pragma once
#include "cocos2d.h"
#include "ZombieBaseClass.h"
USING_NS_CC;

class FlagZombieSprite : public ZombieBaseClass
{
public:
	CREATE_FUNC(FlagZombieSprite);
	FlagZombieSprite();
	~FlagZombieSprite();
	virtual bool init();
	Rect zombieBounding();//重置僵尸的boundingBox
	Rect _flagZombieRect;//重置后的
	bool attacting;
	RepeatForever* _walkAction;
	RepeatForever* walkAnimation();//僵尸行走动画
	FiniteTimeAction* _noHeadWalkAction;
	FiniteTimeAction* noHeadWalkAnimation();
	FiniteTimeAction* _explodAction;
	RepeatForever* attackAnimation();//吃植物动画
	RepeatForever* _attackAction;
	//Action* flagZombieMoveWay();//僵尸向前移动
	//Action* _moveWayAction;
	RepeatForever* flagZombieLostHeadAttackAnimation();//无头僵尸吃植物动画
	RepeatForever* _flagZombieLostHeadAttackAction;
};
