#pragma once
#include "cocos2d.h"
#include "MapLayer.h"
#include "DollarDisplayLayer.h"
#include "SunCellLayer.h"
USING_NS_CC;
class GameLayer : public Layer
{
public:
	CREATE_FUNC(GameLayer);

	virtual bool init();
	void initMapLayer();//初始化地图
	GameLayer();
	~GameLayer();
	void initDollarDisplayerLayer();
	virtual void update(float dt);//监听所有变化的事物,每一帧都会执行该函数
	SunCellLayer* _sunCellLayer;
	void initSunCellLayer();
	Sprite* _bgSprite;
	SpriteFrameCache* _cache;
	MapLayer* _mapLayer;
	DollarDisplayLayer* _dollarDisplayLayer;
};