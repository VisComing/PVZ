#include "ZombieLayer.h"

ZombieLayer::ZombieLayer()
{
	_normalZombieSprite = NULL;
}
ZombieLayer::~ZombieLayer()
{

}

bool ZombieLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	schedule(schedule_selector(ZombieLayer::initNormalZombieSprite), 19.0f);//调度器

	return true;
}


void ZombieLayer::initNormalZombieSprite(float dlt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	this->_normalZombieSprite = NormalZombieSprite::create();
	this->_normalZombieSprite->setPosition(Vec2(visibleSize.width * 8 / 9, visibleSize.height / 2));
	this->addChild(this->_normalZombieSprite);
	this->normalZombieMoveWay();

}
void ZombieLayer::normalZombieMoveWay()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	FiniteTimeAction* normalZombieMove = MoveTo::create(30.0f, Vec2(visibleSize.width / 9, this->_normalZombieSprite->getPosition().y));

	this->_normalZombieSprite->runAction(Sequence::create(normalZombieMove, CCCallFuncN::create(this, callfuncN_selector(ZombieLayer::removeNormalZombie)), NULL));

}
void ZombieLayer::removeNormalZombie(Node* pSend)
{
	Sprite* sprite = (Sprite*)pSend;
	this->removeChild(sprite, true);//从精灵批处理节点中回收红帽子僵尸
}