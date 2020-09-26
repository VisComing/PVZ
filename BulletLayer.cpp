#include "BulletLayer.h"
#include "GameLayer.h"
#include "TouchLayer.h"

BulletLayer::BulletLayer()
{
	this->_bulletSprite = NULL;
}
BulletLayer::~BulletLayer()
{

}

bool BulletLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}
void BulletLayer::initBulletSprite(float dlt)
{
	this->_bulletSprite = BulletSprite::create();
	((GameLayer*)this->getParent())->_touchLayer->addChild(this->_bulletSprite);
	this->_bulletSprite->setPosition(((GameLayer*)this->getParent())->_peaShooterLayer->_peaShooterSprite
		->getPositionX(), ((GameLayer*)this->getParent())->_peaShooterLayer->_peaShooterSprite
		->getPositionY() + 10);
	this->bulletMoveWay();
}

void BulletLayer::bulletMoveWay()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	FiniteTimeAction* bulletMove = MoveTo::create(6.0f, Vec2(8 * visibleSize.width / 9,
		this->_bulletSprite->getPositionY() + 10));
	this->_bulletSprite->runAction(Sequence::create(bulletMove, CallFuncN::create(this, callfuncN_selector(BulletLayer::removeBullet)), NULL));

}
void BulletLayer::removeBullet(Node* pSend)
{
	Sprite* sprite = (Sprite*)pSend;
	((GameLayer*)this->getParent())->_touchLayer->removeChild(sprite);
}