#pragma once
#include "cocos2d.h"
#include "PeaShooterSprite.h"
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

};
