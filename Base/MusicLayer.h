#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
class MusicLayer : public Layer
{
public:
	CREATE_FUNC(MusicLayer);
	MusicLayer();
	~MusicLayer();
	bool init() override;
	SimpleAudioEngine* _effectiveMusic;
	void preLoadMusic();
};
