#pragma once
#include "cocos2d.h"
USING_NS_CC;

class MapLayer : public Layer
{
public:
	CREATE_FUNC(MapLayer);
	MapLayer() {};
	~MapLayer() {};
	virtual bool init();
	void initMap();
	bool _isPlanted[9][5];//地图上是否种植物了
private:
	//Sprite* _map;
};
