#include "PlantBaseClass.h"

PlantBaseClass::PlantBaseClass()
{
	_peaShooterCache = SpriteFrameCache::getInstance();
	_peaShooterCache->addSpriteFramesWithFile("res/peashooter.plist");
}

PlantBaseClass::~PlantBaseClass()
{
}

bool PlantBaseClass::init()
{
	if (!Sprite::init())
	{
		return false;
	}

	return true;
}
