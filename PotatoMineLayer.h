#pragma once
#include "cocos2d.h"
#include "PotatoMineSprite.h"
#include <vector>
using namespace std;
USING_NS_CC;
class PotatoMineLayer : public Layer
{
public:
	CREATE_FUNC(PotatoMineLayer);
	PotatoMineLayer();
	~PotatoMineLayer();
	virtual bool init();
	PotatoMineSprite* _potatoMineSprite;
	void initPotatoMineSprite(Touch*);//初始化土豆地雷，传一个触摸点给它
	void grow(float);
	Vector<PotatoMineSprite*> _potatoMineVector;
	void potatoMineAttackZombie();
	void diedPotatoMine();
	virtual void update(float dt);
	//vector<int> _potatoMineTime;//该地雷已经被种下的时间，每隔0.1秒加一
};
