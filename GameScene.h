#pragma once
#include "cocos2d.h"
#include <string>
USING_NS_CC;
extern bool _iAmPlantSideGolbalVariable;
class GameScene : public Scene
{
public:
	CREATE_FUNC(GameScene);
	static cocos2d::Scene* createScene();
	PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world) { m_world = world; };
	virtual bool init();
	void initGameLayer();
	//���Ƿ��������صĽ������ʾ����ֲ�﷽���ǽ�ʬ��
	//�յ����������ص���Ϣʱ������Ҫ��ƥ�䳡��ת������ս����
	//���շ�������Ϣ����ƥ�䳡�����յģ�Ȼ��Ѳ���������ս������_plantOrZombie��
	//ȡֵ   true   false
};
