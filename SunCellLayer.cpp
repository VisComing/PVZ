#include "SunCellLayer.h"
#include "GameLayer.h"
#include "GameScene.h"
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
	schedule(schedule_selector(SunCellLayer::initSunCell), 3.0f);//调度器

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SunCellLayer::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	
	return true;
}

void SunCellLayer::initSunCell(float dlt)
{
	this->_sunCellSprite = SunCellSprite::create();//创建一个太阳精灵
	auto visibelSize = Director::getInstance()->getVisibleSize();//获得窗口大小

	if (((GameScene*)((GameLayer*)this->getParent())->getParent())->_iAmPlantSide == true)
	{
		this->_sunCellSprite->setPosition(rand() % 720 + 250,
			visibelSize.height + this->_sunCellSprite->getContentSize().height);
	}
	else
	{
		this->_sunCellSprite->setPosition(rand() % 720 + 500,
			visibelSize.height + this->_sunCellSprite->getContentSize().height);
	}
	this->addChild(this->_sunCellSprite);
	this->sunCellMoveWay();
}
void SunCellLayer::sunCellMoveWay()
{
	auto visibelSize = Director::getInstance()->getVisibleSize();
	FiniteTimeAction* sunCellMove1 = MoveTo::create(4.0f, Vec2((this->_sunCellSprite->getPositionX()), (30 + rand() % 250)));
	FiniteTimeAction* sunCellMove2 = MoveBy::create(5.0f, Vec2(0,0));
	//FiniteTimeAction* fade = FadeOut::create(0.01f);
	//this->_sunCellSprite->runAction(CCSequence::create(sunCellMove1, sunCellMove2, CCCallFuncN::create(this, callfuncN_selector(SunCellLayer::removeSunCell2)), NULL));
	Sequence* seq = CCSequence::create(sunCellMove1, sunCellMove2, CCCallFuncN::create(this, callfuncN_selector(SunCellLayer::removeSunCell2)), NULL);
	
	this->_sunCellSprite->runAction(seq);
	seq->setTag(1);
	//sunCellMove1->setTag(1);//阳光向下运动的tag为1
	
}
void SunCellLayer::removeSunCell(Node* pSend)
{

	Sprite* sprite = (Sprite*)pSend;
	this->removeChild(sprite, true);
	((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar = ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar + 25;
}

void SunCellLayer::removeSunCell2(Node* pSend)
{

	Sprite* sprite = (Sprite*)pSend;
	this->removeChild(sprite, true);
}


bool SunCellLayer::onTouchBegan(Touch* touch, Event* event)
{
	if (this->_sunCellSprite != NULL)
			{
				Vec2 point = touch->getLocation();
				auto visibelSize = Director::getInstance()->getWinSize();
				for (auto node : this->getChildren())
				{
					
					if (SunCellSprite::getRect(node).containsPoint(point))
					{
						node->stopActionByTag(1);
						FiniteTimeAction* sunCellMove2;
						if (((GameScene*)((GameLayer*)this->getParent())->getParent())->_iAmPlantSide == true)
						{
							//植物卡阳光处
							sunCellMove2 = MoveTo::create(0.5f, Vec2(261, 513));
						}
						else
						{
							//僵尸卡阳关处
							sunCellMove2 = MoveTo::create(0.5f, Vec2(1359, 525));
						}
						node->runAction(CCSequence::create(sunCellMove2, CCCallFuncN::create(this, callfuncN_selector(SunCellLayer::removeSunCell)), NULL));

					}
						
				}
			}	
	return true;
}