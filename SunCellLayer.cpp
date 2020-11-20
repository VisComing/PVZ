#include "SunCellLayer.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
extern bool _iAmPlantSideGolbalVariable;
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

	if (_iAmPlantSideGolbalVariable == true)
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
	//Sequence* seq = CCSequence::create(sunCellMove1, sunCellMove2, CCCallFuncN::create(this, callfuncN_selector(SunCellLayer::removeSunCell2)), NULL);
	
	//this->_sunCellSprite->runAction(seq);
	//seq->setTag(1);
	auto tmpSprite = this->_sunCellSprite;
	//sunCellMove1->setTag(1);//阳光向下运动的tag为1
	this->_sunCellSprite->runAction(Sequence::create(sunCellMove1, DelayTime::create(5), CallFunc::create(
		[tmpSprite]() {
			tmpSprite->removeFromParent();
		}), NULL));
}
//void SunCellLayer::removeSunCell(Node* pSend)
//{
//
//	Sprite* sprite = (Sprite*)pSend;
//	this->removeChild(sprite, true);
//	((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar = ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar + 25;
//}
//
//void SunCellLayer::removeSunCell2(Node* pSend)
//{
//
//	Sprite* sprite = (Sprite*)pSend;
//	this->removeChild(sprite, true);
//}


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
						SimpleAudioEngine::getInstance()->playEffect("res/music/clickSunSprite.wma");
						//node->stopActionByTag(1);
						node->stopAllActions();
						FiniteTimeAction* sunCellMove2;
						if (_iAmPlantSideGolbalVariable == true)
						{
							//植物卡阳光处
							sunCellMove2 = MoveTo::create(0.5f, Vec2(261, 513));
						}
						else
						{
							//僵尸卡阳光处
							sunCellMove2 = MoveTo::create(0.5f, Vec2(1359, 525));
						}
						//node->runAction(CCSequence::create(sunCellMove2, CCCallFuncN::create(this, callfuncN_selector(SunCellLayer::removeSunCell)), NULL));
						
						//node->runAction(Sequence::createWithTwoActions(sunCellMove2, CallFunc::create())
						auto tmpSprite = node;
						node->runAction(Sequence::createWithTwoActions(sunCellMove2, 
							CallFunc::create([=]() {
								tmpSprite->removeFromParent();
								((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar += 25;
							})));
						break;
					}
						
				}
			}	
	return true;
}

void SunCellLayer::produceSunCell(Vec2 _pos)
{
	auto _sunCellSprite1 = SunCellSprite::create();//创建一个太阳精灵
	Vec2 _pos1, _pos2;
	_pos1.y = _pos.y + 30;
	_pos2.y = _pos.y - 20;
	int random = rand() % 2;
	if (random == 0) _pos1.x = _pos.x - 25, _pos2.x = _pos.x - 30;
	else _pos1.x = _pos.x + 25, _pos2.x = _pos.x + 30;
	_sunCellSprite1->setPosition(_pos);
	this->addChild(_sunCellSprite1);
	auto tmpSprite = _sunCellSprite1;
	_sunCellSprite1->runAction(Sequence::create(MoveTo::create(0.4, _pos1), MoveTo::create(0.6, _pos2), DelayTime::create(5), CallFunc::create([tmpSprite]() {
		tmpSprite->removeFromParent();
		}), NULL));
}
