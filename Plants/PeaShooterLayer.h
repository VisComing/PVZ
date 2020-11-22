#pragma once
#include "cocos2d.h"
#include "PeaShooterSprite.h"
#include <vector>
using namespace std;
//#include "GameLayer.h"
USING_NS_CC;
class PeaShooterLayer : public Layer
{
public:
	CREATE_FUNC(PeaShooterLayer);
	PeaShooterLayer();
	~PeaShooterLayer();
	virtual bool init();
	PeaShooterSprite* _peaShooterSprite;
	void initPeaShooterSprite(Vec2);//��ʼ���㶹���֣���һ�����������
	void producePeaShooterSprite(Vec2);//���ݷ�������������Ϣֱ������ֲ��
	void diedPeaShooter();
	virtual void update(float dt);
	Vector<PeaShooterSprite*> _peaShooterVector;

	vector<int> _peaShooterTime;//�������Ѿ������µ�ʱ�䣬ÿ��0.1���һ
	int shadowTag;
	void removePlant(Vec2);
};
