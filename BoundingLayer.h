#pragma once
#include "cocos2d.h"
#include "NormalZombieSprite.h"
#include "PeaShooterSprite.h"
#include "PotatoMineSprite.h"
//ͷ�ļ��������� ����ı��λ��;֮ǰ  
USING_NS_CC;

class BoundingLayer : public Layer
{
public:
	CREATE_FUNC(BoundingLayer);
	BoundingLayer();
	~BoundingLayer();
	virtual bool init();
	void bulletBoundingZombie();//�ӵ���ײ��ʬ
	void zombieEatPlant();//��ʬ����ֲ��	
	void BoundingLayer::zombieEatPlantT();
	//void BoundingLayer::zombieEatPlantT(ZombieBaseClass * zombieBase, PlantBaseClass * plantBase);
private:
	Map<NormalZombieSprite*, PeaShooterSprite*> zombieAttackPeaShooter;
	Map<NormalZombieSprite*, PotatoMineSprite*> zombieAttackPotatoMine;
	Map< ZombieBaseClass*, PlantBaseClass*> zombieAttackPlant;
};