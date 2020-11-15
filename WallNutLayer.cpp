#include "WallNutLayer.h"
#include "GameLayer.h"
#include "MapLayer.h"
extern Vector<PlantBaseClass*> _plantVector;
extern Vector<ZombieBaseClass*> _zombieVector;
WallNutLayer::WallNutLayer()
{
	this->_wallNutSprite = NULL;
}

WallNutLayer::~WallNutLayer()
{
}

bool WallNutLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	scheduleUpdate();
	return true;
}

void WallNutLayer::initWallNutSprite(Touch * touch)
{
	//创建一个静态的精灵，未被种下时
	Sprite* _wallNutStatic = Sprite::create("res/WallNutStatic.png");
	_wallNutStatic->setPosition(touch->getLocation());
	this->addChild(_wallNutStatic);

	auto lis = EventListenerMouse::create();
	//鼠标移动，则精灵跟着移动
	lis->onMouseMove = [=](EventMouse* e) {
		_wallNutStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		return true;
	};
	//当鼠标按键抬起时，精灵被种下，同时取消鼠标监听
	lis->onMouseUp = [=](EventMouse* e) {
		this->removeChild(_wallNutStatic);

		//判断种坚果墙位置是否合法
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if (((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y))
		{
			//精灵被种下，创建动图精灵
			this->_wallNutSprite = WallNutSprite::create();
			this->addChild(_wallNutSprite);

			this->_wallNutVector.pushBack(this->_wallNutSprite);//将精灵添加到数组中
			_plantVector.pushBack(this->_wallNutSprite);

			//this->_peaShooterTime.push_back(0);//刚被种下，时间置为0

			//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
			this->_wallNutSprite->setPosition(x, y);
			this->_wallNutSprite->_position[0] = (x - 200) / 90;
			this->_wallNutSprite->_position[1] = y / 100;
			((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
				= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 50;//每产生一个坚果墙消耗50金币
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

void WallNutLayer::diedWallNut()
{
}

void WallNutLayer::update(float dt)
{
}
