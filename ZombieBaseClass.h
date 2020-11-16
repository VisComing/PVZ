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
	virtual Rect zombieBounding();//虚函数，子类要实现
	virtual Action* normalZombieMoveWay();//僵尸向前移动
	virtual RepeatForever* walkAnimation();//僵尸行走动画
	SpriteFrameCache* _normalZombieCache;
	SpriteFrameCache* _boomDie1;
	int _hp;
	int _position[2];//僵尸的位置,第一个表示第几列（共9列），第二个表示第几行（共5行）
	int typeOfDeath;
	FiniteTimeAction* explodAnimation();
	FiniteTimeAction* _explodAction;
	const int noHeadHp = 10;//血量为10时，头掉
};