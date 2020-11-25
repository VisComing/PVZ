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
	//�յ��ĸ�ʽ
	//1NormalZombie:1098,908;\n
	//ֲ�﷽ֻ��Ҫ�յ���ʬ��λ��
	//��ʬ����Ҫ�յ�ֲ�����£�ֲ����������ʬ��λ�ü�����
	//��ʬ������Ҫ��ֲ���ʬ��Ѫ��
	//WIN LOSE HeartBeat
	//ֲ�﷽�����㣬��ʬ�������κμ��㣬ֻ�ǵ�������ʾ
	//��ʬ��ֻ�ᷢ�ͽ�ʬ���µ���Ϣ
	//1��ʾֲ���ʬ���µ�λ�ã���ֲ�﷽��ʬ������ʱ�����͸���Ϣ
	//1NormalZombie:1999,21;\n   1Plant:132,321;\n
	//��ʾֲ��������ֲ�﷽ֲ������ʱ��������Ϣ���͸�������������ֻ����λ�ã�������ֲ�������
	//1Remove:2312,31;\n
	//ֲ�﷽���ͽ�ʬ��״̬,��ʬ���
	//2NormalZombie:1231,321,ID,walk/attack/noHeadAttack/dropHead/noHeadWalk/die/boomDie;\n


	string message = TCPSocket::getInstance()->readFromServer();
	if (message == "") return;
	if (message[0] == 'H' && message[1] == 'e' && message[2] == 'a')
	{
		//�����������ݰ�
	}
	else if (message[0] == 'W' && message[1] == 'I' && message[2] == 'N')
	{
		//������˵��ʤ����
		this->serverTellWin();
	}
	else if (message[0] == 'L' && message[1] == 'O' && message[2] == 'S' && message[3] == 'E')
	{
		//�յ�ʧ�ܵĿͻ����������������һ��lose
		TCPSocket::getInstance()->writeIntoServer("LOSE;\n");
		//������˵������
		this->serverTellLose();
	}
	else if (message[0] == 'S' && message[1] == 'T' && message[2] == 'A' && message[3] == 'R')
	{
		//������˵��ʼ��
		this->readySprite->removeFromParent();
		this->startSprite->setVisible(true);
		auto tempSprite = this->startSprite;
		tempSprite->runAction(Sequence::createWithTwoActions(DelayTime::create(1.f), CallFunc::create([tempSprite]()
			{
				tempSprite->removeFromParent();
			})));
		this->schedule(schedule_selector(GameController::remainTimeMinueOneSecond), 1.f);//����ʱ��һ
	}
	else if (message[0] = '1')
	{
		string _mess = message.substr(1);//ȥ����һ���ַ�1
		//ֲ���ʬ���£�����ֲ������
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
		//�����ֲ�﷽�յ���
		if (_name == "NormalZombie" || _name == "ConeheadZombie" || _name == "BucketheadZombie" || _name == "FlagZombie")
		{
			this->produceNormalZombieSprite(_name, pos);
		}
		//���¶��ǽ�ʬ���յ���
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
	//������ʬ�����͵�
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
		//iΪ����λ��
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
					else if (y == 14)//��ͷ����
					{
						auto tmpSprite = Sprite::create();
						this->addChild(tmpSprite);
						tmpSprite->setPosition(x->getPosition());
						//�õ�ͷ�Ķ�����ǰһ�㣬���Ե���ʵ
						tmpSprite->setPositionX(tmpSprite->getPositionX() + 35);

						//ע�⣬Ϊ��ʹ��ʬֻ��һ��ͷ������ѽ�ʬ��Ѫ����һ
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
								(tmp)->removeFromParent();//����ʬɾ��
								})));
					}
					else if (y == 16)
					{
						auto tmp = x;
						x->runAction(Sequence::createWithTwoActions(x
							->explodAnimation(), CallFunc::create([tmp]() {
								(tmp)->removeFromParent();//����ʬɾ��
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
