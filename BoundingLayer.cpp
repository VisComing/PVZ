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
	for (auto peaBullet : ((GameLayer*)this->getParent())->_touchLayer->_bulletVector)//遍历所有子弹
	{		
		for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//遍历所有僵尸
		{
			if (peaBullet->boundingBox().intersectsRect(normalZombie->NormalZombieBounding()))//如果子弹和僵尸碰撞
			{
				bulletRemove.pushBack(peaBullet);//待删除该子弹
				normalZombie->_hp -= 15;//僵尸扣血
				
				normalZombie->runAction(Blink::create(0.07, 1));

				if (normalZombie->_hp == 25)//此时僵尸头掉了
				{
					normalZombie->stopAllActions();
					normalZombie->runAction(Spawn::create(((GameLayer*)this->getParent())->_normalZombieLayer
						->_normalZombieSprite->noHeadAnimation(), ((GameLayer*)this->getParent())->_normalZombieLayer
						->_normalZombieSprite->headAnimation(),((GameLayer*)this->getParent())->_normalZombieLayer
							->noHeadNormalZombieMoveWay(), NULL));
				}

				if (normalZombie->_hp <= 0)
				{
					zombieRemove.pushBack(normalZombie);//将死亡僵尸添加到待删除数组
					
				}
				break;//一个子弹只能碰撞一个僵尸
			}
		}
	}
	for (auto bullet : bulletRemove)//遍历待删除的子弹,将子弹删除
	{
		//bullet->stopAllActions();//停止所有动作
		//bullet->runAction(Sequence::create(((GameLayer*)this->getParent())->_bulletLayer->_bulletSprite->_bulletBroken, CallFuncN::create(((GameLayer*)this->getParent())->_bulletLayer, callfuncN_selector(BulletLayer::removeBullet)), NULL));
		((GameLayer*)this->getParent())->_touchLayer->removeChild(bullet);
		((GameLayer*)this->getParent())->_touchLayer->_bulletVector.eraseObject(bullet);
		
	}
	for (auto zombie : zombieRemove)
	{
		((GameLayer*)this->getParent())->_normalZombieLayer->removeChild(zombie);
		((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector.eraseObject(zombie);

	}
}