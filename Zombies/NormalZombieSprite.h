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
	string _zombieName;
	RepeatForever* _normalZombieWalkAction;
	RepeatForever* normalZombieWalkAnimation();//僵尸行走动画
	FiniteTimeAction* _normalZombieNoHeadWalkAction;
	FiniteTimeAction* normalZombieNoHeadWalkAnimation();//无头僵尸行走
	RepeatForever* _normalZombieAttackAction;
	RepeatForever* normalZombieAttackAnimation();//吃植物动画
	RepeatForever* _normalZombieLostHeadAttackAction;
	RepeatForever* normalZombieLostHeadAttackAnimation();//无头僵尸吃植物动画
	

	RepeatForever* _flagZombieWalkAction;
	RepeatForever* flagZombieWalkAnimation();//僵尸行走动画
	FiniteTimeAction* _flagZombieNoHeadWalkAction;
	FiniteTimeAction* flagZombieNoHeadWalkAnimation();//无头僵尸行走
	RepeatForever* _flagZombieAttackAction;
	RepeatForever* flagZombieAttackAnimation();//吃植物动画
	RepeatForever* _flagZombieLostHeadAttackAction;
	RepeatForever* flagZombieLostHeadAttackAnimation();//无头僵尸吃植物动画
	

	RepeatForever* _coneheadZombieWalkAction;
	RepeatForever* coneheadZombieWalkAnimation();//僵尸行走动画
	RepeatForever* _coneheadZombieAttackAction;
	RepeatForever* coneheadZombieAttackAnimation();//吃植物动画

	RepeatForever* _bucketheadZombieWalkAction;
	RepeatForever* bucketheadZombieWalkAnimation();//僵尸行走动画
	RepeatForever* _bucketheadZombieAttackAction;
	RepeatForever* bucketheadZombieAttackAnimation();//吃植物动画

	void startMusic();
	void stopMusic();
	unsigned int _effectMusicID;
};
