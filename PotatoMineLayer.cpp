#include "PotatoMineLayer.h"
#include "GameLayer.h"
extern Vector<PlantBaseClass*> _plantVector;
extern Vector<ZombieBaseClass*> _zombieVector;
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
	scheduleUpdate();
	return true;
}

void PotatoMineLayer::initPotatoMineSprite(Touch *touch)
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
				_plantVector.pushBack(this->_potatoMineSprite);

				((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
				this->_potatoMineSprite->setPosition(x, y);//����λ��
				this->_potatoMineSprite->_position[0] = (x - 200) / 90;//�����ֲ���λ��
				this->_potatoMineSprite->_position[1] = y / 100;
				((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
					= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 25;//ÿ����һ��������������25���
				//((GameLayer*)this->getParent())->_bulletLayer->schedule(schedule_selector(BulletLayer::initBulletSprite), 0.1f);
				this->schedule(schedule_selector(PotatoMineLayer::grow),1.0f);
				//this->_potatoMineSprite->runAction(Sequence::create(DelayTime::create(this->_potatoMineSprite->_potatoMineGrowTime),
					//RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(this->_potatoMineSprite->images, 1.f / 8))), nullptr));
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

void PotatoMineLayer::potatoMineAttackZombie()
{
	for (auto i = this->_potatoMineVector.begin(); i != this->_potatoMineVector.end();)
	{
		bool _iFlag = false;
		if ((*i)->_plantHP > 0)
		{
			
			if ((*i)->_potatoMineTime == (*i)->_potatoMineGrowTime + 1)
			{
				for (auto j = _zombieVector.begin(); j != _zombieVector.end();)
				{
					if ((*i)->getBoundingBox().intersectsRect((*j)->zombieBounding()))
					{
						_iFlag = true;
						(*i)->removeFromParent();//����������ɾ��
						((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(*i)->_position[0]][(*i)->_position[1]] = false;
						
						//����ֲ���vector��ҲҪɾ��
						for (auto x = _plantVector.begin(); x != _plantVector.end(); x++)
						{
							if ((*i) == (*x))
							{
								_plantVector.erase(x);
								break;
							}
						}
						(*j)->_hp -= 150;//��ʬ��Ѫ
						(*j)->typeOfDeath = 1;
						i = _potatoMineVector.erase(i);//ɾ����������
						break;
					}
					j++;

				}
			}
			
		}
		if (_iFlag == false)
			i++;
	}
}

//ɾȥ����ʬҧ������������
void PotatoMineLayer::diedPotatoMine()
{
	for (auto i = _potatoMineVector.begin(); i != _potatoMineVector.end();)
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
			
			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(*i)->_position[0]][(*i)->_position[1]] = false;
			(*i)->removeFromParent();
			i = _potatoMineVector.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void PotatoMineLayer::update(float dt)
{
	this->potatoMineAttackZombie();
	this->diedPotatoMine();
}
