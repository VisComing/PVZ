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
	Vector<PotatoMineSprite*> potatoMineRemove;//将要删除的土豆地雷精灵
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

	for (auto potatoMine : ((GameLayer*)this->getParent())->_potatoMineLayer->_potatoMineVector)//遍历所有的土豆地雷
	{
		if (potatoMine->_potatoMineTime == 6)
		{
			for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//遍历所有僵尸
			{

				if (potatoMine->getBoundingBox().intersectsRect(normalZombie->NormalZombieBounding()))//如果土豆地雷和僵尸碰撞
				{
					potatoMineRemove.pushBack(potatoMine);
					potatoMine->removeFromParent();

					//僵尸死亡
					normalZombie->stopAllActions();
					zombieRemove.pushBack(normalZombie);//将死亡僵尸添加到待删除数组
					normalZombie->runAction(Sequence::createWithTwoActions(((GameLayer*)this->getParent())->_normalZombieLayer
						->_normalZombieSprite->explodAction(), CallFunc::create([normalZombie]() {
							normalZombie->removeFromParent();//将僵尸删除
							})));
				}
			}
		}
	}

	for (auto bullet : bulletRemove)//遍历待删除的子弹,将子弹删除
	{
		//bullet->stopAllActions();//停止所有动作
		//bullet->runAction(Sequence::create(((GameLayer*)this->getParent())->_bulletLayer->_bulletSprite->_bulletBroken, CallFuncN::create(((GameLayer*)this->getParent())->_bulletLayer, callfuncN_selector(BulletLayer::removeBullet)), NULL));
		((GameLayer*)this->getParent())->_bulletLayer->_bulletVector.eraseObject(bullet);
		//bullet->removeFromParent();
		
	}
	for (auto zombie : zombieRemove)
	{
		((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector.eraseObject(zombie);
		//zombie->removeFromParent();
	}
	for (auto potatoMine : potatoMineRemove)
	{
		//删除该植物，并且在地图上移除
		//log("%d   %d", potatoMine->_position[0], potatoMine->_position[0]);
		((GameLayer*)this->getParent())->_mapLayer->_isPlanted[potatoMine->_position[0]][potatoMine->_position[1]] = false;
		
		((GameLayer*)this->getParent())->_potatoMineLayer->_potatoMineVector.eraseObject(potatoMine);
		//potatoMine->removeFromParent();
	}

}
void BoundingLayer::zombieEatPlant()
{
	Vector<PeaShooterSprite*> peaShooterRemove;//待移除的豌豆射手
	
	for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//遍历所有僵尸
	{
		
		for (auto peaShooter : ((GameLayer*)this->getParent())->_peaShooterLayer->_peaShooterVector)//遍历所有豌豆射手
		{
			if (normalZombie->attacting == false)
			{
				if (peaShooter->getBoundingBox().intersectsRect(normalZombie->NormalZombieBounding()))//如果相交
				{
					//僵尸攻击植物
					normalZombie->stopAllActions();
					normalZombie->runAction(RepeatForever::create(((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieSprite->attackAnimation()));
					normalZombie->attacting = true;
					peaShooter->under_attack = true;
				}
			}
			if (peaShooter->under_attack == true)
			{
				peaShooter->_plantHP -= 1;
			}
			if (peaShooter->_plantHP <= 0)
			{
				peaShooterRemove.pushBack(peaShooter);
				normalZombie->attacting = true;
			}
		}
		
	}
	for (auto peaShooter : peaShooterRemove)
	{
		//log("peaShooter has been erased!");
		((GameLayer*)this->getParent())->_mapLayer->_isPlanted[peaShooter->_position[0]][peaShooter->_position[1]] = false;
		((GameLayer*)this->getParent())->_peaShooterLayer->_peaShooterVector.eraseObject(peaShooter);
		peaShooter->removeFromParent();//?删除土豆地雷的时候用了什么方法
	}
}
