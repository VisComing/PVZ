#pragma once
#include "../Zombies/NormalZombieSprite.h"
#include "../Plants/PlantBaseClass.h"
#include "cocos2d.h"
USING_NS_CC;
extern Vector<NormalZombieSprite*> _zombieVectorGlobalVariable;
extern bool _iAmPlantSideGolbalVariable;
extern Vector<PlantBaseClass*> _plantVectorGlobalVariable;
extern bool isSinglePlayerGameMode;