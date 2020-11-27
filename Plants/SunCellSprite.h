#pragma once
#include "cocos2d.h"
USING_NS_CC;

class SunCellSprite :public  Sprite
{
public:
	CREATE_FUNC(SunCellSprite);
	SunCellSprite(void);
	~SunCellSprite(void);
	bool init() override;
	static Rect getRect(Node*);
};
