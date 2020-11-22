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

MapLayer::MapLayer()
{
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 5; j++)
			_isPlanted[i][j] = false;
}

void MapLayer::initMap()
{
	 auto _map = Sprite::create("res/bg_map.jpg");
	 _map->setAnchorPoint(Vec2(0,0));
	this->addChild(_map);
}

bool MapLayer::isRightPositionForPlants(int & x, int & y)
{
	if ((x < 1000 && x >236) && (y < 510 && y > 30) )
	{
		if (x > 236 && x < 333)
			x = 289;
		else if (x < 405)
			x = 372;
		else if (x < 493)
			x = 456;
		else if (x < 574)
			x = 535;
		else if (x < 652)
			x = 619;
		else if (x < 734)
			x = 695;
		else if (x < 815)
			x = 774;
		else if (x < 896)
			x = 857;
		else if (x < 1000)
			x = 945;
		if (y > 30 && y < 129)
			y = 80;
		else if (y < 219)
			y = 175;
		else if (y < 320)
			y = 274;
		else if (y < 419)
			y = 375;
		else if (y < 510)
			y = 475;
		if (this->_isPlanted[(x - 200) / 90][y / 100] == false)
			return true;
		else
			return false;
	}
	return false;
}
