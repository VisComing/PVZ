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
	Rect zombieBounding();//���ý�ʬ��boundingBox
	Rect _normalZombieRect;//���ú��
	bool attacting;
	RepeatForever* _walkAction;
	RepeatForever* walkAnimation();//��ʬ���߶���
	FiniteTimeAction* _headAction;//ͷ��صĶ���
	FiniteTimeAction* _noHeadWalkAction;
	FiniteTimeAction* headAnimation();
	FiniteTimeAction* noHeadWalkAnimation();
	FiniteTimeAction* downTheGround();
	FiniteTimeAction* _downAction;
	//FiniteTimeAction* explodAction();
	FiniteTimeAction* _explodAction;
	RepeatForever* attackAnimation();//��ֲ�ﶯ��
	RepeatForever* _attackAction;
	Action* normalZombieMoveWay();//��ʬ��ǰ�ƶ�
	Action* _moveWayAction;
	RepeatForever* zombieLostHeadAttackAnimation();//��ֲ�ﶯ��
	RepeatForever* _zombieLostHeadAttackAction;
};
