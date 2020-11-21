#include "GameController.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "global.h"
#include "socket.h"
GameController::GameController()
{
	this->firstFiveZombie = 0;
	this->_remainingTime = 240;
}
GameController::~GameController()
{
}
bool GameController::init()
{
	if (!Layer::init())
	{
		return false;
	}
	if (isSinglePlayerGameMode == true)//是单机游戏
	{
		this->_remainTimeLabel = Label::createWithSystemFont("", "arial", 30);
		this->_remainTimeLabel->setTextColor(Color4B::BLACK);
		this->schedule(schedule_selector(GameController::produceZombieUpdate), 6.f);
		this->addChild(this->_remainTimeLabel);
		this->_remainTimeLabel->setPosition(Vec2(1000, 527));
		this->schedule(schedule_selector(GameController::remainTimeMinueOneSecond), 1.f);
		this->schedule(schedule_selector(GameController::isZombieWin), 0.5f);
	}
	else//不是单机游戏
	{
		this->schedule(schedule_selector(GameController::receiveFromServer), 0.15f);
	}
	return true;
}
void GameController::update(float dt)
{
	
}
void GameController::produceChomperSprite(Vec2 position)
{
	((GameLayer*)this->getParent())->_chomperLayer->produceChomperSprite(position);
}

void GameController::producePeaShooterSprite(Vec2 position)
{
	((GameLayer*)this->getParent())->_peaShooterLayer->producePeaShooterSprite(position);
}

void GameController::producePotatoMineSprite(Vec2 position)
{
	((GameLayer*)this->getParent())->_potatoMineLayer->producePotatoMineSprite(position);
}

void GameController::produceWallNutSprite(Vec2 position)
{
	((GameLayer*)this->getParent())->_wallNutLayer->produceWallNutSprite(position);
}

void GameController::produceSunFlowerSprite(Vec2 position)
{
	((GameLayer*)this->getParent())->_sunFlowerLayer->produceSunFlowerSprite(position);
}


void GameController::produceNormalZombieSprite(string zombieName, Vec2 position)
{
	((GameLayer*)this->getParent())->_normalZombieLayer->autoInitZombie(zombieName, position);
}

void GameController::produceZombieUpdate(float dlt)
{
	
	float x = 1045;
	float y;
	if (firstFiveZombie < 5)
	{
		while (1)
		{
			int random = rand() % 5;
			if (random == 0) y = 80;
			else if (random == 1) y = 175;
			else if (random == 2) y = 274;
			else if (random == 3) y = 375;
			else y = 475;
			if (firstFiveZombieNotInSameLine.find(y) == firstFiveZombieNotInSameLine.end())//没有找到
			{
				firstFiveZombieNotInSameLine.insert(y);
				break;
			}
		}		
		firstFiveZombie++;
	}
	else
	{
		int random = rand() % 5;
		if (random == 0) y = 80;
		else if (random == 1) y = 175;
		else if (random == 2) y = 274;
		else if (random == 3) y = 375;
		else y = 475;
	}
	Vec2 _pos = Vec2(x, y);
	int random = rand() % 4;
	if (random == 0) produceNormalZombieSprite("NormalZombie", _pos);
	else if(random == 1) produceNormalZombieSprite("FlagZombie", _pos);
	else if(random == 2) produceNormalZombieSprite("ConeheadZombie", _pos);
	else produceNormalZombieSprite("BucketheadZombie", _pos);

}

void GameController::remainTimeMinueOneSecond(float dlt)
{
	string _remainTimeStr = StringUtils::format("%dsecond", --(this->_remainingTime));
	this->_remainTimeLabel->setString(_remainTimeStr);
	if (this->_remainingTime == 0)
	{
		SimpleAudioEngine::getInstance()->stopAllEffects();
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		SimpleAudioEngine::getInstance()->playEffect("res/music/winmusic.wma");
		((GameLayer*)this->getParent())->_showSloganLayer->winInSingleMode();
		//Director::getInstance()->pause();
		//胜利了，显示胜利图片，退出场景
		//((GameLayer*)this->getParent())->onExit();
		//((GameLayer*)this->getParent())->_normalZombieLayer->onExit();
		this->unschedule(schedule_selector(GameController::remainTimeMinueOneSecond));
		this->unschedule(schedule_selector(GameController::isZombieWin));
		log("Win!!!");
	}
}

void GameController::isZombieWin(float dlt)
{
	if (((GameLayer*)this->getParent())->_normalZombieLayer->isZombieWin())
	{
		this->unschedule(schedule_selector(GameController::remainTimeMinueOneSecond));
		this->unschedule(schedule_selector(GameController::isZombieWin));
	}
}

void GameController::receiveFromServer(float dlt)
{
	//收到的格式
	//NormalZombie:1098,908;\n
	string message = TCPSocket::getInstance()->readFromServer();
	if (message == "") return;
	else
	{
		string _name, _pos1, _pos2;
		size_t i = 0;
		for (i = 0; i < message.size(); i++)
		{
			if (message[i] != ':')
			{
				_name += message[i];
			}
			else break;
		}
		for (i = i + 1; i < message.size(); i++)
		{
			if (message[i] != ',')
			{
				_pos1 += message[i];
			}
			else break;
		}
		for (i = i + 1; i < message.size(); i++)
		{
			if (message[i] != ';')
			{
				_pos2 += message[i];
			}
			else break;
		}
		
		int pos1 = stoi(_pos1);
		int pos2 = stoi(_pos2);
		Vec2 pos(pos1, pos2);
		if (_name == "NormalZombie" || _name == "ConeheadZombie" || _name == "BucketheadZombie" || _name == "FlagZombie")
		{
			this->produceNormalZombieSprite(_name, pos);
		}
		else if (_name == "Chomper")
		{
			this->produceChomperSprite(pos);
		}
		else if (_name == "PesShooter")
		{
			this->producePeaShooterSprite(pos);
		}
		else if (_name == "PotatoMine")
		{
			this->producePotatoMineSprite(pos);
		}
		else if (_name == "WallNut")
		{
			this->produceWallNutSprite(pos);
		}
		else if (_name == "SunFlower")
		{
			this->produceSunFlowerSprite(pos);
		}
		else
		{
			log("error in GameController receiveFromServer");
		}
	}
}
