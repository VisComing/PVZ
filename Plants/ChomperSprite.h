#pragma once
#include "PlantBaseClass.h"
#include "cocos2d.h"
USING_NS_CC;

class ChomperSprite : public PlantBaseClass
{
public:
	CREATE_FUNC(ChomperSprite);
	ChomperSprite();
	~ChomperSprite();
	bool init() override;
	FiniteTimeAction * chomperAttack();
	FiniteTimeAction * chomperAttackAction;
	RepeatForever * chomperDigest();
	RepeatForever * chomperDigestAction;
	RepeatForever * chomperNormal();
	RepeatForever * chomperNormalAction;
	bool _eatingZombie;
	Rect plantBounding();
	Rect _chomperRect;
	int _ateTime;
	const int _ateDownTime = 500;
	int _chomperSpriteTag;
};