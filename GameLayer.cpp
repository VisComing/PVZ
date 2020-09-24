#include "GameLayer.h"

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->initMapLayer();
	
	

	scheduleUpdate();//监听一切活动/变化
	
	this->initZombieLayer();
	this->initCardLayer();
	this->initTouchLayer();
	
	this->initDollarDisplayerLayer();//初始化金币展示板
	this->initSunCellLayer();//阳光下落
	this->initPeaShooterLayer();
	return true;
}

GameLayer::GameLayer()
{
	this->_sunCellLayer = NULL;
	this->_zombieLayer = NULL;
	this->_cardLayer = NULL;
	this->_touchLayer = NULL;
	this->_peaShooterLayer = NULL;
}

GameLayer::~GameLayer()
{

}

void GameLayer::initMapLayer()
{
	this->_mapLayer = MapLayer::create();
	this->addChild(this->_mapLayer);
}

//定义金币展示层函数
void GameLayer::initDollarDisplayerLayer()
{
	this->_dollarDisplayLayer = DollarDisplayLayer::create();
	this->addChild(this->_dollarDisplayLayer);
}

void GameLayer::update(float dlt)
{
	//监听金币变化
	this->_dollarDisplayLayer->_dollarStr = StringUtils::format("%d", this->_dollarDisplayLayer->_dollar);
	this->_dollarDisplayLayer->_dollarLabel->setString(this->_dollarDisplayLayer->_dollarStr);

}

//初始化太阳因子层
void GameLayer::initSunCellLayer()
{
	this->_sunCellLayer = SunCellLayer::create();
	this->addChild(this->_sunCellLayer);
}

void GameLayer::initZombieLayer()
{
	this->_zombieLayer = ZombieLayer::create();
	this->addChild(this->_zombieLayer);
}

void GameLayer::initCardLayer()
{
	this->_cardLayer = CardLayer::create();
	this->addChild(this->_cardLayer);
}
void GameLayer::initTouchLayer()
{
	this->_touchLayer = TouchLayer::create();
	this->addChild(_touchLayer);
}

void GameLayer::initPeaShooterLayer()
{
	this->_peaShooterLayer = PeaShooterLayer::create();
	this->addChild(this->_peaShooterLayer);
}
