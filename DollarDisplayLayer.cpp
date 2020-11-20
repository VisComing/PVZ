#include "DollarDisplayLayer.h"
#include "GameScene.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "global.h"
using namespace CocosDenshion;
extern bool _iAmPlantSideGolbalVariable;
DollarDisplayLayer::DollarDisplayLayer()
{
	_dollar = 200;
	_remainingTime = 20;
}
DollarDisplayLayer::~DollarDisplayLayer()
{

}
bool DollarDisplayLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	scheduleUpdate();
	this->displayDollarLable();
	if(isSinglePlayerGameMode == true)
		this->schedule(schedule_selector(DollarDisplayLayer::remainTimeMinueOneSecond), 1);
	return true;
}

void DollarDisplayLayer::displayDollarLable()
{
	this->_remainTimeLabel = Label::createWithSystemFont("", "arial", 24);
	this->_dollarLabel = Label::createWithSystemFont("","arial",18);
	this->_dollarStr = StringUtils::format("%d", this->_dollar);
	this->_dollarLabel->setString(this->_dollarStr);//动态金币展示板转化完毕

	this->addChild(this->_dollarLabel);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//this->_dollarLabel->setPosition(Vec2(2 * visibleSize.width / 7, 8 * visibleSize.height / 9));

	if (_iAmPlantSideGolbalVariable == true)
	{
		this->addChild(this->_remainTimeLabel);
		this->_remainTimeLabel->setPosition(Vec2(1000, 527));
		this->_dollarLabel->setPosition(Vec2(263, 527));
	}
	else
	{
		this->_dollarLabel->setPosition(Vec2(1360, 527));
	}
		
	this->_dollarLabel->setColor(Color3B(0, 0, 0));
}

void DollarDisplayLayer::update(float dt)
{
	this->_dollarStr = StringUtils::format("%d", this->_dollar);
	this->_dollarLabel->setString(this->_dollarStr);
}

void DollarDisplayLayer::remainTimeMinueOneSecond(float dlt)
{
	this->_remainTimeStr = StringUtils::format("%dsecond", --(this->_remainingTime));
	this->_remainTimeLabel->setString(this->_remainTimeStr);
	if (this->_remainingTime <= 0)
	{
		SimpleAudioEngine::getInstance()->stopAllEffects();
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		SimpleAudioEngine::getInstance()->playEffect("res/music/winmusic.wma");
		((GameLayer*)this->getParent())->_showSloganLayer->winInSingleMode();
		//胜利了，显示胜利图片，退出场景
		//((GameLayer*)this->getParent())->onExit();
		((GameLayer*)this->getParent())->_normalZombieLayer->onExit();
		this->unschedule(schedule_selector(DollarDisplayLayer::remainTimeMinueOneSecond));
		log("Win!!!");
	}
}
