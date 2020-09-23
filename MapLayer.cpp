#include "MapLayer.h"
bool MapLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->initMap();
	return true;
}

void MapLayer::initMap()
{
	 auto _map = Sprite::create("res/bg_map.jpg");
	 _map->setAnchorPoint(Vec2(0,0));
	this->addChild(_map);
}