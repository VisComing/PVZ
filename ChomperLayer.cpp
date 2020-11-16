#include "ChomperLayer.h"
#include "GameLayer.h"
#include "MapLayer.h"
extern Vector<PlantBaseClass*> _plantVector;
extern Vector<ZombieBaseClass*> _zombieVector;

ChomperLayer::ChomperLayer()
{
	this->_chomperSprite = NULL;
}

ChomperLayer::~ChomperLayer()
{
}

bool ChomperLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	scheduleUpdate();
	return true;
}

void ChomperLayer::initChomperSprite(Touch * touch)
{
	//����һ����̬�ľ��飬δ������ʱ
	Sprite* _chomperStatic = Sprite::create("res/ChomperStatic.png");
	_chomperStatic->setPosition(touch->getLocation());
	this->addChild(_chomperStatic);

	auto lis = EventListenerMouse::create();
	//����ƶ�����������ƶ�
	lis->onMouseMove = [=](EventMouse* e) {
		_chomperStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		return true;
	};
	//����갴��̧��ʱ�����鱻���£�ͬʱȡ��������
	lis->onMouseUp = [=](EventMouse* e) {
		this->removeChild(_chomperStatic);

		//�ж��ּ��ǽλ���Ƿ�Ϸ�
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if (((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y))
		{
			//���鱻���£�������ͼ����
			this->_chomperSprite = ChomperSprite::create();
			this->addChild(_chomperSprite);

			this->_chomperVector.pushBack(this->_chomperSprite);//��������ӵ�������
			_plantVector.pushBack(this->_chomperSprite);

			//this->_peaShooterTime.push_back(0);//�ձ����£�ʱ����Ϊ0

			//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
			this->_chomperSprite->setPosition(x + 10, y + 20);
			this->_chomperSprite->_position[0] = (x - 200) / 90;
			this->_chomperSprite->_position[1] = y / 100;
			((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
				= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 150;//ÿ����һ��ʳ�˻�����150���
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



void ChomperLayer::chomperAttackZombie()
{
	for (auto i = this->_chomperVector.begin(); i != this->_chomperVector.end(); i++)
	{
		if ((*i)->_eatingZombie == true)
		{
			(*i)->_ateTime++;
			if ((*i)->_ateTime == (*i)->_ateDownTime)//��������
			{
				(*i)->_eatingZombie = false;
				(*i)->_ateTime = 0;
				(*i)->stopAllActions();
				(*i)->runAction((*i)->chomperNormal());
			}
		}
		for (auto j = _zombieVector.begin(); j != _zombieVector.end(); j++)
		{
			if ((*i)->_eatingZombie == false)
			{
				if ((*j)->zombieBounding().intersectsRect((*i)->plantBounding()))
				{
					//ֲ�ﶯ���仯
					(*i)->stopAllActions();
					(*i)->runAction((*i)->chomperDigest());
					auto tmp = *j;
					auto a = j;
					//(*j)->_hp -= 200;
					/*(*i)->runAction(Sequence::create((*i)
						->chomperAttack(), CallFunc::create(CC_CALLBACK_0(Sprite::removeFromParent, tmp)),
						(*i)->chomperDigest(),
						NULL));*/
					(*i)->runAction(Sequence::create((*i)
						->chomperAttack(), CallFunc::create([tmp]() {
							tmp->_hp -= 200;
							tmp->removeFromParent();
							
							//_zombieVector.erase(a);
							}),
						(*i)->chomperDigest(),
						NULL));
					//�ѽ�ʬ���ˣ���ʬ��ʧ
					//(*j)->removeFromParent();
					//_zombieVector.erase(j);
					(*i)->_eatingZombie = true;

					break;
				}
				
			}
		}
	}
}
void ChomperLayer::diedChomper()
{
	for (auto i = _chomperVector.begin(); i != _chomperVector.end();)
	{
		log("chomper hp %d", (*i)->_plantHP);
		if ((*i)->_plantHP < 0)
		{
			(*i)->stopAllActions();
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
			i = _chomperVector.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void ChomperLayer::update(float dt)
{
	this->chomperAttackZombie();
	this->diedChomper();
}
