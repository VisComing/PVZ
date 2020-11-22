#pragma once
#include "cocos2d.h"
//#include "ZombieCardSprite.h"
USING_NS_CC;

class ZombieCardLayer : public Layer
{
public:
	CREATE_FUNC(ZombieCardLayer);
	ZombieCardLayer();
	~ZombieCardLayer();
	virtual bool init();
	//ZombieCardSprite* _zombieCardSprte;
	void initZombieCardSprite();//³õÊ¼»¯Ö²Îï¿¨
};
