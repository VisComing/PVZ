#include "BulletLayer.h"
#include "../Base/GameLayer.h"
#include "../Base/TouchLayer.h"
#include "SimpleAudioEngine.h"
#include "../Base/global.h"
using namespace CocosDenshion;
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
	scheduleUpdate();
	return true;
}
void BulletLayer::initBulletSprite(float dlt)
{
	int i = 0;
	for (auto peaShooter : (dynamic_cast<GameLayer*>(this->getParent()))->_peaShooterLayer->_peaShooterVector)
	{	
		//������ʬ���飬�ж��Ƿ��ڸ�ֲ��ǰ��
		for (auto normalZombie : (dynamic_cast<GameLayer*>(this->getParent()))->_normalZombieLayer->_normalZombieVector)
		{
			if (abs(peaShooter->getPositionY() - normalZombie->getPositionY()) < 40 && peaShooter->getPositionX() < normalZombie->getPositionX())
			{

				(dynamic_cast<GameLayer*>(this->getParent()))->_peaShooterLayer->_peaShooterTime[i] += 1;
				if ((dynamic_cast<GameLayer*>(this->getParent()))->_peaShooterLayer->_peaShooterTime[i] == 25)
				{
					this->_bulletSprite = BulletSprite::create();
					this->addChild(this->_bulletSprite);
					this->_bulletVector.pushBack(this->_bulletSprite);//���ӵ���ӵ��ӵ�������
					this->_bulletSprite->setPosition(peaShooter->getPositionX() + 20, peaShooter->getPositionY() + 13);
					this->bulletMoveWay();

					(dynamic_cast<GameLayer*>(this->getParent()))->_peaShooterLayer->_peaShooterTime[i] = 0;

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
	//this->_bulletSprite->runAction(Sequence::create(bulletMove, CallFuncN::create(this, callfuncN_selector(BulletLayer::removeBullet)), NULL));
	auto tmp = this->_bulletSprite;
	this->_bulletSprite->runAction(Sequence::createWithTwoActions(
		bulletMove, CallFunc::create([tmp]() {
			(tmp)->removeFromParent();//���ӵ�ɾ��
			})));
	
}
void BulletLayer::removeBullet(Node* pSend)
{
	Sprite* sprite = (Sprite*)pSend;
	if (this->_bulletVector.contains(sprite))
	{
		this->_bulletVector.eraseObject(sprite);
		this->removeChild(sprite);
	}
}

void BulletLayer::bulletAttackZombie()
{
	for (auto i = this->_bulletVector.begin(); i != this->_bulletVector.end();)
	{
		bool _iFlag = false;
		for (auto j = _zombieVectorGlobalVariable.begin(); j != _zombieVectorGlobalVariable.end();)
		{
			if ((*i)->getBoundingBox().intersectsRect((*j)->zombieBounding()))
			{
				SimpleAudioEngine::getInstance()->playEffect("res/music/bullet.wma");
				_iFlag = true;
				(*i)->removeFromParent();//���ӵ�ɾ��
				i = _bulletVector.erase(i);//ɾ���ӵ�
				
				(*j)->_hp -= 15;//��ʬ��Ѫ
				(*j)->typeOfDeath = 0;//��������0��ʾ���ӵ�����
				break;
			}
			j++;
			
		}
		if (_iFlag == false)
			i++;
	}
}

void BulletLayer::update(float dt)
{
	this->bulletAttackZombie();
}
