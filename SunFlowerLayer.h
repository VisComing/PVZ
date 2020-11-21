#pragma once
#include "cocos2d.h"
#include "SunFlowerSprite.h"
using namespace std;
USING_NS_CC;
class SunFlowerLayer : public Layer
{
public:
	CREATE_FUNC(SunFlowerLayer);
	SunFlowerLayer();
	~SunFlowerLayer();
	virtual bool init();
	SunFlowerSprite* _sunFlowerSprite;
	void initSunFlowerSprite(Vec2);//初始化豌豆射手，传一个触摸点给它
	void produceSunFlowerSprite(Vec2);//根据服务器传来的消息，直接种下该植物
	void diedSunFlower();
	virtual void update(float dt);
	Vector<SunFlowerSprite*> _sunFlowerVector;
	int _sunFlowerSpriteTag;
	int shadowTag;
	void produceSunCellSprite(float dlt);
};