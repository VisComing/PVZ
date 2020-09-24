#include "PeaShooterLayer.h"
#include "GameLayer.h"
PeaShooterLayer::PeaShooterLayer()
{
	//_peaShooterCache = SpriteFrameCache::getInstance();
	//_peaShooterCache->addSpriteFramesWithFile("res/zombie.plist");

	this->_peaShooterSprite = NULL;
}

PeaShooterLayer::~PeaShooterLayer()
{
}

bool PeaShooterLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

void PeaShooterLayer::initPeaShooterSprite(Touch * touch)
{
	this->_peaShooterSprite = PeaShooterSprite::create();
	this->_peaShooterSprite->setPosition(touch->getLocation());
	this->addChild(_peaShooterSprite);
	((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar = ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 100;//ÿ����һ��ֲ��ǹ����100���  
	auto lis = EventListenerMouse::create();
	lis->onMouseMove = [=](EventMouse* e) {
		this->_peaShooterSprite->setPosition(100,300);
		
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);

}
