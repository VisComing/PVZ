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


void NormalZombieLayer::initNormalZombieSprite(Touch* touch, string zombieName)
{

	int _zombieDollar = 0;
	//����һ����̬��ʬ��Ϊ������ʱ
	Sprite* _normalZombieStatic;
	Sprite* _normalZombieStaticShadow;
	if (zombieName == "NormalZombie")
	{
		_normalZombieStatic = Sprite::create("res/ZombieStatic.png");
		_normalZombieStaticShadow = Sprite::create("res/ZombieStatic.png");
		_zombieDollar = 100;
	}
	else if (zombieName == "FlagZombie")
	{
		_normalZombieStatic = Sprite::create("res/FlagZombieStatic.png");
		_normalZombieStaticShadow = Sprite::create("res/FlagZombieStatic.png");
		_zombieDollar = 120;
	}
	else if (zombieName == "ConeheadZombie")
	{
		_normalZombieStatic = Sprite::create("res/ConeheadZombieStatic.png");
		_normalZombieStaticShadow = Sprite::create("res/ConeheadZombieStatic.png");
		_zombieDollar = 150;
	}
	else if (zombieName == "BucketheadZombie")
	{
		_normalZombieStatic = Sprite::create("res/BucketheadZombieStatic.png");
		_normalZombieStaticShadow = Sprite::create("res/BucketheadZombieStatic.png");
		_zombieDollar = 175;
	}
	_normalZombieStatic->setPosition(touch->getLocation());
	_normalZombieStaticShadow->setOpacity(180);
	this->addChild(_normalZombieStaticShadow);
	this->addChild(_normalZombieStatic);
	
	
	auto lis = EventListenerMouse::create();
	//����ƶ�����������ƶ�
	lis->onMouseMove = [=](EventMouse* e) {
		_normalZombieStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
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
		}
		_normalZombieStaticShadow->setPosition(x, y);
		return true;
	};
	//����갴��̧��ʱ�����鱻���£�ͬʱȡ��������
	lis->onMouseDown = [=](EventMouse* e) {
		this->removeChild(_normalZombieStatic);
		this->removeChild(_normalZombieStaticShadow);
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
				= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - _zombieDollar;//ÿ����һ����ʬ���Ľ��
			//�˴���Ҫ��runaction������û�н�ʬͼ��

			//�ڴ˴��޸Ľ�ʬ���٣���ʬѪ������ʬ�۸�
			if (zombieName == "NormalZombie")
			{
				this->_normalZombieSprite->zombieMoney = 100;
				this->_normalZombieSprite->runAction(this->_normalZombieSprite->normalZombieWalkAnimation());
				this->_normalZombieSprite->zombieSpeed = 40;
				this->_normalZombieSprite->_hp = 100;
			}
			else if (zombieName == "FlagZombie")
			{
				this->_normalZombieSprite->zombieMoney = 120;
				this->_normalZombieSprite->runAction(this->_normalZombieSprite->flagZombieWalkAnimation());
				this->_normalZombieSprite->zombieSpeed = 48;
				this->_normalZombieSprite->_hp = 110;
			}
			else if (zombieName == "ConeheadZombie")
			{
				this->_normalZombieSprite->zombieMoney = 150;
				this->_normalZombieSprite->runAction(this->_normalZombieSprite->coneheadZombieWalkAnimation());
				this->_normalZombieSprite->zombieSpeed = 55;
				this->_normalZombieSprite->_hp = 120;
			}
			else if (zombieName == "BucketheadZombie")
			{
				this->_normalZombieSprite->zombieMoney = 175;
				this->_normalZombieSprite->runAction(this->_normalZombieSprite->bucketheadZombieWalkAnimation());
				this->_normalZombieSprite->zombieSpeed = 62;
				this->_normalZombieSprite->_hp = 130;
			}
			this->_normalZombieSprite->_zombieName = zombieName;
			this->_normalZombieSprite->runAction(this->_normalZombieSprite->zombieMoveWay(this->_normalZombieSprite->zombieSpeed));
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

void NormalZombieLayer::diedNormalZombie()
{
	for (auto i = _normalZombieVector.begin(); i != _normalZombieVector.end();)
	{
		//ע���ʱ��ʬ��ͷ��ֵ��һ������ɢ��ֵ��������С�ڵ��ڡ����ڵ���
		if ((*i)->_hp == 20 || (*i)->_hp == 10 || (*i)->_hp == 15)//��ʱ��ʬͷ����
		{
			(*i)->stopAllActions();
			if((*i)->_zombieName == "NormalZombie" || (*i)->_zombieName == "ConeheadZombie" || (*i)->_zombieName == "BucketheadZombie")
				(*i)->runAction((*i)->normalZombieNoHeadWalkAnimation());
			else if((*i)->_zombieName == "FlagZombie")
				(*i)->runAction((*i)->flagZombieNoHeadWalkAnimation());
			(*i)->runAction((*i)->zombieMoveWay((*i)->zombieSpeed));
			//(*i)->runAction(Spawn::create((*i)->noHeadAnimation(),(*i)->normalZombieMoveWay(), NULL));
			auto tmpSprite = Sprite::create();
			this->addChild(tmpSprite);
			tmpSprite->setPosition((*i)->getPosition());
			//�õ�ͷ�Ķ�����ǰһ�㣬���Ե���ʵ
			tmpSprite->setPositionX(tmpSprite->getPositionX() + 35);

			//ע�⣬Ϊ��ʹ��ʬֻ��һ��ͷ������ѽ�ʬ��Ѫ����һ
			(*i)->_hp -= 1;
			//tmpSprite->runAction((*i)->headAnimation());
			tmpSprite->runAction(Sequence::createWithTwoActions((*i)
				->headAnimation(), CallFunc::create([tmpSprite]() {
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
					if ((*i)->getNumberOfRunningActions() != 1)
					{
						(*i)->stopAllActions();
						if ((*i)->_hp > (*i)->noHeadHp)
						{
							if((*i)->_zombieName == "NormalZombie")
								(*i)->runAction((*i)->normalZombieAttackAnimation());
							else if((*i)->_zombieName == "FlagZombie")
								(*i)->runAction((*i)->flagZombieAttackAnimation());
							else if ((*i)->_zombieName == "ConeheadZombie")
								(*i)->runAction((*i)->coneheadZombieAttackAnimation());
							else if ((*i)->_zombieName == "BucketheadZombie")
								(*i)->runAction((*i)->bucketheadZombieAttackAnimation());
						}
						else
						{
							if ((*i)->_zombieName == "NormalZombie" || (*i)->_zombieName == "ConeheadZombie" || (*i)->_zombieName == "BucketheadZombie")
								(*i)->runAction((*i)->normalZombieLostHeadAttackAnimation());
							else if ((*i)->_zombieName == "FlagZombie")
								(*i)->runAction((*i)->flagZombieLostHeadAttackAnimation());
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
			if ((*i)->getNumberOfRunningActions() == 1 && flag == false)
			{
				(*i)->stopAllActions();
				if ((*i)->_hp > (*i)->noHeadHp)
				{
					if ((*i)->_zombieName == "NormalZombie")
						(*i)->runAction((*i)->normalZombieWalkAnimation());//11/16�޸��˴˴���û��Ҫ��repeatforever create
					else if ((*i)->_zombieName == "FlagZombie")
						(*i)->runAction((*i)->flagZombieWalkAnimation());
					else if ((*i)->_zombieName == "ConeheadZombie")
						(*i)->runAction((*i)->coneheadZombieWalkAnimation());
					else if ((*i)->_zombieName == "BucketheadZombie")
						(*i)->runAction((*i)->bucketheadZombieWalkAnimation());
				}
				else
				{
					if ((*i)->_zombieName == "NormalZombie" || (*i)->_zombieName == "ConeheadZombie" || (*i)->_zombieName == "BucketheadZombie")
						(*i)->runAction((*i)->normalZombieNoHeadWalkAnimation());
					else if ((*i)->_zombieName == "FlagZombie")
						(*i)->runAction((*i)->flagZombieNoHeadWalkAnimation());
				}
				(*i)->runAction((*i)->zombieMoveWay((*i)->zombieSpeed));
			}
		}
	}

}

void NormalZombieLayer::update(float dt)
{
	this->diedNormalZombie();
	this->normalZombieAttackPlant();
}
