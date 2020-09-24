#pragma once
#include "cocos2d.h"
#include "PeaShooterSprite.h"
//#include "GameLayer.h"
USING_NS_CC;
class PeaShooterLayer : public Layer
{
public:
	CREATE_FUNC(PeaShooterLayer);
	PeaShooterLayer();
	~PeaShooterLayer();
	virtual bool init();
	//SpriteFrameCache* _peaShooterCache;
	PeaShooterSprite* _peaShooterSprite;
	void initPeaShooterSprite(Touch*);//初始化豌豆射手，，出一个触摸点给它

};
