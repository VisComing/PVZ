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
	Rect zombieBounding();//���ý�ʬ��boundingBox
	Rect _flagZombieRect;//���ú��
	bool attacting;
	RepeatForever* _walkAction;
	RepeatForever* walkAnimation();//��ʬ���߶���
	FiniteTimeAction* _noHeadWalkAction;
	FiniteTimeAction* noHeadWalkAnimation();
	FiniteTimeAction* _explodAction;
	RepeatForever* attackAnimation();//��ֲ�ﶯ��
	RepeatForever* _attackAction;
	//Action* flagZombieMoveWay();//��ʬ��ǰ�ƶ�
	//Action* _moveWayAction;
	RepeatForever* flagZombieLostHeadAttackAnimation();//��ͷ��ʬ��ֲ�ﶯ��
	RepeatForever* _flagZombieLostHeadAttackAction;
};
