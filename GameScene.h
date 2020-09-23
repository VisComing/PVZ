#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GameScene : public Scene
{
public:
	CREATE_FUNC(GameScene);
	static cocos2d::Scene* createScene();

	virtual bool init();
	void initGameLayer();

};
