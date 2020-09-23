#include "GameLayer.h"

bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->initMapLayer();
	this->initDollarDisplayerLayer();//��ʼ�����չʾ��
	

	scheduleUpdate();//����һ�л/�仯
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

//������չʾ�㺯��
void GameLayer::initDollarDisplayerLayer()
{
	this->_dollarDisplayLayer = DollarDisplayLayer::create();
	this->addChild(this->_dollarDisplayLayer);
}

void GameLayer::update(float dlt)
{
	//������ұ仯
	this->_dollarDisplayLayer->_dollarStr = StringUtils::format("dollar:$%d", this->_dollarDisplayLayer->_dollar);
	this->_dollarDisplayLayer->_dollarLabel->setString(this->_dollarDisplayLayer->_dollarStr);

}

//��ʼ��̫�����Ӳ�
void GameLayer::initSunCellLayer()
{
	this->_sunCellLayer = SunCellLayer::create();
	this->addChild(this->_sunCellLayer);
}