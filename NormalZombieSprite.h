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
	RepeatForever* normalZombieWalkAnimation();//��ʬ���߶���
	FiniteTimeAction* _normalZombieNoHeadWalkAction;
	FiniteTimeAction* normalZombieNoHeadWalkAnimation();//��ͷ��ʬ����
	RepeatForever* _normalZombieAttackAction;
	RepeatForever* normalZombieAttackAnimation();//��ֲ�ﶯ��
	RepeatForever* _normalZombieLostHeadAttackAction;
	RepeatForever* normalZombieLostHeadAttackAnimation();//��ͷ��ʬ��ֲ�ﶯ��
	

	RepeatForever* _flagZombieWalkAction;
	RepeatForever* flagZombieWalkAnimation();//��ʬ���߶���
	FiniteTimeAction* _flagZombieNoHeadWalkAction;
	FiniteTimeAction* flagZombieNoHeadWalkAnimation();//��ͷ��ʬ����
	RepeatForever* _flagZombieAttackAction;
	RepeatForever* flagZombieAttackAnimation();//��ֲ�ﶯ��
	RepeatForever* _flagZombieLostHeadAttackAction;
	RepeatForever* flagZombieLostHeadAttackAnimation();//��ͷ��ʬ��ֲ�ﶯ��
	

	RepeatForever* _coneheadZombieWalkAction;
	RepeatForever* coneheadZombieWalkAnimation();//��ʬ���߶���
	RepeatForever* _coneheadZombieAttackAction;
	RepeatForever* coneheadZombieAttackAnimation();//��ֲ�ﶯ��

	RepeatForever* _bucketheadZombieWalkAction;
	RepeatForever* bucketheadZombieWalkAnimation();//��ʬ���߶���
	RepeatForever* _bucketheadZombieAttackAction;
	RepeatForever* bucketheadZombieAttackAnimation();//��ֲ�ﶯ��

	void startMusic();
	void stopMusic();
	unsigned int _effectMusicID;
};
