#pragma once
#include "cocos2d.h"
#include "NormalZombieSprite.h"
#include "PeaShooterSprite.h"
//头文件包含问题 意外的标记位于;之前  
USING_NS_CC;

class BoundingLayer : public Layer
{
public:
	CREATE_FUNC(BoundingLayer);
	BoundingLayer();
	~BoundingLayer();
	virtual bool init();
	void bulletBoundingZombie();//子弹碰撞僵尸
	void zombieEatPlant();//僵尸攻击植物	
	void BoundingLayer::zombieEatPlant(ZombieBaseClass * zombieBase, PlantBaseClass * plantBase);
private:
	Map<NormalZombieSprite*, PeaShooterSprite*> zombieAttackPeaShooter;
};