#pragma once
#include "PlantBaseClass.h"
#include "cocos2d.h"
USING_NS_CC;

class WallNutSprite : public PlantBaseClass
{
public:
	CREATE_FUNC(WallNutSprite);
	WallNutSprite();
	~WallNutSprite();
	virtual bool init();
	RepeatForever * wallNutCracked1();
	RepeatForever * wallNutCracked1Action;
	RepeatForever * wallNutCracked2();
	RepeatForever * wallNutCracked2Action;
};