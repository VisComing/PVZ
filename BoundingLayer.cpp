#include "BoundingLayer.h"
#include "GameLayer.h"
#include <utility>
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
	Vector<PotatoMineSprite*> potatoMineRemove;//��Ҫɾ�����������׾���
	for (auto peaBullet : ((GameLayer*)this->getParent())->_bulletLayer->_bulletVector)//���������ӵ�
	{		
		for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//�������н�ʬ
		{
			if (peaBullet->getBoundingBox().intersectsRect(normalZombie->NormalZombieBounding()))//����ӵ��ͽ�ʬ��ײ
			{
				bulletRemove.pushBack(peaBullet);//��ɾ�����ӵ�
				peaBullet->removeFromParent();//���ӵ�ɾ��
				//peaBullet->runAction(Sequence::createWithTwoActions(((GameLayer*)this->getParent())->_bulletLayer->_bulletSprite->_bulletBroken,
				//	CallFunc::create([peaBullet]() {
				//		peaBullet->removeFromParent();//���ӵ�ɾ��
				//		})
				//));

				normalZombie->_hp -= 15;//��ʬ��Ѫ
				
				//normalZombie->runAction(Blink::create(0.07f, 1));

				if (normalZombie->_hp == 25)//��ʱ��ʬͷ����
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
					zombieRemove.pushBack(normalZombie);//��������ʬ��ӵ���ɾ������
					normalZombie->runAction(Sequence::createWithTwoActions(((GameLayer*)this->getParent())->_normalZombieLayer
						->_normalZombieSprite->downTheGround(), CallFunc::create([normalZombie]() {
							normalZombie->removeFromParent();//����ʬɾ��
							})));
				}
				break;//һ���ӵ�ֻ����ײһ����ʬ
			}
		}
	}
	set<NormalZombieSprite*> normalZombieBoomDied;//��ը���Ľ�ʬ
	for (auto potatoMine : ((GameLayer*)this->getParent())->_potatoMineLayer->_potatoMineVector)//�������е���������
	{
		if (potatoMine->_potatoMineTime == 6)
		{
			for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//�������н�ʬ
			{

				if (potatoMine->getBoundingBox().intersectsRect(normalZombie->NormalZombieBounding()))//����������׺ͽ�ʬ��ײ
				{
					potatoMineRemove.pushBack(potatoMine);
					((GameLayer*)this->getParent())->_mapLayer->_isPlanted[potatoMine->_position[0]][potatoMine->_position[1]] = false;
					potatoMine->removeFromParent();//ԭ�����������Ƴ��˰�
					normalZombieBoomDied.insert(normalZombie);
					//��ʬ����
					//normalZombie->stopAllActions();
					//zombieRemove.pushBack(normalZombie);//��������ʬ��ӵ���ɾ������
					//normalZombie->runAction(Sequence::createWithTwoActions(((GameLayer*)this->getParent())->_normalZombieLayer
					//	->_normalZombieSprite->explodAction(), CallFunc::create([normalZombie]() {
					//		normalZombie->removeFromParent();//����ʬɾ��
					//		})));
				}
			}
		}
		//else//��û�г��󣬿��Ա���ʬ����
		//{
		//	for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//�������н�ʬ
		//	{
		//		if (potatoMine->getBoundingBox().intersectsRect(normalZombie->NormalZombieBounding()))//����������׺ͽ�ʬ��ײ
		//		{

		//		}
		//	}
		//}
	}
	for (auto normalZombie : normalZombieBoomDied)
	{
		normalZombie->stopAllActions();
		zombieRemove.pushBack(normalZombie);//��������ʬ��ӵ���ɾ������
		normalZombie->runAction(Sequence::createWithTwoActions(((GameLayer*)this->getParent())->_normalZombieLayer
			->_normalZombieSprite->explodAction(), CallFunc::create([normalZombie]() {
				normalZombie->removeFromParent();//����ʬɾ��
				})));
	}

	for (auto bullet : bulletRemove)//������ɾ�����ӵ�,���ӵ�ɾ��
	{
		//bullet->stopAllActions();//ֹͣ���ж���
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
		//ɾ����ֲ������ڵ�ͼ���Ƴ�
		//log("%d   %d", potatoMine->_position[0], potatoMine->_position[0]);
		
		((GameLayer*)this->getParent())->_potatoMineLayer->_potatoMineVector.eraseObject(potatoMine);
		//potatoMine->removeFromParent();
	}

}
//Map<NormalZombieSprite*, PeaShooterSprite*> zombieAttackPeaShooter;
void BoundingLayer::zombieEatPlant()
{
	//for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//�������н�ʬ
	//{
	//	for (auto potatoMine : ((GameLayer*)this->getParent())->_potatoMineLayer->_potatoMineVector)
	//	{
	//		if (potatoMine->_potatoMineTime != 6)
	//		{
	//			if (potatoMine->getBoundingBox().intersectsRect(normalZombie->NormalZombieBounding()))//����������׺ͽ�ʬ��ײ
	//			{
	//				if (!normalZombie->getActionByTag(2368))
	//				{
	//					normalZombie->stopAllActions();
	//					normalZombie->runAction(RepeatForever::create(normalZombie->attackAnimation()));
	//				}
	//			}
	//		}
	//	}
	//}
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
		if (flagExist == false)//��ʬ�Ѿ�����
		{
			zombieAttackPeaShooterRemove.insert(x.first);
		}
	}
	for (auto x : zombieAttackPeaShooterRemove)
	{
		this->zombieAttackPeaShooter.erase(this->zombieAttackPeaShooter.find(x));
	}
	zombieAttackPeaShooterRemove.clear();

	set<PeaShooterSprite*> peaShooterRemove;//���Ƴ����㶹����
	
	for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//�������н�ʬ
	{		
		if (this->zombieAttackPeaShooter.find(normalZombie) == this->zombieAttackPeaShooter.end())
		{
			for (auto peaShooter : ((GameLayer*)this->getParent())->_peaShooterLayer->_peaShooterVector)//���������㶹����
			{
				if (peaShooter->getBoundingBox().intersectsRect(normalZombie->NormalZombieBounding()))//����ཻ
				{
					//��ʬ����ֲ��
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
			//�����������ڹ�����ֲ��Ľ�ʬ
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
			//ִ��peaShooter->removeFromParent();������bug���֣�2020/11/13
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
	}
}

void BoundingLayer::zombieEatPlant(ZombieBaseClass * zombieBase, PlantBaseClass * plantBase)
{
	set<PeaShooterSprite*> peaShooterRemove;//���Ƴ����㶹����

	for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//�������н�ʬ
	{
		if (this->zombieAttackPeaShooter.find(normalZombie) == this->zombieAttackPeaShooter.end())
		{
			for (auto peaShooter : ((GameLayer*)this->getParent())->_peaShooterLayer->_peaShooterVector)//���������㶹����
			{
				if (peaShooter->getBoundingBox().intersectsRect(normalZombie->NormalZombieBounding()))//����ཻ
				{
					//��ʬ����ֲ��
					if (!normalZombie->getActionByTag(2368))
					{
						normalZombie->stopAllActions();
						normalZombie->runAction(RepeatForever::create(normalZombie->attackAnimation()));
					}
				}
			}
		}
	}
}
