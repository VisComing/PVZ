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
	void initNormalZombieSprite(Vec2 touch, string zombieName = "");//��ʼ����ʬ
	//void normalZombieMoveWay();//��ʬ�ƶ�·��
	//FiniteTimeAction* noHeadNormalZombieMoveWay();
	Vector<NormalZombieSprite*> _normalZombieVector;
	void diedNormalZombie();
	void normalZombieAttackPlant();
	virtual void update(float dt);
	void autoInitZombie(string, Vec2);
	//Sprite* tmpSprite;
	bool isZombieWin();
};