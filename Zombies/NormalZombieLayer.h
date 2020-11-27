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
	bool init() override;
	NormalZombieSprite* _normalZombieSprite;
	void initNormalZombieSprite(Vec2 touch, string zombieName = "");//初始化僵尸
	//void normalZombieMoveWay();//僵尸移动路线
	//FiniteTimeAction* noHeadNormalZombieMoveWay();
	Vector<NormalZombieSprite*> _normalZombieVector;
	void diedNormalZombie(float);
	void normalZombieAttackPlant();
	void update(float dt) override;
	void autoInitZombie(string, Vec2);
	//Sprite* tmpSprite;
	bool isZombieWin();
	int zombieID;//僵尸唯一标志
	void sendZombieStatus(float);
	void delectZombieFromNormalZombieVector(int ID);
};