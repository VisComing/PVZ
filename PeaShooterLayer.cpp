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
	//����һ����̬�ľ��飬δ������ʱ
	Sprite* _peaShooterStatic = Sprite::create("res/PeashooterStatic.png");
	_peaShooterStatic->setPosition(touch->getLocation());
	this->addChild(_peaShooterStatic);

	auto lis = EventListenerMouse::create();
	//����ƶ�����������ƶ�
	lis->onMouseMove = [=](EventMouse* e) {
		_peaShooterStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		return true;
	};
	//����갴��̧��ʱ�����鱻���£�ͬʱȡ��������
	lis->onMouseUp = [=](EventMouse* e) {
		this->removeChild(_peaShooterStatic);

		//�ж����㶹����λ���Ƿ�Ϸ�
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if (((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x,y))
		{
				//���鱻���£�������ͼ����
				this->_peaShooterSprite = PeaShooterSprite::create();
				this->addChild(_peaShooterSprite);

				this->_peaShooterVector.pushBack(this->_peaShooterSprite);//��������ӵ�������
				_plantVector.pushBack(this->_peaShooterSprite);
				
				this->_peaShooterTime.push_back(0);//�ձ����£�ʱ����Ϊ0

				//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
				((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
				this->_peaShooterSprite->setPosition(x, y);
				this->_peaShooterSprite->_position[0] = (x - 200) / 90;
				this->_peaShooterSprite->_position[1] = y / 100;
				((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
					= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 100;//ÿ����һ��ֲ��ǹ����100���
				((GameLayer*)this->getParent())->_bulletLayer->schedule(schedule_selector(BulletLayer::initBulletSprite), 0.1f);
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
