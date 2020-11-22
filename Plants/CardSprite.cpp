#include "CardSprite.h"

CardSprite::CardSprite()
{
	
}

CardSprite::~CardSprite()
{
}

bool CardSprite::init()
{

	if (!CardBaseSprite::initWithFile("res/Peashooter.png"))//用这样的初始化方法，可以使该类直接成为一个精灵
		//而不需要在其中添加节点精灵，注意不需要create，是在调用该类使create的  2020/9/24/20：40
	{
		return false;
	}
	return true;
}
