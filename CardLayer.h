#pragma once
#include "cocos2d.h"
//#include "CardSprite.h"
USING_NS_CC;

class CardLayer : public Layer
{
public:
	CREATE_FUNC(CardLayer);
	CardLayer();
	~CardLayer();
	virtual bool init();
	//CardSprite* _cardSprte;
	void initCardSprite();//³õÊ¼»¯Ö²Îï¿¨
};
