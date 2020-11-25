#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include <vector>
#include <string>
using namespace std;
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
	Rect _zombieRect;
	SpriteFrameCache* _normalZombieCache;
	SpriteFrameCache* _boomDie1;
	SpriteFrameCache* _armedNormalZombieCache;

	int _position[2];//僵尸的位置,第一个表示第几列（共9列），第二个表示第几行（共5行）
	int typeOfDeath;
	FiniteTimeAction* explodAnimation();//爆炸动画，僵尸通用
	FiniteTimeAction* _explodAction;
	const int noHeadHp = 10;//血量为10时，头掉
	FiniteTimeAction* _headAction;//头落地的动画
	FiniteTimeAction* headAnimation();//头落地，多个僵尸可以复用
	FiniteTimeAction* downTheGround();//僵尸倒地动作，多个僵尸可以复用
	FiniteTimeAction* _downAction;
	Action* zombieMoveWay(int zombieSpeed = 40);//僵尸向前移动,基础speed为40，越大，僵尸速度越快
	Action* _moveWayAction;
	int zombieSpeed;//僵尸的移动速度，越贵的僵尸移速越快
	int zombieMoney;//僵尸金币价格
	int _hp;//僵尸的血量
	string _zombieName;
	int zombieID;
	vector<int> actionTag;
};