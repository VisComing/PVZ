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
	for (auto peaBullet : ((GameLayer*)this->getParent())->_touchLayer->_bulletVector)//���������ӵ�
	{		
		for (auto normalZombie : ((GameLayer*)this->getParent())->_normalZombieLayer->_normalZombieVector)//�������н�ʬ
		{
			if (peaBullet->boundingBox().intersectsRect(normalZombie->NormalZombieBounding()))//����ӵ��ͽ�ʬ��ײ
			{
				bulletRemove.pushBack(peaBullet);//��ɾ�����ӵ�
				normalZombie->_hp -= 15;//��ʬ��Ѫ
				
				normalZombie->runAction(Blink::create(0.07, 1));

				if (normalZombie->_hp == 25)//��ʱ��ʬͷ����
				{
					normalZombie->stopAllActions();
					normalZombie->runAction(Spawn::create(((GameLayer*)this->getParent())->_normalZombieLayer
						->_normalZombieSprite->noHeadAnimation(), ((GameLayer*)this->getParent())->_normalZombieLayer
						->_normalZombieSprite->headAnimation(),((GameLayer*)this->getParent())->_normalZombieLayer
							->noHeadNormalZombieMoveWay(), NULL));
				}

				if (normalZombie->_hp <= 0)
				{
					zombieRemove.pushBack(normalZombie);//��������ʬ��ӵ���ɾ������
					
				}
				break;//һ���ӵ�ֻ����ײһ����ʬ
			}
		}
	}
	for (auto bullet : bulletRemove)//������ɾ�����ӵ�,���ӵ�ɾ��
	{
		//bullet->stopAllActions();//ֹͣ���ж���
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