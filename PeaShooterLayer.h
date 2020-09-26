#pragma once
#include "cocos2d.h"
#include "PeaShooterSprite.h"
#include <vector>
using namespace std;
//#include "GameLayer.h"
USING_NS_CC;
class PeaShooterLayer : public Layer
{
public:
	CREATE_FUNC(PeaShooterLayer);
	PeaShooterLayer();
	~PeaShooterLayer();
	virtual bool init();
	PeaShooterSprite* _peaShooterSprite;
	void initPeaShooterSprite(Touch*);//初始化豌豆射手，，出一个触摸点给它

	Vector<Sprite*> _peaShooterVector;

	vector<int> _peaShooterTime;//该射手已经被种下的时间，每隔0.1秒加一
};
