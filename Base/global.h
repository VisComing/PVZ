#pragma once
#include "../Zombies/ZombieBaseClass.h"
#include "../Plants/PlantBaseClass.h"
#include "cocos2d.h"
USING_NS_CC;
extern Vector<ZombieBaseClass*> _zombieVector;
extern bool _iAmPlantSideGolbalVariable;
extern Vector<PlantBaseClass*> _plantVector;
extern bool isSinglePlayerGameMode;