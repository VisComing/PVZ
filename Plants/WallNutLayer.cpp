#include "WallNutLayer.h"
#include "../Base/GameLayer.h"
#include "../Base/MapLayer.h"
#include "../Base/socket.h"
#include "../Base/global.h"
extern Vector<PlantBaseClass*> _plantVectorGlobalVariable;
extern Vector<ZombieBaseClass*> _zombieVectorGlobalVariable;
WallNutLayer::WallNutLayer()
{
	this->shadowTag = 0;
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

void WallNutLayer::initWallNutSprite(Vec2 touch)
{
	//创建一个静态的精灵，未被种下时
	Sprite* _wallNutStatic = Sprite::create("res/WallNutStatic.png");
	Sprite* _wallNutStaticShadow = Sprite::create("res/WallNutStatic.png");
	_wallNutStaticShadow->setOpacity(150);
	_wallNutStatic->setPosition(touch);
	this->addChild(_wallNutStaticShadow);
	this->addChild(_wallNutStatic);

	auto lis = EventListenerMouse::create();
	//鼠标移动，则精灵跟着移动
	lis->onMouseMove = [=](EventMouse* e) {
		_wallNutStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y);
		_wallNutStaticShadow->setPosition(x, y);
		return true;
	};
	//当鼠标按键抬起时，精灵被种下，同时取消鼠标监听
	lis->onMouseDown = [=](EventMouse* e) {
		this->removeChild(_wallNutStatic);
		this->removeChild(_wallNutStaticShadow);
		Sprite* shadow = Sprite::create("res/plantshadow.png");
		this->addChild(shadow);
		shadow->setTag(++(this->shadowTag));
		//判断种坚果墙位置是否合法
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if (((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y))
		{
			//精灵被种下，创建动图精灵
			this->_wallNutSprite = WallNutSprite::create();
			this->addChild(_wallNutSprite);
			this->_wallNutSprite->_wallNutSpriteTag = this->shadowTag;
			this->_wallNutVector.pushBack(this->_wallNutSprite);//将精灵添加到数组中
			_plantVectorGlobalVariable.pushBack(this->_wallNutSprite);
			this->_wallNutSprite->startGrowPlantMusic();
			//this->_peaShooterTime.push_back(0);//刚被种下，时间置为0

			//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
			this->_wallNutSprite->setPosition(x, y);
			//在此处发送
			if (isSinglePlayerGameMode == false)
			{
				std::string message = "WallNut:" + to_string(x) + "," + to_string(y) + ";\n";
				TCPSocket::getInstance()->writeIntoServer(message);
			}
			shadow->setPosition(x, y - 30);
			this->_wallNutSprite->_position[0] = (x - 200) / 90;
			this->_wallNutSprite->_position[1] = y / 100;
			((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar -= 50;//每产生一个坚果墙消耗50金币
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

void WallNutLayer::produceWallNutSprite(Vec2 position)
{
	int x = position.x;
	int y = position.y;
	Sprite* shadow = Sprite::create("res/plantshadow.png");
	this->addChild(shadow);
	shadow->setTag(++(this->shadowTag));
	this->_wallNutSprite = WallNutSprite::create();
	this->addChild(_wallNutSprite);
	this->_wallNutSprite->_wallNutSpriteTag = this->shadowTag;
	this->_wallNutVector.pushBack(this->_wallNutSprite);//将精灵添加到数组中
	_plantVectorGlobalVariable.pushBack(this->_wallNutSprite);
	this->_wallNutSprite->startGrowPlantMusic();
	//this->_peaShooterTime.push_back(0);//刚被种下，时间置为0

	//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
	((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
	this->_wallNutSprite->setPosition(x, y);
	shadow->setPosition(x, y - 30);
	this->_wallNutSprite->_position[0] = (x - 200) / 90;
	this->_wallNutSprite->_position[1] = y / 100;
	((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar -= 50;//每产生一个坚果墙消耗50金币

}

void WallNutLayer::diedWallNut()
{
	for (auto i = _wallNutVector.begin(); i != _wallNutVector.end();)
	{
		if ((*i)->_plantHP <= 600 && (*i)->_plantHP >= 594)
		{
			(*i)->stopAllActions();
			(*i)->runAction(RepeatForever::create((*i)->wallNutCracked1()));
		}
		if ((*i)->_plantHP <= 300 && (*i)->_plantHP >= 294)
		{
			(*i)->stopAllActions();
			(*i)->runAction(RepeatForever::create((*i)->wallNutCracked2()));
		}
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

			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(*i)->_position[0]][(*i)->_position[1]] = false;
			this->removeChildByTag((*i)->_wallNutSpriteTag);
			(*i)->removeFromParent();
			
			i = _wallNutVector.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void WallNutLayer::update(float dt)
{
	this->diedWallNut();
}
