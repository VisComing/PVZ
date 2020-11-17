#pragma once
#include "cocos2d.h"
#include "NormalZombieSprite.h"
USING_NS_CC;
#include <string>
using namespace std;
class NormalZombieLayer : public Layer
{
public:
	CREATE_FUNC(NormalZombieLayer);
	NormalZombieLayer();
	~NormalZombieLayer();
	virtual bool init();
	NormalZombieSprite* _normalZombieSprite;
	void initNormalZombieSprite(Touch* touch, string zombieName = "");//初始化僵尸
	//void normalZombieMoveWay();//僵尸移动路线
	//FiniteTimeAction* noHeadNormalZombieMoveWay();
	Vector<NormalZombieSprite*> _normalZombieVector;
	void diedNormalZombie();
	void normalZombieAttackPlant();
	virtual void update(float dt);
	//Sprite* tmpSprite;
};