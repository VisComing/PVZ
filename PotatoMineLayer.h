#pragma once
#include "cocos2d.h"
#include "PotatoMineSprite.h"
#include <vector>
using namespace std;
USING_NS_CC;
class PotatoMineLayer : public Layer
{
public:
	CREATE_FUNC(PotatoMineLayer);
	PotatoMineLayer();
	~PotatoMineLayer();
	virtual bool init();
	PotatoMineSprite* _potatoMineSprite;
	void initPeaShooterSprite(Touch*);//��ʼ���������ף���һ�����������
	void grow(float);
	Vector<PotatoMineSprite*> _potatoMineVector;

	//vector<int> _potatoMineTime;//�õ����Ѿ������µ�ʱ�䣬ÿ��0.1���һ
};