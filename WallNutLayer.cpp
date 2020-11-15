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
	//����һ����̬�ľ��飬δ������ʱ
	Sprite* _wallNutStatic = Sprite::create("res/WallNutStatic.png");
	_wallNutStatic->setPosition(touch->getLocation());
	this->addChild(_wallNutStatic);

	auto lis = EventListenerMouse::create();
	//����ƶ�����������ƶ�
	lis->onMouseMove = [=](EventMouse* e) {
		_wallNutStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		return true;
	};
	//����갴��̧��ʱ�����鱻���£�ͬʱȡ��������
	lis->onMouseUp = [=](EventMouse* e) {
		this->removeChild(_wallNutStatic);

		//�ж��ּ��ǽλ���Ƿ�Ϸ�
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if (((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y))
		{
			//���鱻���£�������ͼ����
			this->_wallNutSprite = WallNutSprite::create();
			this->addChild(_wallNutSprite);

			this->_wallNutVector.pushBack(this->_wallNutSprite);//��������ӵ�������
			_plantVector.pushBack(this->_wallNutSprite);

			//this->_peaShooterTime.push_back(0);//�ձ����£�ʱ����Ϊ0

			//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
			this->_wallNutSprite->setPosition(x, y);
			this->_wallNutSprite->_position[0] = (x - 200) / 90;
			this->_wallNutSprite->_position[1] = y / 100;
			((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
				= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 50;//ÿ����һ�����ǽ����50���
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

void WallNutLayer::diedWallNut()
{
}

void WallNutLayer::update(float dt)
{
}
