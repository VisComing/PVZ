#include "PlantBaseClass.h"
#include "PeaShooterLayer.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
PlantBaseClass::PlantBaseClass()
{
	_peaShooterCache = SpriteFrameCache::getInstance();
	_peaShooterCache->addSpriteFramesWithFile("res/peashooter.plist");
	_potatoMineCache = SpriteFrameCache::getInstance();
	_potatoMineCache->addSpriteFramesWithFile("res/potatomine.plist");
	_wallNutCache = SpriteFrameCache::getInstance();
	_wallNutCache->addSpriteFramesWithFile("res/wallnut.plist");
	_chomperCache = SpriteFrameCache::getInstance();
	_chomperCache->addSpriteFramesWithFile("res/chomper.plist");
	_sunFlowerCache = SpriteFrameCache::getInstance();
	_sunFlowerCache->addSpriteFramesWithFile("res/sunflower.plist");
	under_attack = false;
}

PlantBaseClass::~PlantBaseClass()
{
}

bool PlantBaseClass::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}

Rect PlantBaseClass::plantBounding()
{
	return this->getBoundingBox();
}

void PlantBaseClass::startGrowPlantMusic()
{
	int random = rand() % 2;
	if(random == 0)
		SimpleAudioEngine::getInstance()->playEffect("res/music/GrowPlant.wma");
	else 
		SimpleAudioEngine::getInstance()->playEffect("res/music/GrowPlant2.wma");
}

//void PlantBaseClass::plantPlants()
//{
//	//����һ����̬�ľ��飬δ������ʱ
//	Sprite* _peaShooterStatic = Sprite::create("res/PeashooterStatic.png");
//	_peaShooterStatic->setPosition(touch->getLocation());
//	this->addChild(_peaShooterStatic);
//
//	auto lis = EventListenerMouse::create();
//	//����ƶ�����������ƶ�
//	lis->onMouseMove = [=](EventMouse* e) {
//		_peaShooterStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
//		return true;
//	};
//	//����갴��̧��ʱ�����鱻���£�ͬʱȡ��������
//	lis->onMouseUp = [=](EventMouse* e) {
//		this->removeChild(_peaShooterStatic);
//
//		//�ж����㶹����λ���Ƿ�Ϸ�
//		int x = e->getLocation().x;
//		int y = 1200 - e->getLocation().y;
//		if ((x < 1000 && x >236) && (y < 510 && y > 30))
//		{
//			if (x > 236 && x < 333)
//				x = 289;
//			else if (x < 405)
//				x = 372;
//			else if (x < 493)
//				x = 456;
//			else if (x < 574)
//				x = 535;
//			else if (x < 652)
//				x = 619;
//			else if (x < 734)
//				x = 695;
//			else if (x < 815)
//				x = 774;
//			else if (x < 896)
//				x = 857;
//			else if (x < 1000)
//				x = 945;
//			if (y > 30 && y < 129)
//				y = 80;
//			else if (y < 219)
//				y = 175;
//			else if (y < 320)
//				y = 274;
//			else if (y < 419)
//				y = 375;
//			else if (y < 510)
//				y = 475;
//			//��λ���Ѿ��о�����
//			if ((dynamic_cast<GameLayer*>(this->getParent()))->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] == true)
//			{
//				//this->removeChild(_peaShooterSprite);
//			}
//			else
//			{
//
//				//���鱻���£�������ͼ����
//				this->_peaShooterSprite = PeaShooterSprite::create();
//				this->_peaShooterSprite->setPosition(touch->getLocation());
//				this->addChild(_peaShooterSprite);
//
//				this->_peaShooterVector.pushBack(this->_peaShooterSprite);//��������ӵ�������
//				this->_peaShooterTime.push_back(0);//�ձ����£�ʱ����Ϊ0
//
//				(dynamic_cast<GameLayer*>(this->getParent()))->_touchLayer->_isCreatePeaShooter = true;
//				(dynamic_cast<GameLayer*>(this->getParent()))->_mapLayer->_isPlanted[(x - 200) / 90][y / 100] = true;
//				this->_peaShooterSprite->setPosition(x, y);
//				this->_peaShooterSprite->_position[0] = (x - 200) / 90;
//				this->_peaShooterSprite->_position[1] = y / 100;
//				(dynamic_cast<GameLayer*>(this->getParent()))->_dollarDisplayLayer->_dollar
//					= (dynamic_cast<GameLayer*>(this->getParent()))->_dollarDisplayLayer->_dollar - 100;//ÿ����һ��ֲ��ǹ����100���
//				(dynamic_cast<GameLayer*>(this->getParent()))->_bulletLayer->schedule(schedule_selector(BulletLayer::initBulletSprite), 0.1f);
//			}
//		}
//		else//λ�ô���
//		{
//			//(dynamic_cast<GameLayer*>(this->getParent()))->_bulletLayer->unschedule(schedule_selector(BulletLayer::initBulletSprite));
//			//this->removeChild(_peaShooterSprite);
//		}
//		_eventDispatcher->removeEventListener(lis);
//		return true;
//	};
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);
//}
