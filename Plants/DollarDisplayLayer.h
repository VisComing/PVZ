#pragma once
#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;
class DollarDisplayLayer : public Layer
{
public:
	CREATE_FUNC(DollarDisplayLayer);
	DollarDisplayLayer();
	~DollarDisplayLayer();
	virtual bool init();
	void displayDollarLable();
	int _dollar;
	string _dollarStr;
	Label* _dollarLabel;
	virtual void update(float dt);
};