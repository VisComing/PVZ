#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include <string>
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
	
	void produceNormalZombieSprite(string, Vec2);
	void produceZombieUpdate(float dlt);
};