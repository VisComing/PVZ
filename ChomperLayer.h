#pragma once
#include "cocos2d.h"
#include "ChomperSprite.h"
using namespace std;
USING_NS_CC;
class ChomperLayer : public Layer
{
public:
	CREATE_FUNC(ChomperLayer);
	ChomperLayer();
	~ChomperLayer();
	virtual bool init();
	ChomperSprite* _chomperSprite;
	void initChomperSprite(Touch*);//初始化豌豆射手，传一个触摸点给它
	void chomperAttackZombie();
	void diedChomper();
	virtual void update(float dt);
	Vector<ChomperSprite*> _chomperVector;
};