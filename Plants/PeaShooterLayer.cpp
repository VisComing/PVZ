#include "PeaShooterLayer.h"
#include "../Base/GameLayer.h"
#include "../Base/MapLayer.h"
#include "../Base/socket.h"
#include <string>
#include "../Base/global.h"
extern Vector<PlantBaseClass*> _plantVectorGlobalVariable;
extern Vector<ZombieBaseClass*> _zombieVectorGlobalVariable;
PeaShooterLayer::PeaShooterLayer()
{
	this->shadowTag = 0;
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

void PeaShooterLayer::initPeaShooterSprite(Vec2 touch)
{	
	//创建一个静态的精灵，未被种下时
	Sprite* _peaShooterStatic = Sprite::create("res/PeashooterStatic.png");
	Sprite* _peaShooterStaticShadow = Sprite::create("res/PeashooterStatic.png");
	_peaShooterStatic->setPosition(touch);
	_peaShooterStaticShadow->setOpacity(150);
	this->addChild(_peaShooterStaticShadow);
	this->addChild(_peaShooterStatic);

	auto lis = EventListenerMouse::create();
	//鼠标移动，则精灵跟着移动
	lis->onMouseMove = [=](EventMouse* e) {
		_peaShooterStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y);
		_peaShooterStaticShadow->setPosition(x, y);
		return true;
	};
	//当鼠标按键再一次按下时，精灵被种下，同时取消鼠标监听
	lis->onMouseDown = [=](EventMouse* e) {
		this->removeChild(_peaShooterStatic);
		this->removeChild(_peaShooterStaticShadow);
		Sprite* shadow = Sprite::create("res/plantshadow.png");
		this->addChild(shadow);
		shadow->setTag(++(this->shadowTag));
		//判断种豌豆射手位置是否合法
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if (((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x,y))
		{
				//精灵被种下，创建动图精灵
				this->_peaShooterSprite = PeaShooterSprite::create();
				this->addChild(_peaShooterSprite);
				this->_peaShooterSprite->_peaShooterSpriteTag = this->shadowTag;
				this->_peaShooterVector.pushBack(this->_peaShooterSprite);//将精灵添加到数组中
				_plantVectorGlobalVariable.pushBack(this->_peaShooterSprite);
				this->_peaShooterSprite->startGrowPlantMusic();
				this->_peaShooterTime.push_back(0);//刚被种下，时间置为0

				//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
				((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
				this->_peaShooterSprite->setPosition(x, y);
				//在此处发送
				if (isSinglePlayerGameMode == false)
				{
					std::string message = "PeaShooter:" + to_string(x) + "," + to_string(y) + ";\n";
					TCPSocket::getInstance()->writeIntoServer(message);
				}
				shadow->setPosition(x - 5, y - 27);
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

void PeaShooterLayer::producePeaShooterSprite(Vec2 position)
{
	int x = position.x;
	int y = position.y;
	Sprite* shadow = Sprite::create("res/plantshadow.png");
	this->addChild(shadow);
	shadow->setTag(++(this->shadowTag));
	//精灵被种下，创建动图精灵
	this->_peaShooterSprite = PeaShooterSprite::create();
	this->addChild(_peaShooterSprite);
	this->_peaShooterSprite->_peaShooterSpriteTag = this->shadowTag;
	this->_peaShooterVector.pushBack(this->_peaShooterSprite);//将精灵添加到数组中
	_plantVectorGlobalVariable.pushBack(this->_peaShooterSprite);
	this->_peaShooterSprite->startGrowPlantMusic();
	this->_peaShooterTime.push_back(0);//刚被种下，时间置为0

	//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
	((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
	this->_peaShooterSprite->setPosition(x, y);
	shadow->setPosition(x - 5, y - 27);
	this->_peaShooterSprite->_position[0] = (x - 200) / 90;
	this->_peaShooterSprite->_position[1] = y / 100;
	//((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
	//	= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 100;//每产生一个植物枪消耗100金币
	((GameLayer*)this->getParent())->_bulletLayer->schedule(schedule_selector(BulletLayer::initBulletSprite), 0.1f);

}

void PeaShooterLayer::diedPeaShooter()
{
	for (auto i = _peaShooterVector.begin(); i != _peaShooterVector.end();)
	{
		if ((*i)->_plantHP <= 0)
		{
			for (auto j = _plantVectorGlobalVariable.begin(); j != _plantVectorGlobalVariable.end(); j++)
			{
				if ((*i) == (*j))
				{
					_plantVectorGlobalVariable.erase(j);
					break;
				}
			}
			this->removeChildByTag((*i)->_peaShooterSpriteTag);
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

void PeaShooterLayer::removePlant(Vec2 touch)
{
	Sprite* _shovel = Sprite::create("res/Shovel.png");
	_shovel->setPosition(touch);
	this->addChild(_shovel);
	auto lis = EventListenerMouse::create();
	//鼠标移动，则精灵跟着移动
	lis->onMouseMove = [=](EventMouse* e) {
		_shovel->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		_shovel->setPosition(x, y);
		return true;
	};
	lis->onMouseDown = [=](EventMouse* e) {
		this->removeChild(_shovel);
		//判断种豌豆射手位置是否合法
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		Vec2 _pos(x, y);
		for (auto x : _plantVectorGlobalVariable)
		{
			if (x->getBoundingBox().containsPoint(_pos))
			{
				this->_peaShooterSprite->startGrowPlantMusic();
				x->_plantHP -= 30000;
				break;
			}
		}
		_eventDispatcher->removeEventListener(lis);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);
}
