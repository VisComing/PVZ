#pragma once
#include "cocos2d.h"
USING_NS_CC;

class SunCellSprite :public  Sprite
{
public:
	CREATE_FUNC(SunCellSprite);
	SunCellSprite(void);
	~SunCellSprite(void);
	virtual bool init();
	//Sprite* _sunSprite;
	static Rect getRect(Node*);
};
