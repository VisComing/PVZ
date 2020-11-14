#include "DollarDisplayLayer.h"
#include "GameScene.h"
#include "GameLayer.h"
extern bool _iAmPlantSideGolbalVariable;
DollarDisplayLayer::DollarDisplayLayer()
{
	_dollar = 200;

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
	this->displayDollarLable();

	

	return true;
}

void DollarDisplayLayer::displayDollarLable()
{
	this->_dollarLabel = Label::createWithSystemFont("","arial",18);
	this->_dollarStr = StringUtils::format("%d", this->_dollar);
	this->_dollarLabel->setString(this->_dollarStr);//动态金币展示板转化完毕
	this->addChild(this->_dollarLabel);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	//this->_dollarLabel->setPosition(Vec2(2 * visibleSize.width / 7, 8 * visibleSize.height / 9));

	if (_iAmPlantSideGolbalVariable == true)
	{
		this->_dollarLabel->setPosition(Vec2(263, 527));
	}
	else
	{
		this->_dollarLabel->setPosition(Vec2(1360, 527));
	}
		
	this->_dollarLabel->setColor(Color3B(0, 0, 0));
}