#pragma once
#include "cocos2d.h"
#include "NormalZombieSprite.h"
USING_NS_CC;
class NormalZombieLayer : public Layer
{
public:
	CREATE_FUNC(NormalZombieLayer);
	NormalZombieLayer();
	~NormalZombieLayer();
	virtual bool init();
	NormalZombieSprite* _normalZombieSprite;
	void initNormalZombieSprite(Touch* touch);//��ʼ����ʬ
	void normalZombieMoveWay();//��ʬ�ƶ�·��
	FiniteTimeAction* noHeadNormalZombieMoveWay();
	Vector<NormalZombieSprite*> _normalZombieVector;
	void diedNormalZombie();
	virtual void update(float dt);
};