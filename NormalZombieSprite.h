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
	Rect NormalZombieBounding();//���ý�ʬ��boundingBox
	Rect _normalZombieRect;//���ú��
	bool attacting;
	FiniteTimeAction* _walkAction;
	FiniteTimeAction* _headAction;//ͷ��صĶ���
	FiniteTimeAction* _noHeadAction;
	FiniteTimeAction* headAnimation();
	FiniteTimeAction* noHeadAnimation();
	FiniteTimeAction* downTheGround();
	FiniteTimeAction* _downAction;
	FiniteTimeAction* explodAction();
	FiniteTimeAction* _explodAction;
	RepeatForever* attackAnimation();//��ֲ�ﶯ��
	RepeatForever* _attackAction;
};
