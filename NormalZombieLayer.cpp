#include "NormalZombieLayer.h"
#include "GameLayer.h"
extern Vector<ZombieBaseClass*>_zombieVector;
extern Vector<PlantBaseClass*> _plantVector;
NormalZombieLayer::NormalZombieLayer()
{
	_normalZombieSprite = NULL;
}
NormalZombieLayer::~NormalZombieLayer()
{

}

bool NormalZombieLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	scheduleUpdate();
	return true;
}


void NormalZombieLayer::initNormalZombieSprite(Touch* touch)
{
	//����һ����̬��ʬ��Ϊ������ʱ
	Sprite* _normalZombieStatic = Sprite::create("res/ZombieStatic.png");
	_normalZombieStatic->setPosition(touch->getLocation());
	this->addChild(_normalZombieStatic);

	
	auto lis = EventListenerMouse::create();
	//����ƶ�����������ƶ�
	lis->onMouseMove = [=](EventMouse* e) {
		_normalZombieStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		return true;
	};
	//����갴��̧��ʱ�����鱻���£�ͬʱȡ��������
	lis->onMouseUp = [=](EventMouse* e) {
		this->removeChild(_normalZombieStatic);

		//�ж��н�ʬλ���Ƿ�Ϸ�
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if ((x > 995 && x < 1100) && (y < 510 && y > 30))
		{
			x = 1045;
			if (y > 30 && y < 129)
				y = 80;
			else if (y < 219)
				y = 175;
			else if (y < 320)
				y = 274;
			else if (y < 419)
				y = 375;
			else if (y < 510)
				y = 475;
			//��ʬ�����£�������ͼ
			this->_normalZombieSprite = NormalZombieSprite::create();
			this->_normalZombieSprite->setPosition(touch->getLocation());
			this->addChild(_normalZombieSprite);

			this->_normalZombieVector.pushBack(this->_normalZombieSprite);//����ʬ��ӵ�������
			_zombieVector.pushBack(this->_normalZombieSprite);

			this->_normalZombieSprite->setPosition(x, y + 20);
			((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
				= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 100;//ÿ����һ����ʬ����100���
			this->_normalZombieSprite->normalZombieMoveWay();
		}
		else
		{
			//this->removeChild(_normalZombieSprite);
		}
		_eventDispatcher->removeEventListener(lis);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);
}

//void NormalZombieLayer::normalZombieMoveWay()//�ڴ��޸Ľ�ʬ����
//{
//	Action* normalZombieMove = MoveTo::create(this->_normalZombieSprite->getPositionX() / 40, Vec2(0, this->_normalZombieSprite->getPositionY()));
//	this->_normalZombieSprite->runAction(normalZombieMove);
//}
//
//FiniteTimeAction* NormalZombieLayer::noHeadNormalZombieMoveWay()
//{
//	FiniteTimeAction* normalZombieMove = MoveTo::create(15, Vec2(0, this->_normalZombieSprite->getPositionY()));
//	//this->_normalZombieSprite->runAction(normalZombieMove);
//	return normalZombieMove;
//}

void NormalZombieLayer::diedNormalZombie()
{
	for (auto i = _normalZombieVector.begin(); i != _normalZombieVector.end();)
	{
		if ((*i)->_hp == (*i)->noHeadHp)//��ʱ��ʬͷ����
		{
			(*i)->stopAllActions();
			(*i)->runAction((*i)->noHeadWalkAnimation());
			(*i)->runAction((*i)->normalZombieMoveWay());
			//(*i)->runAction(Spawn::create((*i)->noHeadAnimation(),(*i)->normalZombieMoveWay(), NULL));
			tmpSprite = Sprite::create();
			this->addChild(tmpSprite);
			tmpSprite->setPosition((*i)->getPosition());
			(*i)->_hp -= 1;
			//tmpSprite->runAction((*i)->headAnimation());
			tmpSprite->runAction(Sequence::createWithTwoActions((*i)
				->headAnimation(), CallFunc::create([this]() {
						tmpSprite->removeFromParent(); 
					})));
		}

		if ((*i)->_hp <= 0)
		{
			//��ȫ����ʬ�����н���ɾ��
			for (auto j = _zombieVector.begin(); j != _zombieVector.end(); j++)
			{
				if ((*i) == (*j))
				{
					_zombieVector.erase(j);
					break;
				}
			}
			(*i)->stopAllActions();
			auto tmp = *i;
			//ԭ�������е����⣬��ִ�ж�����Ȼ��ִ��lambda���ʽ��ִ�е�lamidaʱ�����i�Ѿ���ɾ����
			//2020/11/15�賿
			if ((*i)->typeOfDeath == 0)//��ʬ���ӵ�����
			{
				(*i)->runAction(Sequence::createWithTwoActions((*i)
					->downTheGround(), CallFunc::create([tmp]() {
						(tmp)->removeFromParent();//����ʬɾ��
						})));
			}
			else if ((*i)->typeOfDeath == 1)//��ʬ��ը��
			{
				(*i)->runAction(Sequence::createWithTwoActions((*i)
					-> explodAnimation(), CallFunc::create([tmp]() {
						(tmp)->removeFromParent();//����ʬɾ��
						})));
			}
			//ע�⣬��һ��Ҫ���ڸ�ѭ�������в����������֮ǰɾ���ˣ���ô��������Ҫʹ��������ô����
			i = _normalZombieVector.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void NormalZombieLayer::normalZombieAttackPlant()
{
	for (auto i = _normalZombieVector.begin(); i != _normalZombieVector.end(); i++)
	{
		
		if ((*i)->_hp > 0)
		{
			
			for (auto j = _plantVector.begin(); j != _plantVector.end(); j++)
			{
				if ((*j)->plantBounding().intersectsRect((*i)->zombieBounding()))//�����ײ
				{
					(*j)->_plantHP -= 1;
					if ((*i)->numberOfRunningActions() != 1)
					{
						(*i)->stopAllActions();
						if ((*i)->_hp > (*i)->noHeadHp)
						{
							(*i)->runAction((*i)->attackAnimation());
						}
						else
						{
							(*i)->runAction((*i)->zombieLostHeadAttackAnimation());
						}
					}
				}
			}
			bool flag = false;
			for (auto x : _plantVector)
			{
				if (x->plantBounding().intersectsRect((*i)->zombieBounding()))
				{
					flag = true;
					break;
				}
			}
			if ((*i)->numberOfRunningActions() == 1 && flag == false)
			{
				(*i)->stopAllActions();
				if ((*i)->_hp > (*i)->noHeadHp)
				{
					(*i)->runAction((*i)->walkAnimation());//11/16�޸��˴˴���û��Ҫ��repeatforever create
				}
				else
				{
					(*i)->runAction((*i)->noHeadWalkAnimation());
				}
				(*i)->runAction((*i)->normalZombieMoveWay());
			}
		}
	}

}

void NormalZombieLayer::update(float dt)
{
	this->diedNormalZombie();
	this->normalZombieAttackPlant();
}
