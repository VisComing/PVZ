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
	bool _isPlanted[9][5];//��ͼ���Ƿ���ֲ����
	bool isRightPositionForPlants(int &x, int& y);
private:
	//Sprite* _map;
};
