#include "TouchLayer.h"
#include "GameLayer.h"
TouchLayer::TouchLayer()
{
	this->_isCreatePeaShooter = false;
	//this->_bulletCache->addSpriteFramesWithFile("bullet.plist");
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
	//listener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

bool TouchLayer::onTouchBegan(Touch* touch, Event* event)
{
	if (((GameLayer*)this->getParent())->_cardLayer->_cardSprte->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
	{
		//if(((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar >= 100)
			((GameLayer*)this->getParent())->_peaShooterLayer->initPeaShooterSprite(touch);
	}
	if (((GameLayer*)this->getParent())->_zombieCardLayer->_zombieCardSprte->getBoundingBox().containsPoint(touch->getLocation()))
	{
		((GameLayer*)this->getParent())->_zombieLayer->initNormalZombieSprite(touch);
	}
	return true;
}

//void TouchLayer::onTouchEnded(Touch* touch, Event* event)
//{
//	
//	if (_isCreatePeaShooter == true)
//	{
//		((GameLayer*)this->getParent())->_bulletLayer->schedule(schedule_selector(BulletLayer::initBulletSprite), 2.5f);
//	}
//}