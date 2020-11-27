#include "GameController.h"
#include "GameLayer.h"
#include "GameScene.h"
#include "global.h"
#include "socket.h"
#include "SimpleAudioEngine.h"
#include <algorithm>
using namespace CocosDenshion; 
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
	this->startTiming = false;
	this->timeMinueToNineFlag = false;
	this->_remainTimeLabel = NULL;
	this->readySprite = NULL;
	this->startSprite = NULL;
}
GameController::~GameController()
{
	this->_remainTimeLabel = NULL;
	this->readySprite = NULL;
	this->startSprite = NULL;
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
	this->schedule(schedule_selector(GameController::isZombieWin), 0.1f);//�жϽ�ʬ�Ƿ�ʤ��
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
		this->schedule(schedule_selector(GameController::receiveFromServer), 0.05f);		
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
void GameController::produceChomperSprite(Vec2 position)
{
	(dynamic_cast<GameLayer*>(this->getParent()))->_chomperLayer->produceChomperSprite(position);
}

void GameController::producePeaShooterSprite(Vec2 position)
{
	(dynamic_cast<GameLayer*>(this->getParent()))->_peaShooterLayer->producePeaShooterSprite(position);
}

void GameController::producePotatoMineSprite(Vec2 position)
{
	(dynamic_cast<GameLayer*>(this->getParent()))->_potatoMineLayer->producePotatoMineSprite(position);
}

void GameController::produceWallNutSprite(Vec2 position)
{
	(dynamic_cast<GameLayer*>(this->getParent()))->_wallNutLayer->produceWallNutSprite(position);
}

void GameController::produceSunFlowerSprite(Vec2 position)
{
	(dynamic_cast<GameLayer*>(this->getParent()))->_sunFlowerLayer->produceSunFlowerSprite(position);
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

//���ݽ�ʬ����λ�ò�����ʬ
void GameController::produceNormalZombieSprite(string zombieName, Vec2 position)
{
	(dynamic_cast<GameLayer*>(this->getParent()))->_normalZombieLayer->autoInitZombie(zombieName, position);
}

//����ģʽ�Զ�������ʬ
void GameController::produceZombieUpdate(float dlt)
{
	
	constexpr float x = 1045;
	float y = 0.0;
	if (firstFiveZombie < 5)
	{
		while (1)
		{
			const int random = rand() % 5;
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
		const int random = rand() % 5;
		if (random == 0) y = 80;
		else if (random == 1) y = 175;
		else if (random == 2) y = 274;
		else if (random == 3) y = 375;
		else y = 475;
	}
	const Vec2 _pos = Vec2(x, y);
	const int random = rand() % 4;
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
	string _remainTimeStr;
	if (_iAmPlantSideGolbalVariable == true || isSinglePlayerGameMode == true)
	{
		_remainTimeStr = StringUtils::format("%d", --(this->_remainingTime));
	}
	else
	{
		_remainTimeStr = StringUtils::format("%d", (this->_remainingTime));
	}
	string _message = "RemainTime:" + to_string(this->_remainingTime) + ";\n";
	TCPSocket::getInstance()->writeIntoServer(_message);
		this->_remainTimeLabel->setString(_remainTimeStr);
		if (this->_remainingTime == 9 && this->timeMinueToNineFlag == false)
		{
			this->timeMinueToNineFlag = true;
			SimpleAudioEngine::getInstance()->playEffect("res/music/remainingTime.wma");
			(dynamic_cast<GameLayer*>(this->getParent()))->_showSloganLayer->showRemainingTime();
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
				(dynamic_cast<GameLayer*>(this->getParent()))->_showSloganLayer->winInSingleMode();
				//Director::getInstance()->pause();
				//ʤ���ˣ���ʾʤ��ͼƬ���˳�����
				//(dynamic_cast<GameLayer*>(this->getParent()))->onExit();
				//(dynamic_cast<GameLayer*>(this->getParent()))->_normalZombieLayer->onExit();
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
			//	(dynamic_cast<GameLayer*>(this->getParent()))->_showSloganLayer->showZombieLose();
			//}
		}
	//}
}

/*����ǵ�������ʬ�ڵ���ʱ����ǰ�����԰����ʬʤ������ʾ��������ӱ���ʬ���ˡ�
*�����������ֲ�﷽���ˣ���ʬ��Ӯ�ˣ���ʬ����ʾʤ��
*/
void GameController::isZombieWin(float dlt)
{
	if ((dynamic_cast<GameLayer*>(this->getParent()))->_normalZombieLayer->isZombieWin())//
	{
		if (isSinglePlayerGameMode == true)
		{
			this->unschedule(schedule_selector(GameController::remainTimeMinueOneSecond));
			this->unschedule(schedule_selector(GameController::isZombieWin));
			this->unschedule(schedule_selector(GameController::produceZombieUpdate));

			_zombieVectorGlobalVariable.clear();
			_plantVectorGlobalVariable.clear();
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
	//����
	//1ZombieDie:ID,typeOfDeath;\n
	//ֲ�﷽���ͽ�ʬ��״̬,��ʬ���
	//2NormalZombie:1231,321,ID,walk/attack/noHeadAttack/dropHead/noHeadWalk/die/boomDie;\n


	string message = TCPSocket::getInstance()->readFromServer();
	if (message == "") return;
	if (message.at(0) == 'R' && message.at(1) == 'e' && message.at(2) == 'm')
	{
		//���ǽ�ʬ�����յ��ģ�������ֲ��˵�ʱ��ͬ��
		size_t i;
		string _time;
		for (i = 0; i < message.size(); i++)
		{
			if (message.at(i) == ':')
				break;
		}
		for (i = i + 1; i < message.size(); i++)
		{
			if (message.at(i) != ';')
				_time += message.at(i);
			else
				break;
		}
		this->_remainingTime = stoi(_time);
	}
	if (message.at(0) == 'H' && message.at(1) == 'e' && message.at(2) == 'a')
	{
		//�����������ݰ�
	}
	else if (message.at(0) == 'W' && message.at(1) == 'I' && message.at(2) == 'N')
	{
		//������˵��ʤ����
		this->serverTellWin();
	}
	else if (message.at(0) == 'L' && message.at(1) == 'O' && message.at(2) == 'S' && message.at(3) == 'E')
	{
		//�յ�ʧ�ܵĿͻ����������������һ��lose
		TCPSocket::getInstance()->writeIntoServer("LOSE;\n");
		//������˵������
		this->serverTellLose();
	}
	else if (message.at(0) == 'S' && message.at(1) == 'T' && message.at(2) == 'A' && message.at(3) == 'R')
	{
		//������˵��ʼ��
		this->readySprite->removeFromParent();
		this->startSprite->setVisible(true);
		auto tempSprite = this->startSprite;
		tempSprite->runAction(Sequence::createWithTwoActions(DelayTime::create(1.f), CallFunc::create([tempSprite]()
			{
				tempSprite->removeFromParent();
			})));
		if (_iAmPlantSideGolbalVariable == true)
		{
			this->schedule(schedule_selector(GameController::remainTimeMinueOneSecond), 1.f);//����ʱ��һ
		}
		else
		{
			this->schedule(schedule_selector(GameController::remainTimeMinueOneSecond), 0.3f);
		}
	}
	else if (message.at(0) == '1')
	{
		string _mess = message.substr(1);//ȥ����һ���ַ�1
		//ֲ���ʬ���£�����ֲ������
		string _name, _pos1, _pos2;
		size_t i = 0;
		for (i = 0; i < _mess.size(); i++)
		{
			if (_mess.at(i) != ':')
			{
				_name += _mess.at(i);
			}
			else break;
		}
		for (i = i + 1; i < _mess.size(); i++)
		{
			if (_mess.at(i) != ',')
			{
				_pos1 += _mess.at(i);
			}
			else break;
		}
		for (i = i + 1; i < _mess.size(); i++)
		{
			if (_mess.at(i) != ';')
			{
				_pos2 += _mess.at(i);
			}
			else break;
		}
		int pos1 = 0, pos2 = 0;
		if (_pos1 != "")
			pos1 = stoi(_pos1);
		if (_pos2 != "")
			pos2 = stoi(_pos2);
		const Vec2 pos(pos1, pos2);
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
		else if (_name == "ZombieDie")
		{
			for (auto iter = _zombieVectorGlobalVariable.begin(); iter != _zombieVectorGlobalVariable.end(); iter++)
			{
				auto x = *iter;
				if (x->zombieID == pos1)
				{
					x->stopMusic();
					x->stopAllActions();
					if (pos2 == 0)//���ӵ�����
					{
						auto tmpe = x;
						x->runAction(Sequence::createWithTwoActions(x
							->downTheGround(), CallFunc::create([tmpe]() {
								(tmpe)->removeFromParent();//����ʬɾ��
								})));
					}
					else if (pos2 == 1)//��ը��
					{
						auto tmpe = x;
						x->runAction(Sequence::createWithTwoActions(x
							->explodAnimation(), CallFunc::create([tmpe]() {
								(tmpe)->removeFromParent();//����ʬɾ��
								})));
					}
					else if (pos2 == 2)//��ʳ�˻��Ե�
					{
						x->removeFromParent();
					}
					(dynamic_cast<GameLayer*>(this->getParent()))->_normalZombieLayer->delectZombieFromNormalZombieVector(pos1);
					_zombieVectorGlobalVariable.erase(iter);
					break;
				}
				
			}
				
		}
	}
	//������ʬ�����͵�
	//2NormalZombie:1231,321,ID,walk/attack/noHeadAttack/dropHead/noHeadWalk/die/boomDie;\n
	//2NormalZombie:8.879150,495.000000,0,1,13;
	else if (message.at(0) == '2')
	{
		string _pos1, _pos2, _ID, _action;
		size_t i;
		for (i = 0; i < message.size(); i++)
		{
			if (message.at(i) == ':')
				break;
		}
		//iΪ����λ��
		for (i = i + 1; i < message.size(); i++)
		{
			if (message.at(i) != ',')
				_pos1 += message.at(i);
			else
				break;
		}
		for (i = i + 1; i < message.size(); i++)
		{
			if (message.at(i) != ',')
				_pos2 += message.at(i);
			else
				break;
		}
		for (i = i + 1; i < message.size(); i++)
		{
			if (message.at(i) != ',')
				_ID += message.at(i);
			else
				break;
		}
		const Vec2 _pos(stoi(_pos1), stoi(_pos2));
		const int _id = stoi(_ID);
		vector<int> _taction;
		string tmp;
		for (i = i + 1; i < message.size(); i++)
		{
			if (message.at(i) != ';')
			{
				if (message.at(i) != ',')
				{
					tmp += message.at(i);
				}
				else
				{
					_taction.push_back(stoi(tmp));
					tmp = "";
				}
			}
			else
			{
				_taction.push_back(stoi(tmp));
				break;
			}
		}
		for (auto x : _zombieVectorGlobalVariable)
		{
			if (x->zombieID == _id)
			{
				
				x->setPosition(_pos);
				//x->stopAllActions();������ǲ��е�
				for (auto y : _taction)
				{
					if (y == 1)
					{
						if (!(std::count(x->actionTag.begin(), x->actionTag.end(), 1)))
						{
							x->stopActionByTag(2);
							x->stopActionByTag(3);//��ͨ��ʬ��ֲ��
							x->stopActionByTag(4);
							x->runAction(x->normalZombieWalkAnimation());
							x->actionTag.insert(1);
						}
					}
					else if (y == 2)
					{
						if (!(std::count(x->actionTag.begin(), x->actionTag.end(), 2)))
						{
							x->stopActionByTag(1);
							x->stopActionByTag(3);
							x->stopActionByTag(4);//��ͷ��ʬ��ֲ��
							x->stopActionByTag(9);
							x->stopActionByTag(10);
							x->stopActionByTag(11);
							x->stopActionByTag(12);
							x->runAction(x->normalZombieNoHeadWalkAnimation());
							x->actionTag.insert(2);
						}
					}
					else if (y == 3)
					{
						if (!(std::count(x->actionTag.begin(), x->actionTag.end(), 3)))
						{
							x->stopActionByTag(1);
							x->stopActionByTag(2);
							x->stopActionByTag(4);
							x->stopActionByTag(13);
							x->runAction(x->normalZombieAttackAnimation());
							x->actionTag.insert(3);
						}
					}
					else if (y == 4)
					{
						if (!(std::count(x->actionTag.begin(), x->actionTag.end(), 4)))
						{
							x->stopActionByTag(1);
							x->stopActionByTag(2);
							x->stopActionByTag(3);
							x->stopActionByTag(9);
							x->stopActionByTag(10);
							x->stopActionByTag(11);
							x->stopActionByTag(12);
							x->stopActionByTag(13);
							x->runAction(x->normalZombieLostHeadAttackAnimation());
							x->actionTag.insert(4);
						}
					}
					else if (y == 5)
					{
						if (!(std::count(x->actionTag.begin(), x->actionTag.end(), 5)))
						{
							x->stopActionByTag(6);
							x->stopActionByTag(7);
							x->stopActionByTag(8);
							x->runAction(x->flagZombieWalkAnimation());
							x->actionTag.insert(5);
						}
					}
					else if (y == 6)
					{
						if (!(std::count(x->actionTag.begin(), x->actionTag.end(), 6)))
						{
							x->stopActionByTag(5);
							x->stopActionByTag(7);
							x->stopActionByTag(8);
							x->runAction(x->flagZombieNoHeadWalkAnimation());
							x->actionTag.insert(6);
						}
					}
					else if (y == 7)
					{
						if (!(std::count(x->actionTag.begin(), x->actionTag.end(), 7)))
						{
							x->stopActionByTag(5);
							x->stopActionByTag(6);
							x->stopActionByTag(8);
							x->stopActionByTag(13);
							x->runAction(x->flagZombieAttackAnimation());
							x->actionTag.insert(7);
						}
					}
					else if (y == 8)
					{
						if (!(std::count(x->actionTag.begin(), x->actionTag.end(), 8)))
						{
							x->stopActionByTag(5);
							x->stopActionByTag(6);
							x->stopActionByTag(7);
							x->stopActionByTag(13);
							x->runAction(x->flagZombieLostHeadAttackAnimation());
							x->actionTag.insert(8);
						}
					}
					else if (y == 9)
					{
						if (!(std::count(x->actionTag.begin(), x->actionTag.end(), 9)))
						{
							x->stopActionByTag(10);
							x->runAction(x->coneheadZombieWalkAnimation());
							x->actionTag.insert(9);
						}
					}
					else if (y == 10)
					{
						if (!(std::count(x->actionTag.begin(), x->actionTag.end(), 10)))
						{
							x->stopActionByTag(9);
							x->stopActionByTag(13);
							x->runAction(x->coneheadZombieAttackAnimation());
							x->actionTag.insert(10);
						}
					}
					else if (y == 11)
					{
						if (!(std::count(x->actionTag.begin(), x->actionTag.end(), 11)))
						{
							x->stopActionByTag(12);
							x->runAction(x->bucketheadZombieWalkAnimation());
							x->actionTag.insert(11);
						}
					}
					else if (y == 12)
					{
						if (!(std::count(x->actionTag.begin(), x->actionTag.end(), 12)))
						{
							x->stopActionByTag(11);
							x->stopActionByTag(13);
							x->runAction(x->bucketheadZombieAttackAnimation()); 
							x->actionTag.insert(12);
						}
					}
					else if (y == 13)
					{
						if (!(std::count(x->actionTag.begin(), x->actionTag.end(), 13)))
						{
							x->stopActionByTag(3);
							x->stopActionByTag(4);
							x->stopActionByTag(7);
							x->stopActionByTag(8);
							x->stopActionByTag(10);
							x->stopActionByTag(12);
							x->runAction(x->zombieMoveWay(x->zombieSpeed));
							x->actionTag.insert(13);
						}
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
						//��ʬֻ���һ��ͷ��֮���14�Ŷ���ɾ��

					}
					else if (y == 15)
					{
						//���ض����������ж�����ͣ��
						x->stopAllActions();
						auto tmpe = x;
						x->runAction(Sequence::createWithTwoActions(x
							->downTheGround(), CallFunc::create([tmpe]() {
								(tmpe)->removeFromParent();//����ʬɾ��
								})));
					}
					else if (y == 16)
					{
						x->stopAllActions();
						auto tmpe = x;
						x->runAction(Sequence::createWithTwoActions(x
							->explodAnimation(), CallFunc::create([tmpe]() {
								(tmpe)->removeFromParent();//����ʬɾ��
								})));
					}
				}
				x->actionTag.clear();
				for (auto y : _taction)
				{
					x->actionTag.insert(y);
				}
				//��14��15��16�Ŷ���ɾ��
				for (auto iter = _taction.begin(); iter != _taction.end();)
				{
					if (*iter == 14 || *iter == 15 || *iter == 16)
					{
						iter = _taction.erase(iter);
					}
					else
					{
						iter++;
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

	this->unschedule(schedule_selector(GameController::remainTimeMinueOneSecond));
	this->unschedule(schedule_selector(GameController::isZombieWin));
	SimpleAudioEngine::getInstance()->stopAllEffects();
	SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	SimpleAudioEngine::getInstance()->playEffect("res/music/winmusic.wma");
	//����ֲ�﷽����Ӯ��
	//ֲ�﷽Ӯ�ͽ�ʬ��Ӯ��ʾ������ͬ��
	(dynamic_cast<GameLayer*>(this->getParent()))->_showSloganLayer->winInSingleMode();
	//Director::getInstance()->pause();
	//ʤ���ˣ���ʾʤ��ͼƬ���˳�����
	//(dynamic_cast<GameLayer*>(this->getParent()))->onExit();
	//(dynamic_cast<GameLayer*>(this->getParent()))->_normalZombieLayer->onExit();
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
		(dynamic_cast<GameLayer*>(this->getParent()))->_showSloganLayer->showZombieEnterYourHome();
		SimpleAudioEngine::getInstance()->playEffect("res/music/losemusic.wma");	
	
	}
	else
	{
		//���ǽ�ʬ��
		SimpleAudioEngine::getInstance()->playEffect("res/music/losemusic.wma");
		(dynamic_cast<GameLayer*>(this->getParent()))->_showSloganLayer->showZombieLose();
	}
	_zombieVectorGlobalVariable.clear();
	_plantVectorGlobalVariable.clear();
	//��ʱ�л��������л���������
		//(dynamic_cast<GameLayer*>(this->getParent()))->onExit();
}
