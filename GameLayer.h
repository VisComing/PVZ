#pragma once
#include "cocos2d.h"
#include "MapLayer.h"
#include "DollarDisplayLayer.h"
#include "SunCellLayer.h"
#include "NormalZombieLayer.h"
#include "CardLayer.h"
#include "ZombieCardLayer.h"
#include "TouchLayer.h"
#include "PeaShooterLayer.h"
#include "BulletLayer.h"
#include "BoundingLayer.h"
#include "PotatoMineLayer.h"
#include "WallNutLayer.h"
#include "ChomperLayer.h"
USING_NS_CC;
class GameLayer : public Layer
{
public:
	CREATE_FUNC(GameLayer);

	virtual bool init();
	void initMapLayer();//��ʼ����ͼ
	GameLayer();
	~GameLayer();
	void initDollarDisplayerLayer();
	virtual void update(float dt);//�������б仯������,ÿһ֡����ִ�иú���
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

	BoundingLayer* _boundingLayer;
	void initBoundingLayer();

	PotatoMineLayer* _potatoMineLayer;
	void initPotatoMineLayer();

	WallNutLayer* _wallNutLayer;
	void initWallNutLayer();

	ChomperLayer* _chomperLayer;
	void initChomperLayer();
};