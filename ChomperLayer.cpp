#include "ChomperLayer.h"
#include "GameLayer.h"
#include "MapLayer.h"
extern Vector<PlantBaseClass*> _plantVector;
extern Vector<ZombieBaseClass*> _zombieVector;

ChomperLayer::ChomperLayer()
{
	this->_chomperSprite = NULL;
}

ChomperLayer::~ChomperLayer()
{
}

bool ChomperLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	scheduleUpdate();
	return true;
}

void ChomperLayer::initChomperSprite(Touch * touch)
{
	//创建一个静态的精灵，未被种下时
	Sprite* _chomperStatic = Sprite::create("res/ChomperStatic.png");
	_chomperStatic->setPosition(touch->getLocation());
	this->addChild(_chomperStatic);

	auto lis = EventListenerMouse::create();
	//鼠标移动，则精灵跟着移动
	lis->onMouseMove = [=](EventMouse* e) {
		_chomperStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		return true;
	};
	//当鼠标按键抬起时，精灵被种下，同时取消鼠标监听
	lis->onMouseUp = [=](EventMouse* e) {
		this->removeChild(_chomperStatic);

		//判断种坚果墙位置是否合法
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if (((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y))
		{
			//精灵被种下，创建动图精灵
			this->_chomperSprite = ChomperSprite::create();
			this->addChild(_chomperSprite);

			this->_chomperVector.pushBack(this->_chomperSprite);//将精灵添加到数组中
			_plantVector.pushBack(this->_chomperSprite);

			//this->_peaShooterTime.push_back(0);//刚被种下，时间置为0

			//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
			this->_chomperSprite->setPosition(x + 10, y + 20);
			this->_chomperSprite->_position[0] = (x - 200) / 90;
			this->_chomperSprite->_position[1] = y / 100;
			((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
				= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 150;//每产生一个食人花消耗150金币
		}
		else//位置错误
		{
			//((GameLayer*)this->getParent())->_bulletLayer->unschedule(schedule_selector(BulletLayer::initBulletSprite));
			//this->removeChild(_peaShooterSprite);
		}
		_eventDispatcher->removeEventListener(lis);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);
}



void ChomperLayer::chomperAttackZombie()
{
	for (auto i = this->_chomperVector.begin(); i != this->_chomperVector.end(); i++)
	{
		if ((*i)->_eatingZombie == true)
		{
			(*i)->_ateTime++;
			if ((*i)->_ateTime == (*i)->_ateDownTime)//消化完了
			{
				(*i)->_eatingZombie = false;
				(*i)->_ateTime = 0;
				(*i)->stopAllActions();
				(*i)->runAction((*i)->chomperNormal());
			}
		}
		for (auto j = _zombieVector.begin(); j != _zombieVector.end(); j++)
		{
			if ((*i)->_eatingZombie == false)
			{
				if ((*j)->zombieBounding().intersectsRect((*i)->plantBounding()))
				{
					//植物动作变化
					(*i)->stopAllActions();
					(*i)->runAction((*i)->chomperDigest());
					auto tmp = *j;
					auto a = j;
					//(*j)->_hp -= 200;
					/*(*i)->runAction(Sequence::create((*i)
						->chomperAttack(), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tmp)),
						(*i)->chomperDigest(),
						NULL));*/
					(*i)->runAction(Sequence::create((*i)
						->chomperAttack(), CallFunc::create([tmp]() {
							tmp->_hp -= 200;
							tmp->removeFromParent();
							
							//_zombieVector.erase(a);
							}),
						(*i)->chomperDigest(),
						NULL));
					//把僵尸吃了，僵尸消失
					//(*j)->removeFromParent();
					//_zombieVector.erase(j);
					(*i)->_eatingZombie = true;

					break;
				}
				
			}
		}
	}
}
void ChomperLayer::diedChomper()
{
	for (auto i = _chomperVector.begin(); i != _chomperVector.end();)
	{
		log("chomper hp %d", (*i)->_plantHP);
		if ((*i)->_plantHP < 0)
		{
			(*i)->stopAllActions();
			for (auto j = _plantVector.begin(); j != _plantVector.end(); j++)
			{
				if ((*i) == (*j))
				{
					_plantVector.erase(j);
					break;
				}
			}

			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(*i)->_position[0]][(*i)->_position[1]] = false;
			(*i)->removeFromParent();
			i = _chomperVector.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void ChomperLayer::update(float dt)
{
	this->chomperAttackZombie();
	this->diedChomper();
}
