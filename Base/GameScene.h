#pragma once
#include "cocos2d.h"
#include <string>
USING_NS_CC;
class GameScene : public Scene
{
public:
	CREATE_FUNC(GameScene);
	static cocos2d::Scene* createScene();
	PhysicsWorld* m_world;
	void setPhyWorld(PhysicsWorld* world) { m_world = world; };
	bool init() override;
	void initGameLayer();
	//这是服务器返回的结果，表示我是植物方还是僵尸方
	//收到服务器返回的信息时，场景要从匹配场景转换到对战场景
	//接收服务器信息是在匹配场景接收的，然后把参数传到对战场景的_plantOrZombie中
	//取值   true   false
};
