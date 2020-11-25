#include "GameController.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "global.h"
#include "socket.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion; 
extern Vector<ZombieBaseClass*>_zombieVectorGlobalVariable;//ע�⣬��������ȫ�ֱ���
extern Vector<PlantBaseClass*> _plantVectorGlobalVariable;
/*�����������ǵ�������Ҫ�У�����ʱ���жϽ�ʬ�Ƿ�����԰����������
*�����������Ҫ�ӷ�����������Ϣ�����ݽ��յ���Ϣ����ֲ��/��ʬ
*������ʱΪ0ʱ�����ʱ����ģʽ��ʤ������ʾ
*����������remainTimeMinueOneSecond��isZombieWin
*����ʱΪ0ʱ������ǵ�������ʾʤ���������������ֲ�﷽ʤ������ʬ����ʾʧ��
*isZombieWin��ʬ�ڵ���ʱ����ǰ�����˼�԰
����ǵ�������ʾ��������ӱ���ʬ���ˡ��������������ֲ�﷽��ʾ��������ӱ���ʬ���ˡ�����ʬ��ʤ��
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
	this->schedule(schedule_selector(GameController::isZombieWin), 0.5f);//�жϽ�ʬ�Ƿ�ʤ��
	this->schedule(schedule_selector(GameController::sendHeartBeat), 1.f);//�����Ƿ�����������Ҫ��������
	//this->schedule(schedule_selector(GameController::remainTimeMinueOneSecond), 1.f);//����ʱ��һ
	if (isSinglePlayerGameMode)
	{		
		//����ģʽ�Զ�������ʬ
		this->schedule(schedule_selector(GameController::produceZombieUpdate), 6.f);
		this->schedule(schedule_selector(GameController::remainTimeMinueOneSecond), 1.f);//����ʱ��һ
	}
	
	else
	{
		//����ģʽ�ӷ�����������Ϣ
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
			if (firstFiveZombieNotInSameLine.find(y) == firstFiveZombieNotInSameLine.end())//û���ҵ�
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
	//���յ�start��Ϣ��ſ�ʼ����ʱ
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
				//����ʱΪ0��ֻ���ǽ�ʬ���ˣ�ֲ�﷽Ӯ��
				SimpleAudioEngine::getInstance()->stopAllEffects();
				SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
				SimpleAudioEngine::getInstance()->playEffect("res/music/winmusic.wma");
				//������������ֲ�﷽����Ӯ��
				((GameLayer*)this->getParent())->_showSloganLayer->winInSingleMode();
				//Director::getInstance()->pause();
				//ʤ���ˣ���ʾʤ��ͼƬ���˳�����
				//((GameLayer*)this->getParent())->onExit();
				//((GameLayer*)this->getParent())->_normalZombieLayer->onExit();
				this->unschedule(schedule_selector(GameController::remainTimeMinueOneSecond));
				this->unschedule(schedule_selector(GameController::isZombieWin));
				_zombieVectorGlobalVariable.clear();
				_plantVectorGlobalVariable.clear();
				//Director::getInstance()->popScene();
				log("Win!!!");
			}
			else if (_iAmPlantSideGolbalVariable == true && isSinglePlayerGameMode == false)//����ģʽֲ�﷢��ʤ��
			{
				TCPSocket::getInstance()->writeIntoServer("WIN;\n");//����ʤ����Ϣ
			}
			//else//��ʬ������
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

/*����ǵ�������ʬ�ڵ���ʱ����ǰ�����԰����ʬʤ������ʾ��������ӱ���ʬ���ˡ�
*�����������ֲ�﷽���ˣ���ʬ��Ӯ�ˣ���ʬ����ʾʤ��
*/
void GameController::isZombieWin(float dlt)
{
	if (((GameLayer*)this->getParent())->_normalZombieLayer->isZombieWin())//
	{
		if (isSinglePlayerGameMode == true)
		{
			this->unschedule(schedule_selector(GameController::remainTimeMinueOneSecond));
			this->unschedule(schedule_selector(GameController::isZombieWin));
			_zombieVectorGlobalVariable.clear();
			_plantVectorGlobalVariable.clear();
			//Director::getInstance()->popScene();
		}
	}
}

void GameController::receiveFromServer(float dlt)
{
	//�յ��ĸ�ʽ
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
			//�����������ݰ�������Ҫ����
		}
		else if (_name[0] == 'W' && _name[1] == 'I' && _name[2] == 'N')
		{
			//������˵��ʤ����
			this->serverTellWin();
		}
		else if (_name[0] == 'L' && _name[1] == 'O' && _name[2] == 'S' && _name[3] == 'E')
		{
			//������˵������
			this->serverTellLose();
		}
		else if (_name[0] == 'S' && _name[1] == 'T' && _name[2] == 'A' && _name[3] == 'R' && _name[4] == 'T')
		{
			this->readySprite->removeFromParent();
			this->startSprite->setVisible(true);
			auto tempSprite = this->startSprite;
			tempSprite->runAction(Sequence::createWithTwoActions(DelayTime::create(1.f), CallFunc::create([tempSprite]()
				{
					tempSprite->removeFromParent();
				})));
			this->schedule(schedule_selector(GameController::remainTimeMinueOneSecond), 1.f);//����ʱ��һ
			//this->startTiming = true;
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

void GameController::serverTellWin()
{
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	SimpleAudioEngine::getInstance()->playEffect("res/music/winmusic.wma");
	//������������ֲ�﷽����Ӯ��
	((GameLayer*)this->getParent())->_showSloganLayer->winInSingleMode();
	//Director::getInstance()->pause();
	//ʤ���ˣ���ʾʤ��ͼƬ���˳�����
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
		//����ֲ�﷽
		((GameLayer*)this->getParent())->_showSloganLayer->showZombieEnterYourHome();
		SimpleAudioEngine::getInstance()->playEffect("res/music/losemusic.wma");	
	
	}
	else
	{
		//���ǽ�ʬ��
		SimpleAudioEngine::getInstance()->playEffect("res/music/losemusic.wma");
		((GameLayer*)this->getParent())->_showSloganLayer->showZombieLose();
	}
	_zombieVectorGlobalVariable.clear();
	_plantVectorGlobalVariable.clear();
	//��ʱ�л��������л���������
		//((GameLayer*)this->getParent())->onExit();
}
