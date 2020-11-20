#include "TouchLayer.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "global.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
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
	//我是植物方
	//if (_iAmPlantSideGolbalVariable == true)
	//{
		if (((GameLayer*)this->getParent())->_cardLayer->getChildByName("PeaShooterCard")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
			//if (((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar >= 100)
				((GameLayer*)this->getParent())->_peaShooterLayer->initPeaShooterSprite(touch->getLocation());
		}
		if (((GameLayer*)this->getParent())->_cardLayer->getChildByName("PotatoMineCard")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
			//if (((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar >= 25)
				((GameLayer*)this->getParent())->_potatoMineLayer->initPotatoMineSprite(touch->getLocation());
		}
		if (((GameLayer*)this->getParent())->_cardLayer->getChildByName("WallNutCard")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
			//if (((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar >= 50)
				((GameLayer*)this->getParent())->_wallNutLayer->initWallNutSprite(touch->getLocation());
		}
		if (((GameLayer*)this->getParent())->_cardLayer->getChildByName("ChomperCard")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
			//if (((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar >= 150)
				((GameLayer*)this->getParent())->_chomperLayer->initChomperSprite(touch->getLocation());
		}
		if (((GameLayer*)this->getParent())->_cardLayer->getChildByName("Shovel")->getBoundingBox().containsPoint(touch->getLocation()))//判断触摸是否发生在植物卡上  
		{
			SimpleAudioEngine::getInstance()->playEffect("res/music/shovel.wma");
			//if (((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar >= 150)
			((GameLayer*)this->getParent())->_peaShooterLayer->removePlant(touch->getLocation());
		}
	//}
	//我是僵尸方
	//else
	//{
		if (isSinglePlayerGameMode == false)
		{
			if (((GameLayer*)this->getParent())->_zombieCardLayer->getChildByName("NormalZombieCard")->getBoundingBox().containsPoint(touch->getLocation()))
			{
				SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
				//if (((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar >= 100)
				((GameLayer*)this->getParent())->_normalZombieLayer->initNormalZombieSprite(touch->getLocation(), "NormalZombie");
			}
			if (((GameLayer*)this->getParent())->_zombieCardLayer->getChildByName("FlagZombieCard")->getBoundingBox().containsPoint(touch->getLocation()))
			{
				SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
				//if (((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar >= 120)
				((GameLayer*)this->getParent())->_normalZombieLayer->initNormalZombieSprite(touch->getLocation(), "FlagZombie");
			}
			if (((GameLayer*)this->getParent())->_zombieCardLayer->getChildByName("ConeheadZombieCard")->getBoundingBox().containsPoint(touch->getLocation()))
			{
				SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
				//if (((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar >= 150)
				((GameLayer*)this->getParent())->_normalZombieLayer->initNormalZombieSprite(touch->getLocation(), "ConeheadZombie");
			}
			if (((GameLayer*)this->getParent())->_zombieCardLayer->getChildByName("BucketheadZombieCard")->getBoundingBox().containsPoint(touch->getLocation()))
			{
				SimpleAudioEngine::getInstance()->playEffect("res/music/clickCard.wma");
				//if (((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar >= 175)
				((GameLayer*)this->getParent())->_normalZombieLayer->initNormalZombieSprite(touch->getLocation(), "BucketheadZombie");
			}
		}
	//}
	return;
	
}