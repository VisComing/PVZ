#pragma once
#include "cocos2d.h"
USING_NS_CC;

class PlantBaseClass : public Sprite
{
public:
	CREATE_FUNC(PlantBaseClass);
	PlantBaseClass();
	~PlantBaseClass();
	virtual bool init();
	SpriteFrameCache* _peaShooterCache;
	int _plantHP;//植物的生命值
};
