#pragma once
#include "cocos2d.h"
USING_NS_CC;

class ZombieBaseClass : public Sprite
{
public:
	enum {
		normalDie,
		boomedDie,
	};
	CREATE_FUNC(ZombieBaseClass);
	ZombieBaseClass();
	~ZombieBaseClass();
	virtual bool init();
	virtual Rect zombieBounding();//�麯��������Ҫʵ��
	virtual Action* normalZombieMoveWay();//��ʬ��ǰ�ƶ�
	virtual RepeatForever* walkAnimation();//��ʬ���߶���
	SpriteFrameCache* _normalZombieCache;
	SpriteFrameCache* _boomDie1;
	int _hp;
	int _position[2];//��ʬ��λ��,��һ����ʾ�ڼ��У���9�У����ڶ�����ʾ�ڼ��У���5�У�
	int typeOfDeath;
	FiniteTimeAction* explodAnimation();
	FiniteTimeAction* _explodAction;
	const int noHeadHp = 10;//Ѫ��Ϊ10ʱ��ͷ��
};