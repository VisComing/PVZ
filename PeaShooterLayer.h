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
	void initPeaShooterSprite(Touch*);//��ʼ���㶹���֣�����һ�����������

	Vector<Sprite*> _peaShooterVector;

	vector<int> _peaShooterTime;//�������Ѿ������µ�ʱ�䣬ÿ��0.1���һ
};
