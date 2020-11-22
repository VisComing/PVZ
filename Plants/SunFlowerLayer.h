#pragma once
#include "cocos2d.h"
#include "SunFlowerSprite.h"
using namespace std;
USING_NS_CC;
class SunFlowerLayer : public Layer
{
public:
	CREATE_FUNC(SunFlowerLayer);
	SunFlowerLayer();
	~SunFlowerLayer();
	virtual bool init();
	SunFlowerSprite* _sunFlowerSprite;
	void initSunFlowerSprite(Vec2);//��ʼ���㶹���֣���һ�����������
	void produceSunFlowerSprite(Vec2);//���ݷ�������������Ϣ��ֱ�����¸�ֲ��
	void diedSunFlower();
	virtual void update(float dt);
	Vector<SunFlowerSprite*> _sunFlowerVector;
	int _sunFlowerSpriteTag;
	int shadowTag;
	void produceSunCellSprite(float dlt);
};