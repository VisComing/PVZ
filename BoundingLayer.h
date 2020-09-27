#pragma once
#include "cocos2d.h"
USING_NS_CC;

class BoundingLayer : public Layer
{
public:
	CREATE_FUNC(BoundingLayer);
	BoundingLayer();
	~BoundingLayer();
	virtual bool init();
	void bulletBoundingZombie();//×Óµ¯Åö×²½©Ê¬
	void zombieEatPlant();//½©Ê¬¹¥»÷Ö²Îï
};