#pragma once
#include "cocos2d.h"
#include "WallNutSprite.h"
using namespace std;
USING_NS_CC;
class WallNutLayer : public Layer
{
public:
	CREATE_FUNC(WallNutLayer);
	WallNutLayer();
	~WallNutLayer();
	bool init() override;
	WallNutSprite* _wallNutSprite;
	void initWallNutSprite(Vec2);//��ʼ���㶹���֣���һ�����������
	void produceWallNutSprite(Vec2);//���ݷ���������������Ϣֱ������ֲ��
	void diedWallNut();
	virtual void update(float dt);
	Vector<WallNutSprite*> _wallNutVector;
	int shadowTag;
};