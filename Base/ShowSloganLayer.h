#pragma once
#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;
class ShowSloganLayer : public Layer
{
public:
	CREATE_FUNC(ShowSloganLayer);
	ShowSloganLayer();
	~ShowSloganLayer();
	bool init() override;
	void showPrepareInfo();
	void showZombieEnterYourHome();
	void winInSingleMode();
	void showZombieLose();
	SpriteFrameCache* _num;
	FiniteTimeAction* _remainingTime;
	void showRemainingTime();
};