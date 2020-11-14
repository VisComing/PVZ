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
	scheduleUpdate();
	return true;
}


void NormalZombieLayer::initNormalZombieSprite(Touch* touch)
{
	//����һ����̬��ʬ��Ϊ������ʱ
	Sprite* _normalZombieStatic = Sprite::create("res/ZombieStatic.png");
	_normalZombieStatic->setPosition(touch->getLocation());
	this->addChild(_normalZombieStatic);

	
	auto lis = EventListenerMouse::create();
	//����ƶ�����������ƶ�
	lis->onMouseMove = [=](EventMouse* e) {
		_normalZombieStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		return true;
	};
	//����갴��̧��ʱ�����鱻���£�ͬʱȡ��������
	lis->onMouseUp = [=](EventMouse* e) {
		this->removeChild(_normalZombieStatic);

		//�ж��н�ʬλ���Ƿ�Ϸ�
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
			//��ʬ�����£�������ͼ
			this->_normalZombieSprite = NormalZombieSprite::create();
			this->_normalZombieSprite->setPosition(touch->getLocation());
			this->addChild(_normalZombieSprite);

			this->_normalZombieVector.pushBack(this->_normalZombieSprite);//����ʬ��ӵ�������
			_zombieVector.pushBack(this->_normalZombieSprite);

			this->_normalZombieSprite->setPosition(x, y + 20);
			((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
				= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 100;//ÿ����һ����ʬ����100���
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

void NormalZombieLayer::normalZombieMoveWay()//�ڴ��޸Ľ�ʬ����
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

void NormalZombieLayer::diedNormalZombie()
{
	for (auto i = _normalZombieVector.begin(); i != _normalZombieVector.end();)
	{
		if ((*i)->_hp <= 0)
		{
			//��ȫ����ʬ�����н���ɾ��
			for (auto j = _zombieVector.begin(); j != _zombieVector.end();)
			{
				if ((*i) == (*j))
				{
					_zombieVector.erase(j);
					break;
				}
			}
			(*i)->stopAllActions();
			auto tmp = *i;
			//ԭ�������е����⣬��ִ�ж�����Ȼ��ִ��lamida���ʽ��ִ�е�lamidaʱ�����i�Ѿ���ɾ����
			//2020/11/15�賿
			(*i)->runAction(Sequence::createWithTwoActions(this->_normalZombieSprite
				->downTheGround(), CallFunc::create([tmp]() {
					(tmp)->removeFromParent();//����ʬɾ��
				})));
			//ע�⣬��һ��Ҫ���ڸ�ѭ�������в����������֮ǰɾ���ˣ���ô��������Ҫʹ��������ô����
			i = _normalZombieVector.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void NormalZombieLayer::update(float dt)
{
	this->diedNormalZombie();
}
