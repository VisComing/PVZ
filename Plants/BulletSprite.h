#pragma once
#include "cocos2d.h"
USING_NS_CC;

class BulletSprite : public Sprite
{
public:
	CREATE_FUNC(BulletSprite);
	BulletSprite();
	~BulletSprite();
	bool init() override;
	FiniteTimeAction* _bulletBroken;

};