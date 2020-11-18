#pragma once
#include "cocos2d.h"
#include "WallNutSprite.h"
using namespace std;
USING_NS_CC;
class WallNutLayer : public Layer
{
public:
	CREATE_FUNC(WallNutLayer);
	WallNutLayer();
	~WallNutLayer();
	virtual bool init();
	WallNutSprite* _wallNutSprite;
	void initWallNutSprite(Vec2);//初始化豌豆射手，传一个触摸点给它
	void diedWallNut();
	virtual void update(float dt);
	Vector<WallNutSprite*> _wallNutVector;
	int shadowTag;
};