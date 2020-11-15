#include "PeaShooterLayer.h"
#include "GameLayer.h"
#include "MapLayer.h"
extern Vector<PlantBaseClass*> _plantVector;
extern Vector<ZombieBaseClass*> _zombieVector;
PeaShooterLayer::PeaShooterLayer()
{
	this->_peaShooterSprite = NULL;
}

PeaShooterLayer::~PeaShooterLayer()
{
}

bool PeaShooterLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	scheduleUpdate();
	return true;
}

void PeaShooterLayer::initPeaShooterSprite(Touch * touch)
{	
	//创建一个静态的精灵，未被种下时
	Sprite* _peaShooterStatic = Sprite::create("res/PeashooterStatic.png");
	_peaShooterStatic->setPosition(touch->getLocation());
	this->addChild(_peaShooterStatic);

	auto lis = EventListenerMouse::create();
	//鼠标移动，则精灵跟着移动
	lis->onMouseMove = [=](EventMouse* e) {
		_peaShooterStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		return true;
	};
	//当鼠标按键抬起时，精灵被种下，同时取消鼠标监听
	lis->onMouseUp = [=](EventMouse* e) {
		this->removeChild(_peaShooterStatic);

		//判断种豌豆射手位置是否合法
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if (((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x,y))
		{
				//精灵被种下，创建动图精灵
				this->_peaShooterSprite = PeaShooterSprite::create();
				this->addChild(_peaShooterSprite);

				this->_peaShooterVector.pushBack(this->_peaShooterSprite);//将精灵添加到数组中
				_plantVector.pushBack(this->_peaShooterSprite);
				
				this->_peaShooterTime.push_back(0);//刚被种下，时间置为0

				//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
				((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
				this->_peaShooterSprite->setPosition(x, y);
				this->_peaShooterSprite->_position[0] = (x - 200) / 90;
				this->_peaShooterSprite->_position[1] = y / 100;
				((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
					= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 100;//每产生一个植物枪消耗100金币
				((GameLayer*)this->getParent())->_bulletLayer->schedule(schedule_selector(BulletLayer::initBulletSprite), 0.1f);
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

void PeaShooterLayer::diedPeaShooter()
{
	for (auto i = _peaShooterVector.begin(); i != _peaShooterVector.end();)
	{
		if ((*i)->_plantHP <= 0)
		{
			for (auto j = _plantVector.begin(); j != _plantVector.end(); j++)
			{
				if ((*i) == (*j))
				{
					_plantVector.erase(j);
					break;
				}
			}
			(*i)->removeFromParent();
			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(*i)->_position[0]][(*i)->_position[1]] = false;
			i = _peaShooterVector.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void PeaShooterLayer::update(float dt)
{
	this->diedPeaShooter();
}
