#pragma once
#include "cocos2d.h"
#include "NormalZombieSprite.h"
USING_NS_CC;
class ZombieLayer : public Layer
{
public:
	CREATE_FUNC(ZombieLayer);
	ZombieLayer();
	~ZombieLayer();
	virtual bool init();
	NormalZombieSprite* _normalZombieSprite;
	void initNormalZombieSprite(float);//��ʼ����ʬ
	void normalZombieMoveWay();//������ʬ���˶�·��
	void removeNormalZombie(Node* pSend);//ɾ����ʬ
};