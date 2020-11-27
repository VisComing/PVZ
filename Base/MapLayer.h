#pragma once
#include "cocos2d.h"
USING_NS_CC;

class MapLayer : public Layer
{
public:
	CREATE_FUNC(MapLayer);
	MapLayer();
	~MapLayer() {};
	bool init() override;
	void initMap();
	bool _isPlanted[9][5];//地图上是否种植物了
	bool isRightPositionForPlants(int &x, int& y);
private:
	//Sprite* _map;
};
