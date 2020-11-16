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
	//创建一个静态僵尸，为被种下时
	Sprite* _normalZombieStatic = Sprite::create("res/ZombieStatic.png");
	_normalZombieStatic->setPosition(touch->getLocation());
	this->addChild(_normalZombieStatic);

	
	auto lis = EventListenerMouse::create();
	//鼠标移动，则精灵跟着移动
	lis->onMouseMove = [=](EventMouse* e) {
		_normalZombieStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		return true;
	};
	//当鼠标按键抬起时，精灵被种下，同时取消鼠标监听
	lis->onMouseUp = [=](EventMouse* e) {
		this->removeChild(_normalZombieStatic);

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
				= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 100;//每产生一个僵尸消耗100金币
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

//void NormalZombieLayer::normalZombieMoveWay()//在此修改僵尸移速
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
		if ((*i)->_hp == (*i)->noHeadHp)//此时僵尸头掉了
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
					(*i)->runAction((*i)->walkAnimation());//11/16修改了此处，没必要用repeatforever create
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
