#include "TouchLayer.h"
#include "GameLayer.h"
TouchLayer::TouchLayer()
{
	this->_isPeaShooter = false;
}

TouchLayer::~TouchLayer()
{
}

bool TouchLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(TouchLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

bool TouchLayer::onTouchBegan(Touch* touch, Event* event)
{
	if (((GameLayer*)this->getParent())->_cardLayer->_cardSprte->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
	{
		((GameLayer*)this->getParent())->_peaShooterLayer->initPeaShooterSprite(touch);
	}
	return true;
}
bool TouchLayer::onMouseMove(Event* event)
{
	return true;
}