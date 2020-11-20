#pragma once
#include "PlantBaseClass.h"
#include "cocos2d.h"
USING_NS_CC;

class SunFlowerSprite : public PlantBaseClass
{
public:
	CREATE_FUNC(SunFlowerSprite);
	SunFlowerSprite();
	~SunFlowerSprite();
	virtual bool init();
	int _sunFlowerSpriteTag;
	int _sunCellTime;//每隔10秒产生一个太阳因子
};