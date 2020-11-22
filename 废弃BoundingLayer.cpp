#include "BoundingLayer.h"
#include "GameLayer.h"
#include <utility>
extern Vector<ZombieBaseClass*>_zombieVector;
extern Vector<PlantBaseClass*> _plantVector;
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
	scheduleUpdate();
	return true;
}

void BoundingLayer::bulletBoundingZombie()
{
	Vector<Sprite*> bulletRemove;
	Vector<NormalZombieSprite*> zombieRemove;
	Vector<PotatoMineSprite*> potatoMineRemove;//将要删除的土豆地雷精灵
	//for (auto peaBullet : ((GameLayer*)this->getParent())->_bulletLayer->_bulletVector)//遍历所有子弹
	//{		
	//	for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//遍历所有僵尸
	//	{
	//		if (peaBullet->getBoundingBox().intersectsRect(normalZombie->NormalZombieBounding()))//如果子弹和僵尸碰撞
	//		{
	//			bulletRemove.pushBack(peaBullet);//待删除该子弹
	//			peaBullet->removeFromParent();//将子弹删除
	//			//peaBullet->runAction(Sequence::createWithTwoActions(((GameLayer*)this->getParent())->_bulletLayer->_bulletSprite->_bulletBroken,
	//			//	CallFunc::create([peaBullet]() {
	//			//		peaBullet->removeFromParent();//将子弹删除
	//			//		})
	//			//));

	//			normalZombie->_hp -= 15;//僵尸扣血
	//			
	//			//normalZombie->runAction(Blink::create(0.07f, 1));

	//			//if (normalZombie->_hp == 25)//此时僵尸头掉了
	//			//{
	//			//	normalZombie->stopAllActions();
	//			//	
	//			//	/*normalZombie->runAction(Spawn::create(((GameLayer*)this->getParent())->_normalZombieLayer
	//			//		->_normalZombieSprite->noHeadAnimation(), ((GameLayer*)this->getParent())->_normalZombieLayer
	//			//		->_normalZombieSprite->headAnimation(),((GameLayer*)this->getParent())->_normalZombieLayer
	//			//			->noHeadNormalZombieMoveWay(), NULL));*/
	//			//	normalZombie->runAction(Sequence::create(((GameLayer*)this->getParent())->
	//			//		_normalZombieLayer->_normalZombieSprite->headAnimation(), Spawn::create(((GameLayer*)this->getParent())->_normalZombieLayer
	//			//		->_normalZombieSprite->noHeadAnimation(), ((GameLayer*)this->getParent())->_normalZombieLayer
	//			//		->noHeadNormalZombieMoveWay(), NULL),NULL));
	//			//}

	//			if (normalZombie->_hp <= 0)
	//			{

	//				normalZombie->stopAllActions();
	//				zombieRemove.pushBack(normalZombie);//将死亡僵尸添加到待删除数组
	//				normalZombie->runAction(Sequence::createWithTwoActions(((GameLayer*)this->getParent())->_normalZombieLayer
	//					->_normalZombieSprite->downTheGround(), CallFunc::create([normalZombie]() {
	//						normalZombie->removeFromParent();//将僵尸删除
	//						})));
	//			}
	//			break;//一个子弹只能碰撞一个僵尸
	//		}
	//	}
	//}
	set<NormalZombieSprite*> normalZombieBoomDied;//被炸死的僵尸
	//for (auto potatoMine : ((GameLayer*)this->getParent())->_potatoMineLayer->_potatoMineVector)//遍历所有的土豆地雷
	//{
	//	if (potatoMine->_potatoMineTime == potatoMine->_potatoMineGrowTime + 1)
	//	{
	//		for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//遍历所有僵尸
	//		{

	//			if (potatoMine->getBoundingBox().intersectsRect(normalZombie->zombieBounding()))//如果土豆地雷和僵尸碰撞
	//			{
	//				potatoMineRemove.pushBack(potatoMine);
	//				((GameLayer*)this->getParent())->_mapLayer->_isPlanted[potatoMine->_position[0]][potatoMine->_position[1]] = false;
	//				potatoMine->removeFromParent();//原来是在这里移除了啊
	//				normalZombieBoomDied.insert(normalZombie);
	//				//僵尸死亡
	//				//normalZombie->stopAllActions();
	//				//zombieRemove.pushBack(normalZombie);//将死亡僵尸添加到待删除数组
	//				//normalZombie->runAction(Sequence::createWithTwoActions(((GameLayer*)this->getParent())->_normalZombieLayer
	//				//	->_normalZombieSprite->explodAction(), CallFunc::create([normalZombie]() {
	//				//		normalZombie->removeFromParent();//将僵尸删除
	//				//		})));
	//			}
	//		}
	//	}
	//	//else//还没有长大，可以被僵尸攻击
	//	//{
	//	//	for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//遍历所有僵尸
	//	//	{
	//	//		if (potatoMine->getBoundingBox().intersectsRect(normalZombie->NormalZombieBounding()))//如果土豆地雷和僵尸碰撞
	//	//		{

	//	//		}
	//	//	}
	//	//}
	//}
	//for (auto normalZombie : normalZombieBoomDied)
	//{
	//	normalZombie->stopAllActions();
	//	zombieRemove.pushBack(normalZombie);//将死亡僵尸添加到待删除数组
	//	normalZombie->runAction(Sequence::createWithTwoActions(((GameLayer*)this->getParent())->_normalZombieLayer
	//		->_normalZombieSprite->explodAction(), CallFunc::create([normalZombie]() {
	//			normalZombie->removeFromParent();//将僵尸删除
	//			})));
	//}

	//for (auto bullet : bulletRemove)//遍历待删除的子弹,将子弹删除
	//{
	//	//bullet->stopAllActions();//停止所有动作
	//	//bullet->runAction(Sequence::create(((GameLayer*)this->getParent())->_bulletLayer->_bulletSprite->_bulletBroken, CallFuncN::create(((GameLayer*)this->getParent())->_bulletLayer, callfuncN_selector(BulletLayer::removeBullet)), NULL));
	//	((GameLayer*)this->getParent())->_bulletLayer->_bulletVector.eraseObject(bullet);
	//	//bullet->removeFromParent();
	//	
	//}
	//for (auto zombie : zombieRemove)
	//{
	//	((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector.eraseObject(zombie);
	//	_zombieVector.eraseObject(zombie);
	//	//zombie->removeFromParent();
	//}
	//for (auto potatoMine : potatoMineRemove)
	//{
	//	//删除该植物，并且在地图上移除
	//	//log("%d   %d", potatoMine->_position[0], potatoMine->_position[0]);
	//	
	//	((GameLayer*)this->getParent())->_potatoMineLayer->_potatoMineVector.eraseObject(potatoMine);
	//	_plantVector.eraseObject(potatoMine);
	//	//potatoMine->removeFromParent();
	//}

}
//Map<NormalZombieSprite*, PeaShooterSprite*> zombieAttackPeaShooter;
void BoundingLayer::zombieEatPlant()
{
	for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//遍历所有僵尸
	{
		for (auto potatoMine : ((GameLayer*)this->getParent())->_potatoMineLayer->_potatoMineVector)
		{
			if (potatoMine->_potatoMineTime != potatoMine->_potatoMineGrowTime + 1)
			{
				if (potatoMine->plantBounding().intersectsRect(normalZombie->zombieBounding()))//如果土豆地雷和僵尸碰撞
				{
					if (normalZombie->numberOfRunningActions() != 1)
					{
						zombieAttackPotatoMine.insert(normalZombie, potatoMine);
						normalZombie->stopAllActions();
						normalZombie->runAction(RepeatForever::create(normalZombie->attackAnimation()));
					}
				}
			}
		}
	}
	for (auto iter = zombieAttackPotatoMine.begin(); iter != zombieAttackPotatoMine.end();)
	{
		auto x = *iter;
		auto zombie = x.first;
		auto potatoMine = x.second;
		potatoMine->_plantHP -= 1;
		if (potatoMine->_plantHP <= 0)
		{
			zombie->stopAllActions();
			zombie->runAction(RepeatForever::create(zombie->walkAnimation()));
			zombie->runAction(zombie->normalZombieMoveWay());
			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[potatoMine->_position[0]][potatoMine->_position[1]] = false;
			potatoMine->removeFromParent();
			((GameLayer*)this->getParent())->_potatoMineLayer->_potatoMineVector.eraseObject(potatoMine);
			_plantVector.eraseObject(potatoMine);
			zombieAttackPotatoMine.erase(iter++);
		}
		else iter++;
	}


	set<NormalZombieSprite*> zombieAttackPeaShooterRemove;
	for (auto x : this->zombieAttackPeaShooter)
	{
		bool flagExist = false;
		auto normalZombie = x.first;
		for (auto normalZombieInVector : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)
		{
			if (normalZombie == normalZombieInVector)
			{
				flagExist = true;
				break;
			}
		}
		if (flagExist == false)//僵尸已经死亡
		{
			zombieAttackPeaShooterRemove.insert(x.first);
		}
	}
	for (auto x : zombieAttackPeaShooterRemove)
	{
		this->zombieAttackPeaShooter.erase(this->zombieAttackPeaShooter.find(x));
	}
	zombieAttackPeaShooterRemove.clear();

	set<PeaShooterSprite*> peaShooterRemove;//待移除的豌豆射手
	
	for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//遍历所有僵尸
	{		
		if (this->zombieAttackPeaShooter.find(normalZombie) == this->zombieAttackPeaShooter.end())
		{
			for (auto peaShooter : ((GameLayer*)this->getParent())->_peaShooterLayer->_peaShooterVector)//遍历所有豌豆射手
			{
				if (peaShooter->plantBounding().intersectsRect(normalZombie->zombieBounding()))//如果相交
				{
					//僵尸攻击植物
					this->zombieAttackPeaShooter.insert(normalZombie, peaShooter);
					normalZombie->stopAllActions();
					//normalZombie->runAction(RepeatForever::create(((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieSprite->attackAnimation()));
					normalZombie->runAction(RepeatForever::create(normalZombie->attackAnimation()));

				}
			}
		}
	}
	for (auto x : this->zombieAttackPeaShooter)
	{
		auto normalZombie = x.first;
		auto peaShooter = x.second;
		peaShooter->_plantHP -= 1;
		if (peaShooter->_plantHP <= 0)
		{
			//对于所有正在攻击该植物的僵尸
			//for (auto y : zombieAttackPeaShooter)
			//{
				//if (y.second == peaShooter)
				//{
			zombieAttackPeaShooterRemove.insert(normalZombie);
			normalZombie->stopAllActions();
			normalZombie->runAction(RepeatForever::create(normalZombie->walkAnimation()));
			//((GameLayer*)this->getParent())->_normalZombieLayer->normalZombieMoveWay();
			normalZombie->runAction(normalZombie->normalZombieMoveWay());
				//}
			//}			
			
			peaShooterRemove.insert(peaShooter);
			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[peaShooter->_position[0]][peaShooter->_position[1]] = false;
			peaShooter->removeFromParent();
			/*peaShooter->runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([peaShooter]() {
				peaShooter->removeFromParent();
				})));*/
			//执行peaShooter->removeFromParent();总是有bug出现，2020/11/13
		}
	}
	for (auto x : zombieAttackPeaShooterRemove)
	{
		this->zombieAttackPeaShooter.erase(this->zombieAttackPeaShooter.find(x));		
	}
	
	for (auto peaShooter : peaShooterRemove)
	{
		//log("peaShooter has been erased!");
		((GameLayer*)this->getParent())->_peaShooterLayer->_peaShooterVector.eraseObject(peaShooter);
		_plantVector.eraseObject(peaShooter);
	}
}

