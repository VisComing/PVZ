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
	bool init() override;
	RepeatForever * wallNutCracked1();
	RepeatForever * wallNutCracked1Action;
	RepeatForever * wallNutCracked2();
	RepeatForever * wallNutCracked2Action;
	int _wallNutSpriteTag;//表明该精灵的编号
};