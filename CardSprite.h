#pragma once
#include "cocos2d.h"
#include "CardBaseSprite.h"
USING_NS_CC;

class CardSprite : public CardBaseSprite
{
public:
	CREATE_FUNC(CardSprite);
	CardSprite();
	~CardSprite();
	virtual bool init();
};