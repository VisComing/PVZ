#pragma once
#include "PlantBaseClass.h"
#include "cocos2d.h"
USING_NS_CC;

class PotatoMineSprite : public PlantBaseClass
{
public:
	CREATE_FUNC(PotatoMineSprite);
	PotatoMineSprite();
	~PotatoMineSprite();
	virtual bool init();
	Action* _potatoMineGrow;
	Vector<SpriteFrame*> images;
	int _potatoMineTime;
};