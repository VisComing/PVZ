#include "NormalZombieLayer.h"
#include "GameLayer.h"
extern Vector<ZombieBaseClass*>_zombieVector;
NormalZombieLayer::NormalZombieLayer()
{
	_normalZombieSprite = NULL;
}
NormalZombieLayer::~NormalZombieLayer()
{

}

bool NormalZombieLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	return true;
}


void NormalZombieLayer::initNormalZombieSprite(Touch* touch)
{
	//创建一个静态僵尸，为被种下时
	Sprite* _normalZombieStatic = Sprite::create("res/ZombieStatic.png");
	_normalZombieStatic->setPosition(touch->getLocation());
	this->addChild(_normalZombieStatic);

	
	auto lis = EventListenerMouse::create();
	//鼠标移动，则精灵跟着移动
	lis->onMouseMove = [=](EventMouse* e) {
		_normalZombieStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		return true;
	};
	//当鼠标按键抬起时，精灵被种下，同时取消鼠标监听
	lis->onMouseUp = [=](EventMouse* e) {
		this->removeChild(_normalZombieStatic);

		//判断中僵尸位置是否合法
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if ((x > 995 && x < 1100) && (y < 510 && y > 30))
		{
			x = 1045;
			if (y > 30 && y < 129)
				y = 80;
			else if (y < 219)
				y = 175;
			else if (y < 320)
				y = 274;
			else if (y < 419)
				y = 375;
			else if (y < 510)
				y = 475;
			//僵尸被种下，创建动图
			this->_normalZombieSprite = NormalZombieSprite::create();
			this->_normalZombieSprite->setPosition(touch->getLocation());
			this->addChild(_normalZombieSprite);

			this->_normalZombieVector.pushBack(this->_normalZombieSprite);//将僵尸添加到数组中
			_zombieVector.pushBack(this->_normalZombieSprite);

			this->_normalZombieSprite->setPosition(x, y + 20);
			((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
				= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 100;//每产生一个僵尸消耗100金币
			this->normalZombieMoveWay();
		}
		else
		{
			//this->removeChild(_normalZombieSprite);
		}
		_eventDispatcher->removeEventListener(lis);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);
}

void NormalZombieLayer::normalZombieMoveWay()//在此修改僵尸移速
{
	Action* normalZombieMove = MoveTo::create(this->_normalZombieSprite->getPositionX() / 40, Vec2(0, this->_normalZombieSprite->getPositionY()));
	this->_normalZombieSprite->runAction(normalZombieMove);
}

FiniteTimeAction* NormalZombieLayer::noHeadNormalZombieMoveWay()
{
	FiniteTimeAction* normalZombieMove = MoveTo::create(15, Vec2(0, this->_normalZombieSprite->getPositionY()));
	//this->_normalZombieSprite->runAction(normalZombieMove);
	return normalZombieMove;
}