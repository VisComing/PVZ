#include "MusicLayer.h"
#include "global.h"
MusicLayer::MusicLayer()
{
	_effectiveMusic = SimpleAudioEngine::getInstance();
}

MusicLayer::~MusicLayer()
{
}

bool MusicLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->preLoadMusic();
	if (_iAmPlantSideGolbalVariable == true || isSinglePlayerGameMode == true)
	{
		_effectiveMusic->playBackgroundMusic("res/music/backgroundMusic.wma", true);
	}
	else
	{
		_effectiveMusic->playBackgroundMusic("res/music/zombiePlayerBGM.wma", true);
	}
	return true;
}

void MusicLayer::preLoadMusic()
{
	_effectiveMusic->preloadBackgroundMusic("res/music/backgroundMusic.wma");
	_effectiveMusic->preloadBackgroundMusic("res/music/zombiePlayerBGM.wma");
	_effectiveMusic->preloadEffect("res/music/clickSunSprite.wma");
	_effectiveMusic->preloadEffect("res/music/potatoMine.wma");
	_effectiveMusic->preloadEffect("res/music/bullet.wma");
	_effectiveMusic->preloadEffect("res/music/zombieChomp.wma");
	_effectiveMusic->preloadEffect("res/music/zombieChomp2.wma");
	_effectiveMusic->preloadEffect("res/music/zombieChomp3.wma");
	_effectiveMusic->preloadEffect("res/music/GrowPlant.wma");
	_effectiveMusic->preloadEffect("res/music/GrowPlant2.wma");
	_effectiveMusic->preloadEffect("res/music/zombieGroan.wma");
	_effectiveMusic->preloadEffect("res/music/zombieGroan2.wma");
	_effectiveMusic->preloadEffect("res/music/zombieGroan3.wma");
	_effectiveMusic->preloadEffect("res/music/zombieGroan4.wma");
	_effectiveMusic->preloadEffect("res/music/zombieGroan5.wma");
	_effectiveMusic->preloadEffect("res/music/zombieGroan6.wma");
	_effectiveMusic->preloadEffect("res/music/clickCard.wma");
	_effectiveMusic->preloadEffect("res/music/losemusic.wma");
	_effectiveMusic->preloadEffect("res/music/winmusic.wma");
	_effectiveMusic->preloadEffect("res/music/shovel.wma");
	_effectiveMusic->preloadEffect("res/music/noEnoughMoney.wma");
}

