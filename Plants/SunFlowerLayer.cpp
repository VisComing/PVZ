#include "SunFlowerLayer.h"
#include "../Base/GameLayer.h"
#include "../Base/MapLayer.h"
#include "../Base/socket.h"
#include "../Base/global.h"
SunFlowerLayer::SunFlowerLayer()
{
	this->shadowTag = 0;
	this->_sunFlowerSprite = NULL;
}

SunFlowerLayer::~SunFlowerLayer()
{
}

bool SunFlowerLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	scheduleUpdate();
	if (_iAmPlantSideGolbalVariable == true || isSinglePlayerGameMode == true)
	{
		schedule(schedule_selector(SunFlowerLayer::produceSunCellSprite), 1);
	}
	return true;
}

void SunFlowerLayer::initSunFlowerSprite(Vec2 touch)
{
	//����һ����̬�ľ��飬δ������ʱ
	Sprite* _sunFlowerStatic = Sprite::create("res/SunFlowerStatic.png");
	Sprite* _sunFlowerStaticShadow = Sprite::create("res/SunFlowerStatic.png");
	_sunFlowerStaticShadow->setOpacity(150);
	_sunFlowerStatic->setPosition(touch);
	this->addChild(_sunFlowerStaticShadow);
	this->addChild(_sunFlowerStatic);

	auto lis = EventListenerMouse::create();
	//����ƶ�����������ƶ�
	lis->onMouseMove = [=](EventMouse* e) {
		_sunFlowerStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y);
		_sunFlowerStaticShadow->setPosition(x, y);
		return true;
	};
	//����갴��̧��ʱ�����鱻���£�ͬʱȡ��������
	lis->onMouseDown = [=](EventMouse* e) {
		this->removeChild(_sunFlowerStatic);
		this->removeChild(_sunFlowerStaticShadow);
		Sprite* shadow = Sprite::create("res/plantshadow.png");
		this->addChild(shadow);
		shadow->setTag(++(this->shadowTag));
		//�ж��ּ��ǽλ���Ƿ�Ϸ�
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if (((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y))
		{
			//���鱻���£�������ͼ����
			this->_sunFlowerSprite = SunFlowerSprite::create();
			this->addChild(_sunFlowerSprite);
			this->_sunFlowerSprite->_sunFlowerSpriteTag = this->shadowTag;
			this->_sunFlowerVector.pushBack(this->_sunFlowerSprite);//��������ӵ�������
			_plantVectorGlobalVariable.pushBack(this->_sunFlowerSprite);
			this->_sunFlowerSprite->startGrowPlantMusic();
			//this->_peaShooterTime.push_back(0);//�ձ����£�ʱ����Ϊ0

			//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
			this->_sunFlowerSprite->setPosition(x, y);
			//�ڴ˴�����
			if (isSinglePlayerGameMode == false)
			{
				std::string message = "1SunFlower:" + to_string(x) + "," + to_string(y) + ";\n";
				TCPSocket::getInstance()->writeIntoServer(message);
			}
			shadow->setPosition(x, y - 30);
			this->_sunFlowerSprite->_position[0] = (x - 200) / 90;
			this->_sunFlowerSprite->_position[1] = y / 100;
			((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar -= 50;//ÿ����һ��̫��������50���
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

void SunFlowerLayer::produceSunFlowerSprite(Vec2 position)
{
	int x = position.x;
	int y = position.y;
	Sprite* shadow = Sprite::create("res/plantshadow.png");
	this->addChild(shadow);
	shadow->setTag(++(this->shadowTag));
	this->_sunFlowerSprite = SunFlowerSprite::create();
	this->addChild(_sunFlowerSprite);
	this->_sunFlowerSprite->_sunFlowerSpriteTag = this->shadowTag;
	this->_sunFlowerVector.pushBack(this->_sunFlowerSprite);//��������ӵ�������
	_plantVectorGlobalVariable.pushBack(this->_sunFlowerSprite);
	this->_sunFlowerSprite->startGrowPlantMusic();
	//this->_peaShooterTime.push_back(0);//�ձ����£�ʱ����Ϊ0

	//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
	((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
	this->_sunFlowerSprite->setPosition(x, y);
	shadow->setPosition(x, y - 30);
	this->_sunFlowerSprite->_position[0] = (x - 200) / 90;
	this->_sunFlowerSprite->_position[1] = y / 100;
	//((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar -=  50;//ÿ����һ��̫��������50���

}

void SunFlowerLayer::diedSunFlower()
{
	for (auto i = _sunFlowerVector.begin(); i != _sunFlowerVector.end();)
	{
		if ((*i)->_plantHP < 0)
		{
			(*i)->stopAllActions();
			for (auto j = _plantVectorGlobalVariable.begin(); j != _plantVectorGlobalVariable.end(); j++)
			{
				if ((*i) == (*j))
				{
					if (isSinglePlayerGameMode == false)
					{
						auto _pos = (*i)->getPosition();
						string message = "1Remove:" + to_string(_pos.x) + "," + to_string(_pos.y) + ";\n";
						TCPSocket::getInstance()->writeIntoServer(message);
					}
					_plantVectorGlobalVariable.erase(j);
					break;
				}
			}

			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(*i)->_position[0]][(*i)->_position[1]] = false;
			this->removeChildByTag((*i)->_sunFlowerSpriteTag);
			(*i)->removeFromParent();
			i = _sunFlowerVector.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void SunFlowerLayer::update(float dt)
{
	this->diedSunFlower();
}

void SunFlowerLayer::produceSunCellSprite(float dlt)
{
	for (auto x : _sunFlowerVector)
	{
		x->_sunCellTime++;
		if (x->_sunCellTime == 20)
		{
			((GameLayer*)this->getParent())->_sunCellLayer->produceSunCell(x->getPosition());
			x->_sunCellTime = 0;
		}
	}
}
