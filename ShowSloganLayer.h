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
	virtual bool init();
	void showPrepareInfo();
};