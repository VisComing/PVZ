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
	bool init() override;
	//CardSprite* _cardSprte;
	void initCardSprite();//³õÊ¼»¯Ö²Îï¿¨
};
