#include "ChomperLayer.h"
#include "../Base/GameLayer.h"
#include "../Base/MapLayer.h"
#include "../Base/socket.h"
#include "../Base/global.h"
extern Vector<PlantBaseClass*> _plantVectorGlobalVariable;
extern Vector<ZombieBaseClass*> _zombieVectorGlobalVariable;

ChomperLayer::ChomperLayer()
{
	this->shadowTag = 0;
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

void ChomperLayer::initChomperSprite(Vec2 touch)
{
	//����һ����̬�ľ��飬δ������ʱ
	Sprite* _chomperStatic = Sprite::create("res/ChomperStatic.png");
	Sprite* _chomperStaticShadow = Sprite::create("res/ChomperStatic.png");
	_chomperStatic->setPosition(touch);
	_chomperStaticShadow->setOpacity(150);
	this->addChild(_chomperStaticShadow);
	this->addChild(_chomperStatic);

	auto lis = EventListenerMouse::create();
	//����ƶ�����������ƶ�
	lis->onMouseMove = [=](EventMouse* e) {
		_chomperStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y);
		
		_chomperStaticShadow->setPosition(x, y);
		return true;
	};
	//����갴��̧��ʱ�����鱻���£�ͬʱȡ��������
	lis->onMouseDown = [=](EventMouse* e) {
		this->removeChild(_chomperStatic);
		this->removeChild(_chomperStaticShadow);
		Sprite* shadow = Sprite::create("res/plantshadow.png");
		this->addChild(shadow);
		shadow->setTag(++(this->shadowTag));
		//�ж��ּ��ǽλ���Ƿ�Ϸ�
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if (((GameLayer*)this->getParent())->_mapLayer->isRightPositionForPlants(x, y))
		{

			//���鱻���£�������ͼ����
			this->_chomperSprite = ChomperSprite::create();
			this->addChild(_chomperSprite);
			this->_chomperSprite->_chomperSpriteTag = this->shadowTag;
			this->_chomperVector.pushBack(this->_chomperSprite);//��������ӵ�������
			_plantVectorGlobalVariable.pushBack(this->_chomperSprite);
			this->_chomperSprite->startGrowPlantMusic();
			//this->_peaShooterTime.push_back(0);//�ձ����£�ʱ����Ϊ0

			//((GameLayer*)this->getParent())->_touchLayer->_isCreatePeaShooter = true;
			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
			this->_chomperSprite->setPosition(x + 10, y + 20);
			//�ڴ˴�����
			if (isSinglePlayerGameMode == false)
			{
				std::string message = "1Chomper:" + to_string(x) + "," + to_string(y) + ";\n";
				TCPSocket::getInstance()->writeIntoServer(message);
			}
			shadow->setPosition(x - 20, y - 33);
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

void ChomperLayer::produceChomperSprite(Vec2 position)
{
	int x = position.x;
	int y = position.y;
	Sprite* shadow = Sprite::create("res/plantshadow.png");
	this->addChild(shadow);
	shadow->setTag(++(this->shadowTag));
	//���鱻���£�������ͼ����
	this->_chomperSprite = ChomperSprite::create();
	this->addChild(_chomperSprite);
	this->_chomperSprite->_chomperSpriteTag = this->shadowTag;
	this->_chomperVector.pushBack(this->_chomperSprite);//��������ӵ�������
	_plantVectorGlobalVariable.pushBack(this->_chomperSprite);
	this->_chomperSprite->startGrowPlantMusic();
	((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
	this->_chomperSprite->setPosition(x + 10, y + 20);
	shadow->setPosition(x - 20, y - 33);
	this->_chomperSprite->_position[0] = (x - 200) / 90;
	this->_chomperSprite->_position[1] = y / 100;
	//((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
	//	= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - 150;//ÿ����һ��ʳ�˻�����150���

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
		for (auto j = _zombieVectorGlobalVariable.begin(); j != _zombieVectorGlobalVariable.end(); j++)
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
					(*j)->typeOfDeath = 2;//��������2��ʾ��ʳ�˻��Ե�
					(*i)->runAction(Sequence::create((*i)
						->chomperAttack(), CallFunc::create([tmp]() {
							tmp->_hp -= 500;
							//tmp->removeFromParent();
							//��ֲ��layer�в�Ҫɾ����ʬ����ֻ�۳���ʬѪ��2020/11/19
							//_zombieVectorGlobalVariable.erase(a);
							}),
						(*i)->chomperDigest(),
						NULL));
					//�ѽ�ʬ���ˣ���ʬ��ʧ
					//(*j)->removeFromParent();
					//_zombieVectorGlobalVariable.erase(j);
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
			for (auto j = _plantVectorGlobalVariable.begin(); j != _plantVectorGlobalVariable.end(); j++)
			{
				if ((*i) == (*j))
				{
					_plantVectorGlobalVariable.erase(j);
					break;
				}
			}

			((GameLayer*)this->getParent())->_mapLayer->_isPlanted[(*i)->_position[0]][(*i)->_position[1]] = false;
			this->removeChildByTag((*i)->_chomperSpriteTag);
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
