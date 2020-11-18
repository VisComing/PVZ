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
	//创建一个静态僵尸，为被种下时
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
	//鼠标移动，则精灵跟着移动
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
	//当鼠标按键抬起时，精灵被种下，同时取消鼠标监听
	lis->onMouseDown = [=](EventMouse* e) {
		this->removeChild(_normalZombieStatic);
		this->removeChild(_normalZombieStaticShadow);
		//判断中僵尸位置是否合法
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
			//僵尸被种下，创建动图
			this->_normalZombieSprite = NormalZombieSprite::create();
			this->_normalZombieSprite->setPosition(touch->getLocation());
			this->addChild(_normalZombieSprite);

			this->_normalZombieVector.pushBack(this->_normalZombieSprite);//将僵尸添加到数组中
			_zombieVector.pushBack(this->_normalZombieSprite);

			


			this->_normalZombieSprite->setPosition(x, y + 20);
			((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
				= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - _zombieDollar;//每产生一个僵尸消耗金币
			//此处需要用runaction，否则没有僵尸图像

			//在此处修改僵尸移速，僵尸血量，僵尸价格
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
		//注意此时僵尸掉头的值，一定是离散的值，不能用小于等于、大于等于
		if ((*i)->_hp == 20 || (*i)->_hp == 10 || (*i)->_hp == 15)//此时僵尸头掉了
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
			//让掉头的动作靠前一点，更显得真实
			tmpSprite->setPositionX(tmpSprite->getPositionX() + 35);

			//注意，为了使僵尸只掉一次头，这里把僵尸的血量减一
			(*i)->_hp -= 1;
			//tmpSprite->runAction((*i)->headAnimation());
			tmpSprite->runAction(Sequence::createWithTwoActions((*i)
				->headAnimation(), CallFunc::create([tmpSprite]() {
						tmpSprite->removeFromParent(); 
					})));
		}

		if ((*i)->_hp <= 0)
		{
			//从全部僵尸数组中将其删除
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
			//原来是序列的问题，先执行动作，然后执行lambda表达式，执行到lamida时里面的i已经被删除了
			//2020/11/15凌晨
			if ((*i)->typeOfDeath == 0)//僵尸被子弹打死
			{
				(*i)->runAction(Sequence::createWithTwoActions((*i)
					->downTheGround(), CallFunc::create([tmp]() {
						(tmp)->removeFromParent();//将僵尸删除
						})));
			}
			else if ((*i)->typeOfDeath == 1)//僵尸被炸死
			{
				(*i)->runAction(Sequence::createWithTwoActions((*i)
					-> explodAnimation(), CallFunc::create([tmp]() {
						(tmp)->removeFromParent();//将僵尸删除
						})));
			}
			//注意，下一行要放在该循环的所有操作后，如果在之前删除了，那么接下来还要使用它的怎么办呢
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
				if ((*j)->plantBounding().intersectsRect((*i)->zombieBounding()))//如果碰撞
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
						(*i)->runAction((*i)->normalZombieWalkAnimation());//11/16修改了此处，没必要用repeatforever create
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
