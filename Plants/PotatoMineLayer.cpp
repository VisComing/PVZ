#include "PotatoMineLayer.h"
#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "socket.h"
#include "global.h"
using namespace CocosDenshion;
extern Vector<PlantBaseClass*> _plantVector;
extern Vector<ZombieBaseClass*> _zombieVector;
PotatoMineLayer::PotatoMineLayer()
{
	this->shadowTag = 20;
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

void PotatoMineLayer::initPotatoMineSprite(Vec2 touch)
{
	//����һ����̬�ľ��飬δ������ʱ
	Sprite* _potatoMineStatic = Sprite::create("res/PotatoMineStatic.png");
	Sprite* _potatoMineStaticShadow = Sprite::create("res/PotatoMineStatic.png");
	_potatoMineStaticShadow->setOpacity(150);
	_potatoMineStatic->setPosition(touch);
	this->addChild(_potatoMineStaticShadow);
	this->addChild(_potatoMineStatic);

	auto lis = EventListenerMouse::create();
	//����ƶ�����������ƶ�
	lis->onMouseMove = [=](EventMouse* e) {
		_potatoMineStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y);
		_potatoMineStaticShadow->setPosition(x, y);
		return true;
	};

	//����갴��̧��ʱ�����鱻���£�ͬʱȡ��������
	lis->onMouseDown = [=](EventMouse* e) {
		this->removeChild(_potatoMineStatic);
		this->removeChild(_potatoMineStaticShadow);
		Sprite* shadow = Sprite::create("res/plantshadow.png");
		this->addChild(shadow);
		shadow->setTag(++(this->shadowTag));
		//�ж�����λ���Ƿ�Ϸ�
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if (((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y))
		{
				//���鱻���£�����һ����������
				this->_potatoMineSprite = PotatoMineSprite::create();
				this->addChild(_potatoMineSprite);
				this->_potatoMineSprite->_potatoMineSpriteTag = this->shadowTag;
				this->_potatoMineVector.pushBack(this->_potatoMineSprite);//���������ӵ�������
				_plantVector.pushBack(this->_potatoMineSprite);
				this->_potatoMineSprite->startGrowPlantMusic();
				((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
				this->_potatoMineSprite->setPosition(x, y);//����λ��
				//�ڴ˴�����
				if (isSinglePlayerGameMode == false)
				{
					std::string message = "PotatoMine:" + to_string(x) + "," + to_string(y) + ";\n";
					TCPSocket::getInstance()->writeIntoServer(message);
				}
				shadow->setPosition(x, y - 20);
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

void PotatoMineLayer::producePotatoMineSprite(Vec2 position)
{
	int x = position.x;
	int y = position.y;
	Sprite* shadow = Sprite::create("res/plantshadow.png");
	this->addChild(shadow);
	shadow->setTag(++(this->shadowTag));
	//���鱻���£�����һ����������
	this->_potatoMineSprite = PotatoMineSprite::create();
	this->addChild(_potatoMineSprite);
	this->_potatoMineSprite->_potatoMineSpriteTag = this->shadowTag;
	this->_potatoMineVector.pushBack(this->_potatoMineSprite);//���������ӵ�������
	_plantVector.pushBack(this->_potatoMineSprite);
	this->_potatoMineSprite->startGrowPlantMusic();
	((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
	this->_potatoMineSprite->setPosition(x, y);//����λ��
	shadow->setPosition(x, y - 20);
	this->_potatoMineSprite->_position[0] = (x - 200) / 90;//�����ֲ���λ��
	this->_potatoMineSprite->_position[1] = y / 100;
	((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
		= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 25;//ÿ����һ��������������25���
	this->schedule(schedule_selector(PotatoMineLayer::grow), 1.0f);
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
					if ((*i)->plantBounding().intersectsRect((*j)->zombieBounding()))
					{
						SimpleAudioEngine::getInstance()->playEffect("res/music/potatoMine.wma");
						_iFlag = true;
						(*i)->_plantHP -= 500;
						//(*i)->removeFromParent();//����������ɾ��
						((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(*i)->_position[0]][(*i)->_position[1]] = false;
						
						//����ֲ���vector��ҲҪɾ��
						/*for (auto x = _plantVector.begin(); x != _plantVector.end(); x++)
						{
							if ((*i) == (*x))
							{
								_plantVector.erase(x);
								break;
							}
						}*/
						(*j)->_hp -= 500;//��ʬ��Ѫ
						(*j)->typeOfDeath = 1;
						//i = _potatoMineVector.erase(i);//ɾ����������
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
			this->removeChildByTag((*i)->_potatoMineSpriteTag);
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