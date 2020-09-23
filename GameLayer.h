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
	void initMapLayer();//��ʼ����ͼ
	GameLayer();
	~GameLayer();
	void initDollarDisplayerLayer();
	virtual void update(float dt);//�������б仯������,ÿһ֡����ִ�иú���
	SunCellLayer* _sunCellLayer;
	void initSunCellLayer();
	Sprite* _bgSprite;
	SpriteFrameCache* _cache;
	MapLayer* _mapLayer;
	DollarDisplayLayer* _dollarDisplayLayer;
};