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
	//����һ����̬�ľ��飬δ������ʱ
	Sprite* _wallNutStatic = Sprite::create("res/WallNutStatic.png");
	Sprite* _wallNutStaticShadow = Sprite::create("res/WallNutStatic.png");
	_wallNutStaticShadow->setOpacity(150);
	_wallNutStatic->setPosition(touch);
	this->addChild(_wallNutStaticShadow);
	this->addChild(_wallNutStatic);

	auto lis = EventListenerMouse::create();
	//����ƶ�����������ƶ�
	lis->onMouseMove = [=](EventMouse* e) {
		_wallNutStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y);
		_wallNutStaticShadow->setPosition(x, y);
		return true;
	};
	//����갴��̧��ʱ�����鱻���£�ͬʱȡ��������
	lis->onMouseDown = [=](EventMouse* e) {
		this->removeChild(_wallNutStatic);
		this->removeChild(_wallNutStaticShadow);
		Sprite* shadow = Sprite::create("res/plantshadow.png");
		this->addChild(shadow);
		shadow->setTag(++(this->shadowTag));
		//�ж��ּ��ǽλ���Ƿ�Ϸ�
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if (((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y))
		{
			//���鱻���£�������ͼ����
			this->_wallNutSprite = WallNutSprite::create();
			this->addChild(_wallNutSprite);
			this->_wallNutSprite->_wallNutSpriteTag = this->shadowTag;
			this->_wallNutVector.pushBack(this->_wallNutSprite);//��������ӵ�������
			_plantVectorGlobalVariable.pushBack(this->_wallNutSprite);
			this->_wallNutSprite->startGrowPlantMusic();
			//this->_peaShooterTime.push_back(0);//�ձ����£�ʱ����Ϊ0

			//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
			this->_wallNutSprite->setPosition(x, y);
			//�ڴ˴�����
			if (isSinglePlayerGameMode == false)
			{
				std::string message = "WallNut:" + to_string(x) + "," + to_string(y) + ";\n";
				TCPSocket::getInstance()->writeIntoServer(message);
			}
			shadow->setPosition(x, y - 30);
			this->_wallNutSprite->_position[0] = (x - 200) / 90;
			this->_wallNutSprite->_position[1] = y / 100;
			((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar -= 50;//ÿ����һ�����ǽ����50���
		}
		else//λ�ô���
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
	this->_wallNutVector.pushBack(this->_wallNutSprite);//��������ӵ�������
	_plantVectorGlobalVariable.pushBack(this->_wallNutSprite);
	this->_wallNutSprite->startGrowPlantMusic();
	//this->_peaShooterTime.push_back(0);//�ձ����£�ʱ����Ϊ0

	//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
	((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
	this->_wallNutSprite->setPosition(x, y);
	shadow->setPosition(x, y - 30);
	this->_wallNutSprite->_position[0] = (x - 200) / 90;
	this->_wallNutSprite->_position[1] = y / 100;
	((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar -= 50;//ÿ����һ�����ǽ����50���

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
