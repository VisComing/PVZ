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
	void initNormalZombieSprite(Vec2 touch, string zombieName = "");//��ʼ����ʬ
	//void normalZombieMoveWay();//��ʬ�ƶ�·��
	//FiniteTimeAction* noHeadNormalZombieMoveWay();
	Vector<NormalZombieSprite*> _normalZombieVector;
	void diedNormalZombie(float);
	void normalZombieAttackPlant();
	void update(float dt) override;
	void autoInitZombie(string, Vec2);
	//Sprite* tmpSprite;
	bool isZombieWin();
	int zombieID;//��ʬΨһ��־
	void sendZombieStatus(float);
	void delectZombieFromNormalZombieVector(int ID);
};