#pragma once
#include "cocos2d.h"
#include "MapLayer.h"
#include "../Plants/DollarDisplayLayer.h"
#include "../Plants/SunCellLayer.h"
#include "../Zombies/NormalZombieLayer.h"
#include "../Plants/CardLayer.h"
#include "../Zombies/ZombieCardLayer.h"
#include "TouchLayer.h"
#include "../Plants/PeaShooterLayer.h"
#include "../Plants/BulletLayer.h"
//#include "BoundingLayer.h"
#include "../Plants/PotatoMineLayer.h"
#include "../Plants/WallNutLayer.h"
#include "../Plants/ChomperLayer.h"
#include "GameController.h"
#include "ShowSloganLayer.h"
#include "MusicLayer.h"
#include "../Plants/SunFlowerLayer.h"
USING_NS_CC;
class GameLayer : public Layer
{
public:
	CREATE_FUNC(GameLayer);

	bool init() override;
	void initMapLayer();//初始化地图
	GameLayer();
	~GameLayer();
	void initDollarDisplayerLayer();
	//virtual void update(float dt);//监听所有变化的事物,每一帧都会执行该函数
	SunCellLayer* _sunCellLayer;
	void initSunCellLayer();
	Sprite* _bgSprite;
	SpriteFrameCache* _cache;
	MapLayer* _mapLayer;
	DollarDisplayLayer* _dollarDisplayLayer;
	NormalZombieLayer* _normalZombieLayer;
	void initNormalZombieLayer();
	CardLayer* _cardLayer;
	void initCardLayer();
	ZombieCardLayer* _zombieCardLayer;
	void initZombieCardLayer();
	TouchLayer* _touchLayer;
	void initTouchLayer();
	//PeaShooterLayer* _peaShooterLayer;
	void initPeaShooterLayer();
	PeaShooterLayer* _peaShooterLayer;

	int getDistanceFromPlantToZombie(int row);//获得这一排，植物和僵尸的距离，若前面没有僵尸，则距离为无限大

	BulletLayer* _bulletLayer;
	void initBulletLayer();

	//BoundingLayer* _boundingLayer;
	//void initBoundingLayer();

	PotatoMineLayer* _potatoMineLayer;
	void initPotatoMineLayer();

	WallNutLayer* _wallNutLayer;
	void initWallNutLayer();

	ChomperLayer* _chomperLayer;
	void initChomperLayer();

	GameController* _gameController;
	void initGameController();

	ShowSloganLayer* _showSloganLayer;
	void initShowSloganLayer();

	MusicLayer* _musicLayer;
	void initMusicLayer();

	SunFlowerLayer* _sunFlowerLayer;
	void initSunFlowerLayer();
};