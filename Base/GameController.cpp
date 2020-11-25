#include "GameController.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "global.h"
#include "socket.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion; 
extern Vector<ZombieBaseClass*>_zombieVectorGlobalVariable;//注意，这两个是全局变量
extern Vector<PlantBaseClass*> _plantVectorGlobalVariable;
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
	this->_remainingTime = 120;
	startTiming = false;
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
	this->schedule(schedule_selector(GameController::isZombieWin), 0.5f);//判断僵尸是否胜利
	this->schedule(schedule_selector(GameController::sendHeartBeat), 1.f);//不管是否联机，都需要发送心跳
	//this->schedule(schedule_selector(GameController::remainTimeMinueOneSecond), 1.f);//倒计时减一
	if (isSinglePlayerGameMode)
	{		
		//单机模式自动产生僵尸
		this->schedule(schedule_selector(GameController::produceZombieUpdate), 6.f);
		this->schedule(schedule_selector(GameController::remainTimeMinueOneSecond), 1.f);//倒计时减一
	}
	
	else
	{
		//联机模式从服务器接收信息
		this->schedule(schedule_selector(GameController::receiveFromServer), 0.15f);		
	}
	if (isSinglePlayerGameMode == false)
	{
		this->readySprite = Sprite::create("res/ready.png");
		this->startSprite = Sprite::create("res/start.png");
		this->readySprite->setPosition(700, 300);
		this->addChild(this->readySprite);
		this->addChild(this->startSprite);
		this->startSprite->setVisible(false);
		this->startSprite->setPosition(700, 300);
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

void GameController::removePlant(Vec2 _pos)
{
	for (auto x : _plantVectorGlobalVariable)
	{
		if (x->getBoundingBox().containsPoint(_pos))
		{
			x->_plantHP -= 30000;
			break;
		}
	}
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
	//当收到start信息后才开始倒计时
	//if (isSinglePlayerGameMode == true || startTiming == true)
	//{
		string _remainTimeStr = StringUtils::format("%d", --(this->_remainingTime));
		this->_remainTimeLabel->setString(_remainTimeStr);
		if (this->_remainingTime == 9)
		{
			SimpleAudioEngine::getInstance()->playEffect("res/music/remainingTime.wma");
			((GameLayer*)this->getParent())->_showSloganLayer->showRemainingTime();
		}
		if (this->_remainingTime == 0)
		{
			this->unschedule(schedule_selector(GameController::remainTimeMinueOneSecond));
			this->unschedule(schedule_selector(GameController::isZombieWin));
			if (isSinglePlayerGameMode == true)
			{
				//倒计时为0，只能是僵尸输了，植物方赢了
				SimpleAudioEngine::getInstance()->stopAllEffects();
				SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
				SimpleAudioEngine::getInstance()->playEffect("res/music/winmusic.wma");
				//单机或者联机植物方都是赢了
				((GameLayer*)this->getParent())->_showSloganLayer->winInSingleMode();
				//Director::getInstance()->pause();
				//胜利了，显示胜利图片，退出场景
				//((GameLayer*)this->getParent())->onExit();
				//((GameLayer*)this->getParent())->_normalZombieLayer->onExit();
				this->unschedule(schedule_selector(GameController::remainTimeMinueOneSecond));
				this->unschedule(schedule_selector(GameController::isZombieWin));
				_zombieVectorGlobalVariable.clear();
				_plantVectorGlobalVariable.clear();
				//Director::getInstance()->popScene();
				log("Win!!!");
			}
			else if (_iAmPlantSideGolbalVariable == true && isSinglePlayerGameMode == false)//联机模式植物发送胜利
			{
				TCPSocket::getInstance()->writeIntoServer("WIN;\n");//发送胜利信息
			}
			//else//僵尸方输了
			//{
			//	this->unschedule(schedule_selector(GameController::remainTimeMinueOneSecond));
			//	SimpleAudioEngine::getInstance()->stopAllEffects();
			//	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			//	SimpleAudioEngine::getInstance()->playEffect("res/music/losemusic.wma");
			//	((GameLayer*)this->getParent())->_showSloganLayer->showZombieLose();
			//}
		}
	//}
}

/*如果是单机，僵尸在倒计时结束前进入家园，僵尸胜利，显示“你的脑子被僵尸吃了”
*如果是联机，植物方输了，僵尸方赢了，僵尸方显示胜利
*/
void GameController::isZombieWin(float dlt)
{
	if (((GameLayer*)this->getParent())->_normalZombieLayer->isZombieWin())//
	{
		if (isSinglePlayerGameMode == true)
		{
			_zombieVectorGlobalVariable.clear();
			_plantVectorGlobalVariable.clear();
			this->unschedule(schedule_selector(GameController::remainTimeMinueOneSecond));
			this->unschedule(schedule_selector(GameController::isZombieWin));
			this->unschedule(schedule_selector(GameController::produceZombieUpdate));
			//Director::getInstance()->popScene();
		}
	}
}

void GameController::receiveFromServer(float dlt)
{
	//收到的格式
	//1NormalZombie:1098,908;\n
	//植物方只需要收到僵尸的位置
	//僵尸方需要收到植物种下，植物死亡，僵尸的位置及动作
	//僵尸方不需要扣植物或僵尸的血量
	//WIN LOSE HeartBeat
	//植物方做计算，僵尸方不做任何计算，只是单纯的显示
	//僵尸方只会发送僵尸种下的信息
	//1表示植物或僵尸种下的位置，当植物方或僵尸方种下时，发送该信息
	//1NormalZombie:1999,21;\n   1Plant:132,321;\n
	//表示植物死亡，植物方植物死亡时，将该信息发送给服务器，这里只关心位置，不关心植物的名字
	//1Remove:2312,31;\n
	//植物方发送僵尸的状态,僵尸标号
	//2NormalZombie:1231,321,ID,walk/attack/noHeadAttack/dropHead/noHeadWalk/die/boomDie;\n


	string message = TCPSocket::getInstance()->readFromServer();
	if (message == "") return;
	if (message[0] == 'H' && message[1] == 'e' && message[2] == 'a')
	{
		//这是心跳数据包
	}
	else if (message[0] == 'W' && message[1] == 'I' && message[2] == 'N')
	{
		//服务器说我胜利了
		this->serverTellWin();
	}
	else if (message[0] == 'L' && message[1] == 'O' && message[2] == 'S' && message[3] == 'E')
	{
		//收到失败的客户端再向服务器发送一个lose
		TCPSocket::getInstance()->writeIntoServer("LOSE;\n");
		//服务器说我输了
		this->serverTellLose();
	}
	else if (message[0] == 'S' && message[1] == 'T' && message[2] == 'A' && message[3] == 'R')
	{
		//服务器说开始！
		this->readySprite->removeFromParent();
		this->startSprite->setVisible(true);
		auto tempSprite = this->startSprite;
		tempSprite->runAction(Sequence::createWithTwoActions(DelayTime::create(1.f), CallFunc::create([tempSprite]()
			{
				tempSprite->removeFromParent();
			})));
		this->schedule(schedule_selector(GameController::remainTimeMinueOneSecond), 1.f);//倒计时减一
	}
	else if (message[0] = '1')
	{
		string _mess = message.substr(1);//去掉第一个字符1
		//植物或僵尸种下，或者植物死亡
		string _name, _pos1, _pos2;
		size_t i = 0;
		for (i = 0; i < _mess.size(); i++)
		{
			if (_mess[i] != ':')
			{
				_name += _mess[i];
			}
			else break;
		}
		for (i = i + 1; i < _mess.size(); i++)
		{
			if (_mess[i] != ',')
			{
				_pos1 += _mess[i];
			}
			else break;
		}
		for (i = i + 1; i < _mess.size(); i++)
		{
			if (_mess[i] != ';')
			{
				_pos2 += _mess[i];
			}
			else break;
		}
		int pos1 = 0, pos2 = 0;
		if (_pos1 != "")
			pos1 = stoi(_pos1);
		if (_pos2 != "")
			pos2 = stoi(_pos2);
		Vec2 pos(pos1, pos2);
		//这个是植物方收到的
		if (_name == "NormalZombie" || _name == "ConeheadZombie" || _name == "BucketheadZombie" || _name == "FlagZombie")
		{
			this->produceNormalZombieSprite(_name, pos);
		}
		//以下都是僵尸方收到的
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
		else if (_name == "Remove")
		{
			this->removePlant(pos);
		}
	}
	//这是向僵尸方发送的
	//2NormalZombie:1231,321,ID,walk/attack/noHeadAttack/dropHead/noHeadWalk/die/boomDie;\n
	else if (message[0] == '2')
	{
		string _pos1, _pos2, _ID, _action;
		int i, j;
		for (i = 0; i < message.size(); i++)
		{
			if (message[i] == ':')
				break;
		}
		//i为：的位置
		for (i = i + 1; i < message.size(); i++)
		{
			if (message[i] != ',')
				_pos1 += message[i];
			else
				break;
		}
		for (i = i + 1; i < message.size(); i++)
		{
			if (message[i] != ',')
				_pos2 += message[i];
			else
				break;
		}
		for (i = i + 1; i < message.size(); i++)
		{
			if (message[i] != ',')
				_ID += message[i];
			else
				break;
		}
		Vec2 _pos(stoi(_pos1), stoi(_pos2));
		int _id = stoi(_ID);
		vector<int> _action;
		string tmp;
		for (i = i + 1; i < message.size(); i++)
		{
			if (message[i] != ';')
			{
				if (message[i] != ',')
				{
					tmp += message[i];
				}
				else
				{
					_action.push_back(stoi(tmp));
					tmp = "";
				}
			}
			else
				break;
		}
		for (auto x : _zombieVectorGlobalVariable)
		{
			if (x->zombieID == _id)
			{
				x->setPosition(_pos);
				x->stopAllActions();
				for (auto y : _action)
				{
					if (y == 1)
					{
						x->runAction(x->normalZombieWalkAnimation());
					}
					else if (y == 2)
					{
						x->runAction(x->normalZombieNoHeadWalkAnimation());
					}
					else if (y == 3)
					{
						x->runAction(x->normalZombieAttackAnimation());
					}
					else if (y == 4)
					{
						x->runAction(x->normalZombieLostHeadAttackAnimation());
					}
					else if (y == 5)
					{
						x->runAction(x->flagZombieWalkAnimation());
					}
					else if (y == 6)
					{
						x->runAction(x->flagZombieNoHeadWalkAnimation());
					}
					else if (y == 7)
					{
						x->runAction(x->flagZombieAttackAnimation());
					}
					else if (y == 8)
					{
						x->runAction(x->flagZombieLostHeadAttackAnimation());
					}
					else if (y == 9)
					{
						x->runAction(x->coneheadZombieWalkAnimation());
					}
					else if (y == 10)
					{
						x->runAction(x->coneheadZombieAttackAnimation());
					}
					else if (y == 11)
					{
						x->runAction(x->bucketheadZombieWalkAnimation());
					}
					else if (y == 12)
					{
						x->runAction(x->bucketheadZombieAttackAnimation());
					}
					else if (y == 13)
					{
						x->runAction(x->zombieMoveWay(x->zombieSpeed))
					}
					else if (y == 14)//掉头动作
					{
						auto tmpSprite = Sprite::create();
						this->addChild(tmpSprite);
						tmpSprite->setPosition(x->getPosition());
						//让掉头的动作靠前一点，更显得真实
						tmpSprite->setPositionX(tmpSprite->getPositionX() + 35);

						//注意，为了使僵尸只掉一次头，这里把僵尸的血量减一
						//tmpSprite->runAction((*i)->headAnimation());
						tmpSprite->runAction(Sequence::createWithTwoActions(x
							->headAnimation(), CallFunc::create([tmpSprite]() {
								tmpSprite->removeFromParent();
								})));
					}
					else if (y == 15)
					{
						auto tmp = x;
						x->runAction(Sequence::createWithTwoActions(x
							->downTheGround(), CallFunc::create([tmp]() {
								(tmp)->removeFromParent();//将僵尸删除
								})));
					}
					else if (y == 16)
					{
						auto tmp = x;
						x->runAction(Sequence::createWithTwoActions(x
							->explodAnimation(), CallFunc::create([tmp]() {
								(tmp)->removeFromParent();//将僵尸删除
								})));
					}
				}
				break;
			}
		}
	}

}

void GameController::sendHeartBeat(float dlt)
{
	TCPSocket::getInstance()->writeIntoServer("HeartBeat;\n");
}

void GameController::serverTellWin()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	SimpleAudioEngine::getInstance()->playEffect("res/music/winmusic.wma");
	//单机或者联机植物方都是赢了
	((GameLayer*)this->getParent())->_showSloganLayer->winInSingleMode();
	//Director::getInstance()->pause();
	//胜利了，显示胜利图片，退出场景
	//((GameLayer*)this->getParent())->onExit();
	//((GameLayer*)this->getParent())->_normalZombieLayer->onExit();
	this->unschedule(schedule_selector(GameController::remainTimeMinueOneSecond));
	this->unschedule(schedule_selector(GameController::isZombieWin));
	_zombieVectorGlobalVariable.clear();
	_plantVectorGlobalVariable.clear();
	log("Win!!!");
}

void GameController::serverTellLose()
{
	this->unschedule(schedule_selector(GameController::remainTimeMinueOneSecond));
	this->unschedule(schedule_selector(GameController::isZombieWin));
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	if (_iAmPlantSideGolbalVariable == true)
	{
		//我是植物方
		((GameLayer*)this->getParent())->_showSloganLayer->showZombieEnterYourHome();
		SimpleAudioEngine::getInstance()->playEffect("res/music/losemusic.wma");	
	
	}
	else
	{
		//我是僵尸方
		SimpleAudioEngine::getInstance()->playEffect("res/music/losemusic.wma");
		((GameLayer*)this->getParent())->_showSloganLayer->showZombieLose();
	}
	_zombieVectorGlobalVariable.clear();
	_plantVectorGlobalVariable.clear();
	//此时切换场景，切换回主场景
		//((GameLayer*)this->getParent())->onExit();
}
