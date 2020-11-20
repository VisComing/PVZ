#pragma once
#include "cocos2d.h"
#include "SunCellSprite.h"
#include "DollarDisplayLayer.h"
USING_NS_CC;
class SunCellLayer : public Layer
{
public:
	CREATE_FUNC(SunCellLayer);
	SunCellLayer();
	~SunCellLayer();
	virtual bool init();
	SunCellSprite* _sunCellSprite;//Ì«ÑôÒò×Ó¾«Áé
	void initSunCell(float);
	void sunCellMoveWay();
	//void removeSunCell(Node*);
	//void removeSunCell2(Node*);
	bool onTouchBegan(Touch* touch, Event* event);
};