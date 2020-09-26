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
	int _position[2];//植物的位置,第一个表示第几列（共9列），第二个表示第几行（共5行）
};
