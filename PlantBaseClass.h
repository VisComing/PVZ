#pragma once
#include "cocos2d.h"
USING_NS_CC;

class PlantBaseClass : public Sprite
{
public:
	CREATE_FUNC(PlantBaseClass);
	PlantBaseClass();
	~PlantBaseClass();
	virtual bool init();
	SpriteFrameCache* _peaShooterCache;
	SpriteFrameCache* _potatoMineCache;
	SpriteFrameCache* _wallNutCache;
	SpriteFrameCache* _chomperCache;
	int _plantHP;//ֲ�������ֵ
	int _position[2];//ֲ���λ��,��һ����ʾ�ڼ��У���9�У����ڶ�����ʾ�ڼ��У���5�У�
	//void plantPlants();//��ֲ��
	bool under_attack;
	virtual Rect plantBounding();
	void startGrowPlantMusic();
};
