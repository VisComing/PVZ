#include "BoundingLayer.h"
#include "GameLayer.h"

BoundingLayer::BoundingLayer()
{

}

BoundingLayer::~BoundingLayer()
{

}

bool BoundingLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

void BoundingLayer::bulletBoundingZombie()
{
	Vector<Sprite*> bulletRemove;
	Vector<NormalZombieSprite*> zombieRemove;
	for (auto peaBullet : ((GameLayer*)this->getParent())->_bulletLayer->_bulletVector)//遍历所有子弹
	{		
		for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//遍历所有僵尸
		{
			if (peaBullet->getBoundingBox().intersectsRect(normalZombie->NormalZombieBounding()))//如果子弹和僵尸碰撞
			{
				bulletRemove.pushBack(peaBullet);//待删除该子弹
				peaBullet->removeFromParent();//将子弹删除
				//peaBullet->runAction(Sequence::createWithTwoActions(((GameLayer*)this->getParent())->_bulletLayer->_bulletSprite->_bulletBroken,
				//	CallFunc::create([peaBullet]() {
				//		peaBullet->removeFromParent();//将子弹删除
				//		})
				//));

				normalZombie->_hp -= 15;//僵尸扣血
				
				//normalZombie->runAction(Blink::create(0.07f, 1));

				if (normalZombie->_hp == 25)//此时僵尸头掉了
				{
					normalZombie->stopAllActions();
					
					/*normalZombie->runAction(Spawn::create(((GameLayer*)this->getParent())->_normalZombieLayer
						->_normalZombieSprite->noHeadAnimation(), ((GameLayer*)this->getParent())->_normalZombieLayer
						->_normalZombieSprite->headAnimation(),((GameLayer*)this->getParent())->_normalZombieLayer
							->noHeadNormalZombieMoveWay(), NULL));*/
					normalZombie->runAction(Sequence::create(((GameLayer*)this->getParent())->
						_normalZombieLayer->_normalZombieSprite->headAnimation(), Spawn::create(((GameLayer*)this->getParent())->_normalZombieLayer
						->_normalZombieSprite->noHeadAnimation(), ((GameLayer*)this->getParent())->_normalZombieLayer
						->noHeadNormalZombieMoveWay(), NULL),NULL));
				}

				if (normalZombie->_hp <= 0)
				{

					normalZombie->stopAllActions();
					zombieRemove.pushBack(normalZombie);//将死亡僵尸添加到待删除数组
					normalZombie->runAction(Sequence::createWithTwoActions(((GameLayer*)this->getParent())->_normalZombieLayer
						->_normalZombieSprite->downTheGround(), CallFunc::create([normalZombie]() {
							normalZombie->removeFromParent();//将僵尸删除
							})));
				}
				break;//一个子弹只能碰撞一个僵尸
			}
		}
	}
	for (auto bullet : bulletRemove)//遍历待删除的子弹,将子弹删除
	{
		//bullet->stopAllActions();//停止所有动作
		//bullet->runAction(Sequence::create(((GameLayer*)this->getParent())->_bulletLayer->_bulletSprite->_bulletBroken, CallFuncN::create(((GameLayer*)this->getParent())->_bulletLayer, callfuncN_selector(BulletLayer::removeBullet)), NULL));
		((GameLayer*)this->getParent())->_bulletLayer->_bulletVector.eraseObject(bullet);
		
	}
	for (auto zombie : zombieRemove)
	{
		((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector.eraseObject(zombie);
	}
}

void BoundingLayer::zombieEatPlant()
{
	//Vector<PeaShooterSprite*> peaShooterRemove;
	//for (auto peaBullet : ((GameLayer*)this->getParent())->_bulletLayer->_bulletVector)//遍历所有
	//{
	//	for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//遍历所有僵尸
}
