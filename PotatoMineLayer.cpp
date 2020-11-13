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
	//创建一个静态的精灵，未被种下时
	Sprite* _potatoMineStatic = Sprite::create("res/PotatoMineStatic.png");
	_potatoMineStatic->setPosition(touch->getLocation());
	this->addChild(_potatoMineStatic);

	auto lis = EventListenerMouse::create();
	//鼠标移动，则精灵跟着移动
	lis->onMouseMove = [=](EventMouse* e) {
		_potatoMineStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		return true;
	};

	//当鼠标按键抬起时，精灵被种下，同时取消鼠标监听
	lis->onMouseUp = [=](EventMouse* e) {
		this->removeChild(_potatoMineStatic);

		//判断种下位置是否合法
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if (((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y))
		{
				//精灵被种下，创建一个土豆地雷
				this->_potatoMineSprite = PotatoMineSprite::create();
				this->addChild(_potatoMineSprite);

				this->_potatoMineVector.pushBack(this->_potatoMineSprite);//将精灵添加到数组中

				((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
				this->_potatoMineSprite->setPosition(x, y);//设置位置
				this->_potatoMineSprite->_position[0] = (x - 200) / 90;//保存该植物的位置
				this->_potatoMineSprite->_position[1] = y / 100;
				((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
					= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 25;//每产生一个土豆地雷消耗80金币
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
			potatoMine->_potatoMineTime += 1;//以后时间将不会改变，一直保持potatoMine->_potatoMineGrowTime + 1秒
		}
	}
}