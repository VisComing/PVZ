#pragma once
#include "cocos2d.h"
USING_NS_CC;

class TouchLayer : public Layer
{
public:
	CREATE_FUNC(TouchLayer);
	TouchLayer();
	~TouchLayer();
	bool init() override;

	bool onTouchBegan(Touch*, Event*);
	void onTouchEnded(Touch*, Event*);
	bool _isCreatePeaShooter;

	//SpriteFrameCache* _bulletCache;

	//Vector<Sprite*> _bulletVector;
};
