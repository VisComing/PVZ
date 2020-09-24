#pragma once
#include "cocos2d.h"
USING_NS_CC;

class TouchLayer : public Layer
{
public:
	CREATE_FUNC(TouchLayer);
	TouchLayer();
	~TouchLayer();
	virtual bool init();

	bool onTouchBegan(Touch*, Event*);
	bool onMouseMove(Event*);
	bool _isPeaShooter;
};
