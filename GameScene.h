#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameScene : public Scene
{
public:
	CREATE_FUNC(GameScene);
	static cocos2d::Scene* createScene();
	PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world) { m_world = world; };
	virtual bool init();
	void initGameLayer();

};
