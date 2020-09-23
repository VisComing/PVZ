#include "SunCellLayer.h"
#include "GameLayer.h"

SunCellLayer::SunCellLayer()
{
	this->_sunCellSprite = NULL;
}
SunCellLayer::~SunCellLayer()
{

}
bool SunCellLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	log("\n\nnnnnn\n");
	schedule(schedule_selector(SunCellLayer::initSunCell), 7.0f);//调度器
	return true;
}

void SunCellLayer::initSunCell(float dlt)
{
	log("\nherehrehrehrheh\n");
	this->_sunCellSprite = SunCellSprite::create();//创建一个太阳精灵
	auto visibelSize = Director::getInstance()->getWinSize();//获得窗口大小
	this->_sunCellSprite->_sunSprite->setPosition(rand()%720+ 250,
		visibelSize.height + this->_sunCellSprite->getContentSize().height);
	this->addChild(this->_sunCellSprite->_sunSprite);
	this->sunCellMoveWay();
}
void SunCellLayer::sunCellMoveWay()
{
	auto visibelSize = Director::getInstance()->getWinSize();
	FiniteTimeAction* sunCellMove1 = MoveTo::create(8.0f, Vec2((this->_sunCellSprite->_sunSprite->getPositionX()),(1 * visibelSize.height / 4)));
	FiniteTimeAction* sunCellMove2 = MoveTo::create(0.5f, Vec2(2 * visibelSize.width / 7, 8 * visibelSize.height / 9));
	this->_sunCellSprite->_sunSprite->runAction(Sequence::create(sunCellMove1, sunCellMove2, CallFuncN::create(this, callfuncN_selector(SunCellLayer::removeSunCell)), NULL));

}
void SunCellLayer::removeSunCell(Node* pSend)
{
	Sprite* sprite = (Sprite*)pSend;
	this->removeChild(sprite, true);
	((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar = ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar + 25;
}