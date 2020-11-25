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
	RepeatForever* normalZombieWalkAnimation();//��ʬ���߶���         1
	FiniteTimeAction* _normalZombieNoHeadWalkAction;
	FiniteTimeAction* normalZombieNoHeadWalkAnimation();//��ͷ��ʬ����  2
	RepeatForever* _normalZombieAttackAction;
	RepeatForever* normalZombieAttackAnimation();//��ֲ�ﶯ��           3
	RepeatForever* _normalZombieLostHeadAttackAction;
	RepeatForever* normalZombieLostHeadAttackAnimation();//��ͷ��ʬ��ֲ�ﶯ��  4
	

	RepeatForever* _flagZombieWalkAction;
	RepeatForever* flagZombieWalkAnimation();//��ʬ���߶���   5
	FiniteTimeAction* _flagZombieNoHeadWalkAction;
	FiniteTimeAction* flagZombieNoHeadWalkAnimation();//��ͷ��ʬ����   6
	RepeatForever* _flagZombieAttackAction;
	RepeatForever* flagZombieAttackAnimation();//��ֲ�ﶯ��           7
	RepeatForever* _flagZombieLostHeadAttackAction;
	RepeatForever* flagZombieLostHeadAttackAnimation();//��ͷ��ʬ��ֲ�ﶯ��    8
	

	RepeatForever* _coneheadZombieWalkAction;
	RepeatForever* coneheadZombieWalkAnimation();//��ʬ���߶���     9
	RepeatForever* _coneheadZombieAttackAction;
	RepeatForever* coneheadZombieAttackAnimation();//��ֲ�ﶯ��    10

	RepeatForever* _bucketheadZombieWalkAction;
	RepeatForever* bucketheadZombieWalkAnimation();//��ʬ���߶���   11
	RepeatForever* _bucketheadZombieAttackAction;
	RepeatForever* bucketheadZombieAttackAnimation();//��ֲ�ﶯ��   12
	//ZombieMoveWay  13
	//headAnimation 14
	//downTheGround 15
	//exploadAnimation 16


	void startMusic();
	void stopMusic();
	unsigned int _effectMusicID;
	
	//������ʬ����ִ��ʲô������

	//walk 1
	//attack 2
	//noHeadAttack 3
	//dropHead 4
	//noHeadWalk 5
	//die 6
	//boomDie 7
};
