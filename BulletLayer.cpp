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
	int i = 0;
	for (auto peaShooter : ((GameLayer*)this->getParent())->_peaShooterLayer->_peaShooterVector)
	{	
		//遍历僵尸数组，判断是否在该植物前方
		for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)
		{
			if (abs(peaShooter->getPositionY() - normalZombie->getPositionY()) < 40 && peaShooter->getPositionX() < normalZombie->getPositionX())
			{

				((GameLayer*)this->getParent())->_peaShooterLayer->_peaShooterTime[i] += 1;
				if (((GameLayer*)this->getParent())->_peaShooterLayer->_peaShooterTime[i] == 25)
				{
					this->_bulletSprite = BulletSprite::create();
					((GameLayer*)this->getParent())->_touchLayer->addChild(this->_bulletSprite);
					((GameLayer*)this->getParent())->_touchLayer->_bulletVector.pushBack(this->_bulletSprite);//将子弹添加到子弹数组中
					this->_bulletSprite->setPosition(peaShooter->getPositionX(), peaShooter->getPositionY() + 10);
					this->bulletMoveWay();

					((GameLayer*)this->getParent())->_peaShooterLayer->_peaShooterTime[i] = 0;

				}
				i++;
				break;
			}
		}
	}
}

void BulletLayer::bulletMoveWay()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	float time = (8 * visibleSize.width / 9 - this->_bulletSprite->getPositionX()) / 300;
	
	FiniteTimeAction* bulletMove = MoveTo::create(time, Vec2(8 * visibleSize.width / 9,
		this->_bulletSprite->getPositionY() + 15));
	this->_bulletSprite->runAction(Sequence::create(bulletMove, CallFuncN::create(this, callfuncN_selector(BulletLayer::removeBullet)), NULL));
}
void BulletLayer::removeBullet(Node* pSend)
{
	Sprite* sprite = (Sprite*)pSend;
	if (((GameLayer*)this->getParent())->_touchLayer->_bulletVector.contains(sprite))
	{
		((GameLayer*)this->getParent())->_touchLayer->_bulletVector.eraseObject(sprite);
		((GameLayer*)this->getParent())->_touchLayer->removeChild(sprite);
	}
}