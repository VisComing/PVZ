#include "PotatoMineLayer.h"
#include "GameLayer.h"

PotatoMineLayer::PotatoMineLayer()
{
	this->_potatoMineSprite = NULL;
}

PotatoMineLayer::~PotatoMineLayer()
{
}

bool PotatoMineLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}

void PotatoMineLayer::initPeaShooterSprite(Touch *touch)
{
	//����һ����̬�ľ��飬δ������ʱ
	Sprite* _potatoMineStatic = Sprite::create("res/PotatoMineStatic.png");
	_potatoMineStatic->setPosition(touch->getLocation());
	this->addChild(_potatoMineStatic);

	auto lis = EventListenerMouse::create();
	//����ƶ�����������ƶ�
	lis->onMouseMove = [=](EventMouse* e) {
		_potatoMineStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		return true;
	};

	//����갴��̧��ʱ�����鱻���£�ͬʱȡ��������
	lis->onMouseUp = [=](EventMouse* e) {
		this->removeChild(_potatoMineStatic);

		//�ж�����λ���Ƿ�Ϸ�
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if (((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y))
		{
				//���鱻���£�����һ����������
				this->_potatoMineSprite = PotatoMineSprite::create();
				this->addChild(_potatoMineSprite);

				this->_potatoMineVector.pushBack(this->_potatoMineSprite);//��������ӵ�������

				((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
				this->_potatoMineSprite->setPosition(x, y);//����λ��
				this->_potatoMineSprite->_position[0] = (x - 200) / 90;//�����ֲ���λ��
				this->_potatoMineSprite->_position[1] = y / 100;
				((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
					= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 25;//ÿ����һ��������������80���
				//((GameLayer*)this->getParent())->_bulletLayer->schedule(schedule_selector(BulletLayer::initBulletSprite), 0.1f);
				this->schedule(schedule_selector(PotatoMineLayer::grow),1.0f);
		}
		_eventDispatcher->removeEventListener(lis);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);
}

void PotatoMineLayer::grow(float dlt)
{
	for (auto potatoMine : _potatoMineVector)
	{
		if(potatoMine->_potatoMineTime < potatoMine->_potatoMineGrowTime)
			potatoMine->_potatoMineTime += 1;
		
		if (potatoMine->_potatoMineTime == potatoMine->_potatoMineGrowTime)
		{
			//potatoMine->runAction(potatoMine->_potatoMineGrow);
			potatoMine->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(potatoMine->images, 1.f / 8))));
			potatoMine->_potatoMineTime += 1;//�Ժ�ʱ�佫����ı䣬һֱ����potatoMine->_potatoMineGrowTime + 1��
		}
	}
}