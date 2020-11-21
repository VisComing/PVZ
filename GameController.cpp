#include "GameController.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "global.h"
#include "socket.h"
/*不管联机还是单机，都要有：倒计时，判断僵尸是否进入家园，发送心跳
*如果是联机：要从服务器接收信息，根据接收的信息创建植物/僵尸
*当倒计时为0时，如果时单机模式，胜利，显示
*有两个函数remainTimeMinueOneSecond和isZombieWin
*倒计时为0时，如果是单机，显示胜利，如果是联机，植物方胜利，僵尸方显示失败
*isZombieWin僵尸在倒计时结束前进入了家园
如果是单机，显示“你的脑子被僵尸吃了”，如果是联机，植物方显示“你的脑子被僵尸吃了”，僵尸方胜利
*/
GameController::GameController()
{
	this->firstFiveZombie = 0;
	this->_remainingTime = 10;
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
	this->_remainTimeLabel = Label::createWithSystemFont("", "arial", 50);
	this->_remainTimeLabel->setTextColor(Color4B(200, 0, 0, 255));
	this->addChild(this->_remainTimeLabel);
	this->_remainTimeLabel->setPosition(Vec2(790, 570));
	this->schedule(schedule_selector(GameController::remainTimeMinueOneSecond), 1.f);//倒计时减一
	this->schedule(schedule_selector(GameController::isZombieWin), 0.5f);//判断僵尸是否胜利
	this->schedule(schedule_selector(GameController::sendHeartBeat), 1.f);//不管是否联机，都需要发送心跳
	if (isSinglePlayerGameMode)
	{		
		//单机模式自动产生僵尸
		this->schedule(schedule_selector(GameController::produceZombieUpdate), 6.f);		
	}
	else
	{
		//联机模式从服务器接收信息
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
	string _remainTimeStr = StringUtils::format("%d", --(this->_remainingTime));
	this->_remainTimeLabel->setString(_remainTimeStr);
	if (this->_remainingTime == 0)
	{
		if (_iAmPlantSideGolbalVariable == true || isSinglePlayerGameMode == true)
		{
			//倒计时为0，只能是僵尸输了，植物方赢了
			SimpleAudioEngine::getInstance()->stopAllEffects();
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			SimpleAudioEngine::getInstance()->playEffect("res/music/winmusic.wma");
			//单机或者联机植物方都是赢了
			((GameLayer*)this->getParent())->_showSloganLayer->winInSingleMode();
			//Director::getInstance()->pause();
			//胜利了，显示胜利图片，退出场景
			//((GameLayer*)this->getParent())->onExit();
			//((GameLayer*)this->getParent())->_normalZombieLayer->onExit();
			this->unschedule(schedule_selector(GameController::remainTimeMinueOneSecond));
			this->unschedule(schedule_selector(GameController::isZombieWin));
			log("Win!!!");
		}
		else//僵尸方输了
		{
			this->unschedule(schedule_selector(GameController::remainTimeMinueOneSecond));
			SimpleAudioEngine::getInstance()->stopAllEffects();
			SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			SimpleAudioEngine::getInstance()->playEffect("res/music/losemusic.wma");
			((GameLayer*)this->getParent())->_showSloganLayer->showZombieLose();
		}
	}
}

/*如果是单机，僵尸在倒计时结束前进入家园，僵尸胜利，显示“你的脑子被僵尸吃了”
*如果是联机，植物方输了，僵尸方赢了，僵尸方显示胜利
*/
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
		int pos1 = 0, pos2 = 0;
		if(_pos1 != "")
			pos1 = stoi(_pos1);
		if(_pos2 != "")
			pos2 = stoi(_pos2);
		Vec2 pos(pos1, pos2);
		if (_name == "NormalZombie" || _name == "ConeheadZombie" || _name == "BucketheadZombie" || _name == "FlagZombie")
		{
			this->produceNormalZombieSprite(_name, pos);
		}
		else if (_name == "Chomper")
		{
			this->produceChomperSprite(pos);
		}
		else if (_name == "PeaShooter")
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
		else if (_name[0] == 'H' && _name[1] == 'e')
		{
			//这是心跳数据包，不需要处理
		}
		else
		{
			log("error in GameController receiveFromServer");
		}
	}
}

void GameController::sendHeartBeat(float dlt)
{
	TCPSocket::getInstance()->writeIntoServer("HeartBeat;\n");
}
