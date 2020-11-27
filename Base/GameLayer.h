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
	void initMapLayer();//��ʼ����ͼ
	GameLayer();
	~GameLayer();
	void initDollarDisplayerLayer();
	//virtual void update(float dt);//�������б仯������,ÿһ֡����ִ�иú���
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

	int getDistanceFromPlantToZombie(int row);//�����һ�ţ�ֲ��ͽ�ʬ�ľ��룬��ǰ��û�н�ʬ�������Ϊ���޴�

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