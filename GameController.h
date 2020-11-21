#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include <string>
#include <set>
using namespace std;
class GameController : public Layer
{
public:
	CREATE_FUNC(GameController);
	GameController();
	~GameController();	
	virtual bool init();
	virtual void update(float dt);
	void produceChomperSprite(Vec2);
	void producePeaShooterSprite(Vec2);
	void producePotatoMineSprite(Vec2);
	void produceWallNutSprite(Vec2);
	void produceSunFlowerSprite(Vec2);

	void produceNormalZombieSprite(string, Vec2);
	void produceZombieUpdate(float dlt);
	void remainTimeMinueOneSecond(float dlt);

	int _remainingTime;
	Label* _remainTimeLabel;

	void isZombieWin(float dlt);

	int firstFiveZombie;
	set<int> firstFiveZombieNotInSameLine;

	void receiveFromServer(float dlt);
};