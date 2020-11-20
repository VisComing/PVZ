#include "GameLayer.h"
#include "global.h"
bool GameLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->initMapLayer();
	
	

	//scheduleUpdate();//监听一切活动/变化
	this->initCardLayer();
	if (isSinglePlayerGameMode == false)
	{
		this->initZombieCardLayer();
	}
	this->initTouchLayer();
	
	this->initDollarDisplayerLayer();//初始化金币展示板
	
	this->initPotatoMineLayer();//土豆地雷层
	
	//this->initBoundingLayer();
	this->initWallNutLayer();//坚果墙
	this->initChomperLayer();
	
	this->initBulletLayer();//子弹层  在最上面一层
	this->initNormalZombieLayer();
	this->initPeaShooterLayer();
	this->initSunCellLayer();//阳光下落
	if (isSinglePlayerGameMode == true)
	{
		this->initGameController();
		this->initShowSloganLayer();
	}

	this->initMusicLayer();
	return true;
}

GameLayer::GameLayer()
{
	this->_sunCellLayer = NULL;
	this->_normalZombieLayer = NULL;
	this->_cardLayer = NULL;
	this->_touchLayer = NULL;
	this->_peaShooterLayer = NULL;
	//this->_boundingLayer = NULL;
}

GameLayer::~GameLayer()
{

}

void GameLayer::initMapLayer()
{
	this->_mapLayer = MapLayer::create();
	this->addChild(this->_mapLayer);
}

//定义金币展示层函数
void GameLayer::initDollarDisplayerLayer()
{
	this->_dollarDisplayLayer = DollarDisplayLayer::create();
	this->addChild(this->_dollarDisplayLayer);
}
//在每一个层中执行update？
//void GameLayer::update(float dlt)//每一帧都会执行一次
//{
//	//监听金币变化
//	this->_dollarDisplayLayer->_dollarStr = StringUtils::format("%d", this->_dollarDisplayLayer->_dollar);
//	this->_dollarDisplayLayer->_dollarLabel->setString(this->_dollarDisplayLayer->_dollarStr);
//
//	//this->_boundingLayer->bulletBoundingZombie();//子弹碰撞僵尸，对僵尸造成伤害
//	//this->_boundingLayer->zombieEatPlant();//僵尸吃植物
//}

//初始化太阳因子层
void GameLayer::initSunCellLayer()
{
	this->_sunCellLayer = SunCellLayer::create();
	this->addChild(this->_sunCellLayer);
}

void GameLayer::initNormalZombieLayer()
{
	this->_normalZombieLayer = NormalZombieLayer::create();
	this->addChild(this->_normalZombieLayer);
}

void GameLayer::initCardLayer()
{
	this->_cardLayer = CardLayer::create();
	this->addChild(this->_cardLayer);
}
void GameLayer::initZombieCardLayer()
{
	this->_zombieCardLayer = ZombieCardLayer::create();
	this->addChild(this->_zombieCardLayer);
}
void GameLayer::initTouchLayer()
{
	this->_touchLayer = TouchLayer::create();
	this->addChild(_touchLayer);
}

void GameLayer::initPeaShooterLayer()
{
	this->_peaShooterLayer = PeaShooterLayer::create();
	this->addChild(this->_peaShooterLayer);
}

int GameLayer::getDistanceFromPlantToZombie(int row)//row为植物在第几行
{
	int yPos = this->_normalZombieLayer->_normalZombieSprite->getPosition().y;
	if (yPos / 100 == row)//植物前面有僵尸
	{
		//this->_zombieLayer->_normalZombieSprite->getBoundingBox().getMaxX;
	}
	return 0;
}

void GameLayer::initBulletLayer()
{
	this->_bulletLayer = BulletLayer::create();
	this->addChild(this->_bulletLayer);
}

//void GameLayer::initBoundingLayer()
//{
//	this->_boundingLayer = BoundingLayer::create();
//	this->addChild(this->_boundingLayer);
//}

void GameLayer::initPotatoMineLayer()
{
	this->_potatoMineLayer = PotatoMineLayer::create();
	this->addChild(this->_potatoMineLayer);
}

void GameLayer::initWallNutLayer()
{
	this->_wallNutLayer = WallNutLayer::create();
	this->addChild(this->_wallNutLayer);
}

void GameLayer::initChomperLayer()
{
	this->_chomperLayer = ChomperLayer::create();
	this->addChild(this->_chomperLayer);
}

void GameLayer::initGameController()
{
	_gameController = GameController::create();
	this->addChild(this->_gameController);
}

void GameLayer::initShowSloganLayer()
{
	_showSloganLayer = ShowSloganLayer::create();
	this->addChild(this->_showSloganLayer);
}

void GameLayer::initMusicLayer()
{
	_musicLayer = MusicLayer::create();
	this->addChild(_musicLayer);
}

