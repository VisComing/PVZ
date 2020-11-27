#include "TouchLayer.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "global.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
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
	listener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
	//listener->onTouchEnded = CC_CALLBACK_2(TouchLayer::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	return true;
}

bool TouchLayer::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void TouchLayer::onTouchEnded(Touch* touch, Event* event)
{
	//我是植物方，或者是单机模式
	if (_iAmPlantSideGolbalVariable == true || isSinglePlayerGameMode == true)
	{
		if ((dynamic_cast<GameLayer*>(this->getParent()))->_cardLayer->getChildByName("PeaShooterCard")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			
			if ((dynamic_cast<GameLayer*>(this->getParent()))->_dollarDisplayLayer->_dollar >= 100)
			{
				SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
				(dynamic_cast<GameLayer*>(this->getParent()))->_peaShooterLayer->initPeaShooterSprite(touch->getLocation());
			}
			else SimpleAudioEngine::getInstance()->playEffect("res/music/noEnoughMoney.wma");
		}
		if ((dynamic_cast<GameLayer*>(this->getParent()))->_cardLayer->getChildByName("PotatoMineCard")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			
			if ((dynamic_cast<GameLayer*>(this->getParent()))->_dollarDisplayLayer->_dollar >= 25)
			{
				SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
				(dynamic_cast<GameLayer*>(this->getParent()))->_potatoMineLayer->initPotatoMineSprite(touch->getLocation());
			}
			else SimpleAudioEngine::getInstance()->playEffect("res/music/noEnoughMoney.wma");
		}
		if ((dynamic_cast<GameLayer*>(this->getParent()))->_cardLayer->getChildByName("WallNutCard")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			if ((dynamic_cast<GameLayer*>(this->getParent()))->_dollarDisplayLayer->_dollar >= 50)
			{
				SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
				(dynamic_cast<GameLayer*>(this->getParent()))->_wallNutLayer->initWallNutSprite(touch->getLocation());
			}
			else SimpleAudioEngine::getInstance()->playEffect("res/music/noEnoughMoney.wma");
		}
		if ((dynamic_cast<GameLayer*>(this->getParent()))->_cardLayer->getChildByName("ChomperCard")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			if ((dynamic_cast<GameLayer*>(this->getParent()))->_dollarDisplayLayer->_dollar >= 150)
			{
				SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
				(dynamic_cast<GameLayer*>(this->getParent()))->_chomperLayer->initChomperSprite(touch->getLocation());
			}
			else SimpleAudioEngine::getInstance()->playEffect("res/music/noEnoughMoney.wma");
		}
		if ((dynamic_cast<GameLayer*>(this->getParent()))->_cardLayer->getChildByName("SunFlowerCard")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			if ((dynamic_cast<GameLayer*>(this->getParent()))->_dollarDisplayLayer->_dollar >= 50)
			{
				SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
				(dynamic_cast<GameLayer*>(this->getParent()))->_sunFlowerLayer->initSunFlowerSprite(touch->getLocation());
			}
			else SimpleAudioEngine::getInstance()->playEffect("res/music/noEnoughMoney.wma");
		}
		if ((dynamic_cast<GameLayer*>(this->getParent()))->_cardLayer->getChildByName("Shovel")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			SimpleAudioEngine::getInstance()->playEffect("res/music/shovel.wma");
			(dynamic_cast<GameLayer*>(this->getParent()))->_peaShooterLayer->removePlant(touch->getLocation());
		}
	}
	//我是僵尸方
	else if(_iAmPlantSideGolbalVariable == false && isSinglePlayerGameMode == false)
	{
		
		if ((dynamic_cast<GameLayer*>(this->getParent()))->_zombieCardLayer->getChildByName("NormalZombieCard")->getBoundingBox().containsPoint(touch->getLocation()))
		{
			
			if ((dynamic_cast<GameLayer*>(this->getParent()))->_dollarDisplayLayer->_dollar >= 100)
			{
				SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
				(dynamic_cast<GameLayer*>(this->getParent()))->_normalZombieLayer->initNormalZombieSprite(touch->getLocation(), "NormalZombie");
			}
			else SimpleAudioEngine::getInstance()->playEffect("res/music/noEnoughMoney.wma");
		}
		if ((dynamic_cast<GameLayer*>(this->getParent()))->_zombieCardLayer->getChildByName("FlagZombieCard")->getBoundingBox().containsPoint(touch->getLocation()))
		{
			
			if ((dynamic_cast<GameLayer*>(this->getParent()))->_dollarDisplayLayer->_dollar >= 120)
			{
				SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
				(dynamic_cast<GameLayer*>(this->getParent()))->_normalZombieLayer->initNormalZombieSprite(touch->getLocation(), "FlagZombie");
			}
			else SimpleAudioEngine::getInstance()->playEffect("res/music/noEnoughMoney.wma");
		}
		if ((dynamic_cast<GameLayer*>(this->getParent()))->_zombieCardLayer->getChildByName("ConeheadZombieCard")->getBoundingBox().containsPoint(touch->getLocation()))
		{
			if ((dynamic_cast<GameLayer*>(this->getParent()))->_dollarDisplayLayer->_dollar >= 150)
			{
				SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
				(dynamic_cast<GameLayer*>(this->getParent()))->_normalZombieLayer->initNormalZombieSprite(touch->getLocation(), "ConeheadZombie");
			}
			else SimpleAudioEngine::getInstance()->playEffect("res/music/noEnoughMoney.wma");
		}
		if ((dynamic_cast<GameLayer*>(this->getParent()))->_zombieCardLayer->getChildByName("BucketheadZombieCard")->getBoundingBox().containsPoint(touch->getLocation()))
		{
			if ((dynamic_cast<GameLayer*>(this->getParent()))->_dollarDisplayLayer->_dollar >= 175)
			{
				SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
				(dynamic_cast<GameLayer*>(this->getParent()))->_normalZombieLayer->initNormalZombieSprite(touch->getLocation(), "BucketheadZombie");
			}
			else SimpleAudioEngine::getInstance()->playEffect("res/music/noEnoughMoney.wma");
		}
	}
	return;
	
}