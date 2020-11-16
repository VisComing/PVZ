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
	Rect zombieBounding();//重置僵尸的boundingBox
	Rect _normalZombieRect;//重置后的
	bool attacting;
	RepeatForever* _walkAction;
	RepeatForever* walkAnimation();//僵尸行走动画
	FiniteTimeAction* _headAction;//头落地的动画
	FiniteTimeAction* _noHeadWalkAction;
	FiniteTimeAction* headAnimation();
	FiniteTimeAction* noHeadWalkAnimation();
	FiniteTimeAction* downTheGround();
	FiniteTimeAction* _downAction;
	//FiniteTimeAction* explodAction();
	FiniteTimeAction* _explodAction;
	RepeatForever* attackAnimation();//吃植物动画
	RepeatForever* _attackAction;
	Action* normalZombieMoveWay();//僵尸向前移动
	Action* _moveWayAction;
	RepeatForever* zombieLostHeadAttackAnimation();//吃植物动画
	RepeatForever* _zombieLostHeadAttackAction;
};