void BoundingLayer::zombieEatPlantT()
{
	for (auto zombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//遍历所有僵尸
	{
			for (auto plant : ((GameLayer*)this->getParent())->_peaShooterLayer->_peaShooterVector)//遍历所有豌豆射手
			{
				if (plant->plantBounding().intersectsRect(zombie->zombieBounding()))//如果相交
				{
					
					//僵尸攻击植物
					if (zombie->numberOfRunningActions() != 1)
					{
						zombieAttackPlant.insert(zombie, plant);
						zombie->stopAllActions();
						zombie->runAction(RepeatForever::create(zombie->attackAnimation()));
					}
				}
			}
	}
	for (auto iter = zombieAttackPlant.begin(); iter != zombieAttackPlant.end();)
	{
		auto x = *iter;
		auto zombie = x.first;
		auto plant = x.second;
		plant->_plantHP -= 1;
		if (plant->_plantHP <= 0)
		{
			zombie->stopAllActions();
			zombie->runAction(RepeatForever::create(zombie->walkAnimation()));
			zombie->runAction(zombie->normalZombieMoveWay());
			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[plant->_position[0]][plant->_position[1]] = false;
			plant->removeFromParent();
			//((GameLayer*)this->getParent())->_peaShooterLayer->_peaShooterVector.eraseObject(plant);
			zombieAttackPlant.erase(iter++);
		}
		else iter++;
	}
}

void BoundingLayer::update(float dlt)
{
	//this->bulletBoundingZombie();//子弹碰撞僵尸，对僵尸造成伤害
	//this->zombieEatPlant();//僵尸吃植物
}
