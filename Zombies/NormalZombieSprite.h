#pragma once
#include "cocos2d.h"
#include "ZombieBaseClass.h"
USING_NS_CC;
#include <string>
using namespace std;
class NormalZombieSprite : public ZombieBaseClass
{
public:
	CREATE_FUNC(NormalZombieSprite);
	NormalZombieSprite();
	~NormalZombieSprite();
	virtual bool init();
	bool attacting;
	RepeatForever* _normalZombieWalkAction;
	RepeatForever* normalZombieWalkAnimation();//僵尸行走动画         1
	FiniteTimeAction* _normalZombieNoHeadWalkAction;
	FiniteTimeAction* normalZombieNoHeadWalkAnimation();//无头僵尸行走  2
	RepeatForever* _normalZombieAttackAction;
	RepeatForever* normalZombieAttackAnimation();//吃植物动画           3
	RepeatForever* _normalZombieLostHeadAttackAction;
	RepeatForever* normalZombieLostHeadAttackAnimation();//无头僵尸吃植物动画  4
	

	RepeatForever* _flagZombieWalkAction;
	RepeatForever* flagZombieWalkAnimation();//僵尸行走动画   5
	FiniteTimeAction* _flagZombieNoHeadWalkAction;
	FiniteTimeAction* flagZombieNoHeadWalkAnimation();//无头僵尸行走   6
	RepeatForever* _flagZombieAttackAction;
	RepeatForever* flagZombieAttackAnimation();//吃植物动画           7
	RepeatForever* _flagZombieLostHeadAttackAction;
	RepeatForever* flagZombieLostHeadAttackAnimation();//无头僵尸吃植物动画    8
	

	RepeatForever* _coneheadZombieWalkAction;
	RepeatForever* coneheadZombieWalkAnimation();//僵尸行走动画     9
	RepeatForever* _coneheadZombieAttackAction;
	RepeatForever* coneheadZombieAttackAnimation();//吃植物动画    10

	RepeatForever* _bucketheadZombieWalkAction;
	RepeatForever* bucketheadZombieWalkAnimation();//僵尸行走动画   11
	RepeatForever* _bucketheadZombieAttackAction;
	RepeatForever* bucketheadZombieAttackAnimation();//吃植物动画   12
	//ZombieMoveWay  13
	//headAnimation 14
	//downTheGround 15
	//exploadAnimation 16


	void startMusic();
	void stopMusic();
	unsigned int _effectMusicID;
	
	//表明僵尸正在执行什么动作、

	//walk 1
	//attack 2
	//noHeadAttack 3
	//dropHead 4
	//noHeadWalk 5
	//die 6
	//boomDie 7
};
