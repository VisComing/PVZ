#pragma once
#include "PlantBaseClass.h"
#include "cocos2d.h"
USING_NS_CC;

class PeaShooterSprite : public PlantBaseClass
{
public:
	CREATE_FUNC(PeaShooterSprite);
	PeaShooterSprite();
	~PeaShooterSprite();
	virtual bool init();
	int _peaShooterSpriteTag;
};