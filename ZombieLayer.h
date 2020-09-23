#pragma once
#include "cocos2d.h"
#include "NormalZombieSprite.h"
USING_NS_CC;
class ZombieLayer : public Layer
{
public:
	CREATE_FUNC(ZombieLayer);
	ZombieLayer();
	~ZombieLayer();
	virtual bool init();
	NormalZombieSprite* _normalZombieSprite;
	void initNormalZombieSprite(float);//初始化僵尸
	void normalZombieMoveWay();//给定僵尸的运动路线
	void removeNormalZombie(Node* pSend);//删除僵尸
};