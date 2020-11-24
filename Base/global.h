#pragma once
#include "../Zombies/ZombieBaseClass.h"
#include "../Plants/PlantBaseClass.h"
#include "cocos2d.h"
USING_NS_CC;
extern Vector<ZombieBaseClass*> _zombieVectorGlobalVariable;
extern bool _iAmPlantSideGolbalVariable;
extern Vector<PlantBaseClass*> _plantVectorGlobalVariable;
extern bool isSinglePlayerGameMode;