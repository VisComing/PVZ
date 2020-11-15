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
	void initChomperSprite(Touch*);//��ʼ���㶹���֣���һ�����������
	void chomperAttackZombie();
	void diedChomper();
	virtual void update(float dt);
	Vector<ChomperSprite*> _chomperVector;
};