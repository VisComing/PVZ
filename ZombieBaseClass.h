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
	Rect _zombieRect;
	SpriteFrameCache* _normalZombieCache;
	SpriteFrameCache* _boomDie1;
	SpriteFrameCache* _armedNormalZombieCache;
	int _hp;
	int _position[2];//��ʬ��λ��,��һ����ʾ�ڼ��У���9�У����ڶ�����ʾ�ڼ��У���5�У�
	int typeOfDeath;
	FiniteTimeAction* explodAnimation();//��ը��������ʬͨ��
	FiniteTimeAction* _explodAction;
	const int noHeadHp = 10;//Ѫ��Ϊ10ʱ��ͷ��
	FiniteTimeAction* _headAction;//ͷ��صĶ���
	FiniteTimeAction* headAnimation();//ͷ��أ������ʬ���Ը���
	FiniteTimeAction* downTheGround();//��ʬ���ض����������ʬ���Ը���
	FiniteTimeAction* _downAction;
	Action* zombieMoveWay();//��ʬ��ǰ�ƶ�
	Action* _moveWayAction;
};