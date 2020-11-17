#include "TouchLayer.h"
#include "GameLayer.h"
#include "GameScene.h"
extern bool _iAmPlantSideGolbalVariable;
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
	//我是植物方
	//if (_iAmPlantSideGolbalVariable == true)
	//{
		if (((GameLayer*)this->getParent())->_cardLayer->getChildByName("PeaShooterCard")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			//if(((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar >= 100)
			((GameLayer*)this->getParent())->_peaShooterLayer->initPeaShooterSprite(touch);
		}
		if (((GameLayer*)this->getParent())->_cardLayer->getChildByName("PotatoMineCard")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			//if(((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar >= 80)
			((GameLayer*)this->getParent())->_potatoMineLayer->initPotatoMineSprite(touch);
		}
		if (((GameLayer*)this->getParent())->_cardLayer->getChildByName("WallNutCard")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			//if(((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar >= 80)
			((GameLayer*)this->getParent())->_wallNutLayer->initWallNutSprite(touch);
		}
		if (((GameLayer*)this->getParent())->_cardLayer->getChildByName("ChomperCard")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			//if(((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar >= 80)
			((GameLayer*)this->getParent())->_chomperLayer->initChomperSprite(touch);
		}
	//}
	//我是僵尸方
	//else
	//{
		if (((GameLayer*)this->getParent())->_zombieCardLayer->getChildByName("NormalZombieCard")->getBoundingBox().containsPoint(touch->getLocation()))
		{
			((GameLayer*)this->getParent())->_normalZombieLayer->initNormalZombieSprite(touch);
		}
	//}
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