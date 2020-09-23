#include "GameLayer.h"

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->initMapLayer();
	this->initDollarDisplayerLayer();//初始化金币展示板
	

	scheduleUpdate();//监听一切活动/变化
	this->initSunCellLayer();
	return true;
}

GameLayer::GameLayer()
{
	this->_sunCellLayer = NULL;
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
	this->_dollarDisplayLayer->_dollarStr = StringUtils::format("dollar:$%d", this->_dollarDisplayLayer->_dollar);
	this->_dollarDisplayLayer->_dollarLabel->setString(this->_dollarDisplayLayer->_dollarStr);

}

//初始化太阳因子层
void GameLayer::initSunCellLayer()
{
	this->_sunCellLayer = SunCellLayer::create();
	this->addChild(this->_sunCellLayer);
}