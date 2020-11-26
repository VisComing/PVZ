#include "NormalZombieLayer.h"
#include "../Base/GameLayer.h"
#include "../Base/global.h"
#include "SimpleAudioEngine.h"
#include "../Base/socket.h"
using namespace CocosDenshion;
NormalZombieLayer::NormalZombieLayer()
{
	_normalZombieSprite = NULL;
	this->zombieID = 0;
}
NormalZombieLayer::~NormalZombieLayer()
{

}

bool NormalZombieLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}
	if (_iAmPlantSideGolbalVariable == true && isSinglePlayerGameMode == false)
	{
		this->schedule(schedule_selector(NormalZombieLayer::sendZombieStatus), 0.2f);
	}
	if (_iAmPlantSideGolbalVariable == true || isSinglePlayerGameMode == true)
	{
		this->schedule(schedule_selector(NormalZombieLayer::diedNormalZombie), 0.3f);
	}
	scheduleUpdate();
	return true;
}

//��ʬ����ʬ��ֲ��Ĺ���Ϊ0��

//��ʬ�����½�ʬ
void NormalZombieLayer::initNormalZombieSprite(Vec2 touch, string zombieName)
{
	
	int _zombieDollar = 0;
	//����һ����̬��ʬ��Ϊ������ʱ
	Sprite* _normalZombieStatic;
	Sprite* _normalZombieStaticShadow;
	if (zombieName == "NormalZombie")
	{
		_normalZombieStatic = Sprite::create("res/ZombieStatic.png");
		_normalZombieStaticShadow = Sprite::create("res/ZombieStatic.png");
		_zombieDollar = 100;
	}
	else if (zombieName == "FlagZombie")
	{
		_normalZombieStatic = Sprite::create("res/FlagZombieStatic.png");
		_normalZombieStaticShadow = Sprite::create("res/FlagZombieStatic.png");
		_zombieDollar = 120;
	}
	else if (zombieName == "ConeheadZombie")
	{
		_normalZombieStatic = Sprite::create("res/ConeheadZombieStatic.png");
		_normalZombieStaticShadow = Sprite::create("res/ConeheadZombieStatic.png");
		_zombieDollar = 150;
	}
	else if (zombieName == "BucketheadZombie")
	{
		_normalZombieStatic = Sprite::create("res/BucketheadZombieStatic.png");
		_normalZombieStaticShadow = Sprite::create("res/BucketheadZombieStatic.png");
		_zombieDollar = 175;
	}
	_normalZombieStatic->setPosition(touch);
	_normalZombieStaticShadow->setOpacity(180);
	this->addChild(_normalZombieStaticShadow);
	this->addChild(_normalZombieStatic);
	
	
	auto lis = EventListenerMouse::create();
	//����ƶ�����������ƶ�
	lis->onMouseMove = [=](EventMouse* e) {
		_normalZombieStatic->setPosition(e->getLocation().x, 1200 - e->getLocation().y);
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if ((x > 995 && x < 1100) && (y < 510 && y > 30))
		{
			x = 1045;
			if (y > 30 && y < 129)
				y = 80;
			else if (y < 219)
				y = 175;
			else if (y < 320)
				y = 274;
			else if (y < 419)
				y = 375;
			else if (y < 510)
				y = 475;
		}
		_normalZombieStaticShadow->setPosition(x, y);
		return true;
	};
	//����갴��̧��ʱ�����鱻���£�ͬʱȡ��������
	lis->onMouseDown = [=](EventMouse* e) {
		this->removeChild(_normalZombieStatic);
		this->removeChild(_normalZombieStaticShadow);
		//�ж��н�ʬλ���Ƿ�Ϸ�
		int x = e->getLocation().x;
		int y = 1200 - e->getLocation().y;
		if ((x > 995 && x < 1100) && (y < 510 && y > 30))
		{
			x = 1045;
			if (y > 30 && y < 129)
				y = 80;
			else if (y < 219)
				y = 175;
			else if (y < 320)
				y = 274;
			else if (y < 419)
				y = 375;
			else if (y < 510)
				y = 475;
			//��ʬ�����£�������ͼ
			this->_normalZombieSprite = NormalZombieSprite::create();
			this->_normalZombieSprite->zombieID = ++(this->zombieID);//�˴�Ϊ��ʬID
			this->_normalZombieSprite->setPosition(touch);
			this->addChild(_normalZombieSprite);
			this->_normalZombieSprite->_zombieName = zombieName;
			this->_normalZombieVector.pushBack(this->_normalZombieSprite);//����ʬ��ӵ�������
			_zombieVectorGlobalVariable.pushBack(this->_normalZombieSprite);

			int _random = rand() % 6;
			if(_random == 0)
				SimpleAudioEngine::getInstance()->playEffect("res/music/zombieGroan.wma");
			else if(_random == 1)
				SimpleAudioEngine::getInstance()->playEffect("res/music/zombieGroan2.wma");
			else if(_random == 2)
				SimpleAudioEngine::getInstance()->playEffect("res/music/zombieGroan3.wma");
			else if(_random == 3)
				SimpleAudioEngine::getInstance()->playEffect("res/music/zombieGroan4.wma");
			else if(_random == 4)
				SimpleAudioEngine::getInstance()->playEffect("res/music/zombieGroan5.wma");
			else
				SimpleAudioEngine::getInstance()->playEffect("res/music/zombieGroan6.wma");

			this->_normalZombieSprite->setPosition(x, y + 20);
			//�ڴ˴�����
			if (isSinglePlayerGameMode == false)
			{
				std::string message ="1" + zombieName + ":" + to_string(x) + "," + to_string(y) + ";\n";
				TCPSocket::getInstance()->writeIntoServer(message);
			}
			((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar
				= ((GameLayer*)this->getParent())->_dollarDisplayLayer->_dollar - _zombieDollar;//ÿ����һ����ʬ���Ľ��
			//�˴���Ҫ��runaction������û�н�ʬͼ��

			//�ڴ˴��޸Ľ�ʬ���٣���ʬѪ������ʬ�۸�
			if (zombieName == "NormalZombie")
			{
				this->_normalZombieSprite->zombieMoney = 100;
				if (_iAmPlantSideGolbalVariable == true || isSinglePlayerGameMode == true)
				{
					this->_normalZombieSprite->runAction(this->_normalZombieSprite->normalZombieWalkAnimation());
				}
				//this->_normalZombieSprite->actionTag.push_back(1);
				this->_normalZombieSprite->zombieSpeed = 40;
				this->_normalZombieSprite->_hp = 100;
			}
			else if (zombieName == "FlagZombie")
			{
				this->_normalZombieSprite->zombieMoney = 120;
				if (_iAmPlantSideGolbalVariable == true || isSinglePlayerGameMode == true)
				{
					this->_normalZombieSprite->runAction(this->_normalZombieSprite->flagZombieWalkAnimation());
				}
				//this->_normalZombieSprite->actionTag.push_back(5);
				this->_normalZombieSprite->zombieSpeed = 48;
				this->_normalZombieSprite->_hp = 110;
			}
			else if (zombieName == "ConeheadZombie")
			{
				this->_normalZombieSprite->zombieMoney = 150;
				if (_iAmPlantSideGolbalVariable == true || isSinglePlayerGameMode == true)
				{
					this->_normalZombieSprite->runAction(this->_normalZombieSprite->coneheadZombieWalkAnimation());
				}
				//this->_normalZombieSprite->actionTag.push_back(9);
				this->_normalZombieSprite->zombieSpeed = 55;
				this->_normalZombieSprite->_hp = 120;
			}
			else if (zombieName == "BucketheadZombie")
			{
				this->_normalZombieSprite->zombieMoney = 175;
				if (_iAmPlantSideGolbalVariable == true || isSinglePlayerGameMode == true)
				{
					this->_normalZombieSprite->runAction(this->_normalZombieSprite->bucketheadZombieWalkAnimation());
				}
				//this->_normalZombieSprite->actionTag.push_back(11);
				this->_normalZombieSprite->zombieSpeed = 62;
				this->_normalZombieSprite->_hp = 130;
			}
			this->_normalZombieSprite->_zombieName = zombieName;
			if (_iAmPlantSideGolbalVariable == true || isSinglePlayerGameMode == true)
			{
				this->_normalZombieSprite->runAction(this->_normalZombieSprite->zombieMoveWay(this->_normalZombieSprite->zombieSpeed));
			}
			//this->_normalZombieSprite->actionTag.push_back(13);
		}
		else
		{
			//this->removeChild(_normalZombieSprite);
		}
		_eventDispatcher->removeEventListener(lis);
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(lis, this);
}

//��ʬ���ڽ�ʬ��Ȼ����������͸�ֲ�﷽
void NormalZombieLayer::autoInitZombie(string zombieName, Vec2 position)
{
	this->_normalZombieSprite = NormalZombieSprite::create();
	this->_normalZombieSprite->setPosition(position);
	this->addChild(_normalZombieSprite);
	const int _random = rand() % 6;
	if (_random == 0)
		SimpleAudioEngine::getInstance()->playEffect("res/music/zombieGroan.wma");
	else if (_random == 1)
		SimpleAudioEngine::getInstance()->playEffect("res/music/zombieGroan2.wma");
	else if (_random == 2)
		SimpleAudioEngine::getInstance()->playEffect("res/music/zombieGroan3.wma");
	else if (_random == 3)
		SimpleAudioEngine::getInstance()->playEffect("res/music/zombieGroan4.wma");
	else if (_random == 4)
		SimpleAudioEngine::getInstance()->playEffect("res/music/zombieGroan5.wma");
	else
		SimpleAudioEngine::getInstance()->playEffect("res/music/zombieGroan6.wma");
	this->_normalZombieVector.pushBack(this->_normalZombieSprite);//����ʬ��ӵ�������
	this->_normalZombieSprite->zombieID = ++(this->zombieID);//�˴�Ϊ��ʬID
	_zombieVectorGlobalVariable.pushBack(this->_normalZombieSprite);


	const int x = position.x;
	const int y = position.y;

	this->_normalZombieSprite->setPosition(x, y + 20);
	//�˴���Ҫ��runaction������û�н�ʬͼ��

	//�ڴ˴��޸Ľ�ʬ���٣���ʬѪ������ʬ�۸�
	if (zombieName == "NormalZombie")
	{
		this->_normalZombieSprite->zombieMoney = 100;
		this->_normalZombieSprite->runAction(this->_normalZombieSprite->normalZombieWalkAnimation());
		this->_normalZombieSprite->actionTag.insert(1);
		this->_normalZombieSprite->zombieSpeed = 40;
		this->_normalZombieSprite->_hp = 100;
	}
	else if (zombieName == "FlagZombie")
	{
		this->_normalZombieSprite->zombieMoney = 120;
		this->_normalZombieSprite->runAction(this->_normalZombieSprite->flagZombieWalkAnimation());
		this->_normalZombieSprite->actionTag.insert(5);
		this->_normalZombieSprite->zombieSpeed = 48;
		this->_normalZombieSprite->_hp = 110;
	}
	else if (zombieName == "ConeheadZombie")
	{
		this->_normalZombieSprite->zombieMoney = 150;
		this->_normalZombieSprite->runAction(this->_normalZombieSprite->coneheadZombieWalkAnimation());
		this->_normalZombieSprite->actionTag.insert(9);
		this->_normalZombieSprite->zombieSpeed = 55;
		this->_normalZombieSprite->_hp = 120;
	}
	else if (zombieName == "BucketheadZombie")
	{
		this->_normalZombieSprite->zombieMoney = 175;
		this->_normalZombieSprite->runAction(this->_normalZombieSprite->bucketheadZombieWalkAnimation());
		this->_normalZombieSprite->actionTag.insert(11);
		this->_normalZombieSprite->zombieSpeed = 62;
		this->_normalZombieSprite->_hp = 130;
	}
	this->_normalZombieSprite->_zombieName = zombieName;
	this->_normalZombieSprite->runAction(this->_normalZombieSprite->zombieMoveWay(this->_normalZombieSprite->zombieSpeed));
	this->_normalZombieSprite->actionTag.insert(13);
}

bool NormalZombieLayer::isZombieWin()
{
	
	for (auto i = _zombieVectorGlobalVariable.begin(); i != _zombieVectorGlobalVariable.end(); i++)
	{
		if ((*i)->getPositionX() < 170)//��ʬ�����԰����ʬʤ��
		{
			if (isSinglePlayerGameMode == true)
			{
				((GameLayer*)this->getParent())->_showSloganLayer->showZombieEnterYourHome();
				//SimpleAudioEngine::getInstance()->stopAllEffects();
				//SimpleAudioEngine::getInstance()->stopBackgroundMusic();
				//SimpleAudioEngine::getInstance()->playEffect("res/music/losemusic.wma");
				//��ʱ�л��������л���������
				//((GameLayer*)this->getParent())->onExit();
			}
			else if (_iAmPlantSideGolbalVariable == false && isSinglePlayerGameMode == false)//����ģʽ��ʬ����ʤ��
			{
				TCPSocket::getInstance()->writeIntoServer("WIN;\n");//����ʤ����Ϣ
			}
			//else//��ʬ����ʾʤ��
			//{
			//	SimpleAudioEngine::getInstance()->stopAllEffects();
			//	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			//	SimpleAudioEngine::getInstance()->playEffect("res/music/winmusic.wma");
			//	((GameLayer*)this->getParent())->_showSloganLayer->winInSingleMode();
			//	
			//}
			return true;
		}
	}
	return false;
}



void NormalZombieLayer::diedNormalZombie(float)
{
	for (auto i = _normalZombieVector.begin(); i != _normalZombieVector.end();)
	{
		
		//ע���ʱ��ʬ��ͷ��ֵ��һ������ɢ��ֵ��������С�ڵ��ڡ����ڵ���
		if ((*i)->_hp == 20 || (*i)->_hp == 10 || (*i)->_hp == 15)//��ʱ��ʬͷ����
		{
			(*i)->stopAllActions();
			(*i)->actionTag.clear();
			if ((*i)->_zombieName == "NormalZombie" || (*i)->_zombieName == "ConeheadZombie" || (*i)->_zombieName == "BucketheadZombie")
			{
				(*i)->runAction((*i)->normalZombieNoHeadWalkAnimation());
				(*i)->actionTag.insert(2);
			}
				
			else if ((*i)->_zombieName == "FlagZombie")
			{
				(*i)->runAction((*i)->flagZombieNoHeadWalkAnimation());
				(*i)->actionTag.insert(6);
			}
			(*i)->runAction((*i)->zombieMoveWay((*i)->zombieSpeed));
			(*i)->actionTag.insert(13);
			//(*i)->runAction(Spawn::create((*i)->noHeadAnimation(),(*i)->normalZombieMoveWay(), NULL));
			auto tmpSprite = Sprite::create();
			this->addChild(tmpSprite);
			tmpSprite->setPosition((*i)->getPosition());
			//�õ�ͷ�Ķ�����ǰһ�㣬���Ե���ʵ
			tmpSprite->setPositionX(tmpSprite->getPositionX() + 35);

			//ע�⣬Ϊ��ʹ��ʬֻ��һ��ͷ������ѽ�ʬ��Ѫ����һ
			(*i)->_hp -= 1;
			//tmpSprite->runAction((*i)->headAnimation());
			tmpSprite->runAction(Sequence::createWithTwoActions((*i)
				->headAnimation(), CallFunc::create([tmpSprite]() {
						tmpSprite->removeFromParent(); 
					})));
			(*i)->actionTag.insert(14);
		}

		if ((*i)->_hp <= 0)
		{
			(*i)->stopMusic();
			//��ȫ����ʬ�����н���ɾ��
			for (auto j = _zombieVectorGlobalVariable.begin(); j != _zombieVectorGlobalVariable.end(); j++)
			{
				if ((*i) == (*j))
				{
					//��ʱ��ʬ����
					//1ZombieDie:ID,typeOfDeath;\n
					const string _message = "1ZombieDie:" + to_string((*i)->zombieID) + "," + to_string((*i)->typeOfDeath) + ";\n";
					TCPSocket::getInstance()->writeIntoServer(_message);
					_zombieVectorGlobalVariable.erase(j);
					break;
				}
			}
			(*i)->stopAllActions();
			(*i)->actionTag.clear();
			auto tmp = *i;
			//ԭ�������е����⣬��ִ�ж�����Ȼ��ִ��lambda���ʽ��ִ�е�lamidaʱ�����i�Ѿ���ɾ����
			//2020/11/15�賿
			if ((*i)->typeOfDeath == 0)//��ʬ���ӵ�����
			{
				(*i)->runAction(Sequence::createWithTwoActions((*i)
					->downTheGround(), CallFunc::create([tmp]() {
						(tmp)->removeFromParent();//����ʬɾ��
						})));
				(*i)->actionTag.clear();
				(*i)->actionTag.insert(15);
				log("insert 15");
			}
			else if ((*i)->typeOfDeath == 1)//��ʬ��ը��
			{
				(*i)->runAction(Sequence::createWithTwoActions((*i)
					-> explodAnimation(), CallFunc::create([tmp]() {
						(tmp)->removeFromParent();//����ʬɾ��
						})));
				(*i)->actionTag.clear();
				(*i)->actionTag.insert(16);
			}
			else if ((*i)->typeOfDeath == 2)//��ʳ�˻��Ե�
			{
				(*i)->actionTag.clear();
				(*i)->removeFromParent();
			}
			//ע�⣬��һ��Ҫ���ڸ�ѭ�������в����������֮ǰɾ���ˣ���ô��������Ҫʹ��������ô����
			i = _normalZombieVector.erase(i);
		}
		else
		{
			i++;
		}
	}
}

void NormalZombieLayer::normalZombieAttackPlant()
{
	for (auto i = _zombieVectorGlobalVariable.begin(); i != _zombieVectorGlobalVariable.end(); i++)
	{
		
		if ((*i)->_hp > 0)
		{
			
			for (auto j = _plantVectorGlobalVariable.begin(); j != _plantVectorGlobalVariable.end(); j++)
			{
				if ((*j)->plantBounding().intersectsRect((*i)->zombieBounding()))//�����ײ
				{
					
					(*j)->_plantHP -= 1;
					if ((*i)->getNumberOfRunningActions() != 1)
					{
						(*i)->startMusic();
						(*i)->stopAllActions();
						(*i)->actionTag.clear();
						if ((*i)->_hp >= 20)//ע���ͷʱ��Ѫ��2020/11/18
						{
							if ((*i)->_zombieName == "NormalZombie")
							{
								(*i)->runAction((*i)->normalZombieAttackAnimation());
								(*i)->actionTag.insert(3);
							}
							else if ((*i)->_zombieName == "FlagZombie")
							{
								(*i)->runAction((*i)->flagZombieAttackAnimation());
								(*i)->actionTag.insert(7);
							}
							else if ((*i)->_zombieName == "ConeheadZombie")
							{
								(*i)->runAction((*i)->coneheadZombieAttackAnimation());
								(*i)->actionTag.insert(10);
							}
							else if ((*i)->_zombieName == "BucketheadZombie")
							{
								(*i)->runAction((*i)->bucketheadZombieAttackAnimation());
								(*i)->actionTag.insert(12);
							}
						}
						else
						{
							if ((*i)->_zombieName == "NormalZombie" || (*i)->_zombieName == "ConeheadZombie" || (*i)->_zombieName == "BucketheadZombie")
							{
								(*i)->runAction((*i)->normalZombieLostHeadAttackAnimation());
								(*i)->actionTag.insert(4);
							}
							else if ((*i)->_zombieName == "FlagZombie")
							{
								(*i)->runAction((*i)->flagZombieLostHeadAttackAnimation());
								(*i)->actionTag.insert(8);
							}
						}
					}
				}
			}
			bool flag = false;
			for (auto x : _plantVectorGlobalVariable)
			{
				if (x->plantBounding().intersectsRect((*i)->zombieBounding()))
				{
					flag = true;
					break;
				}
			}
			if ((*i)->getNumberOfRunningActions() == 1 && flag == false)
			{
				(*i)->stopMusic();
				(*i)->stopAllActions();
				(*i)->actionTag.clear();
				if ((*i)->_hp > 20)//ע�⽩ʬ��ͷʱ��Ѫ����2020/11/18
				{
					if ((*i)->_zombieName == "NormalZombie")
					{
						(*i)->runAction((*i)->normalZombieWalkAnimation());//11/16�޸��˴˴���û��Ҫ��repeatforever create
						(*i)->actionTag.insert(1);
					}
					else if ((*i)->_zombieName == "FlagZombie")
					{
						(*i)->runAction((*i)->flagZombieWalkAnimation());
						(*i)->actionTag.insert(5);
					}
					else if ((*i)->_zombieName == "ConeheadZombie")
					{
						(*i)->runAction((*i)->coneheadZombieWalkAnimation());
						(*i)->actionTag.insert(9);
					}
					else if ((*i)->_zombieName == "BucketheadZombie")
					{
						(*i)->runAction((*i)->bucketheadZombieWalkAnimation());
						(*i)->actionTag.insert(11);
					}
				}
				else
				{
					if ((*i)->_zombieName == "NormalZombie" || (*i)->_zombieName == "ConeheadZombie" || (*i)->_zombieName == "BucketheadZombie")
					{
						(*i)->runAction((*i)->normalZombieNoHeadWalkAnimation());
						(*i)->actionTag.insert(2);
					}
					else if ((*i)->_zombieName == "FlagZombie")
					{
						(*i)->runAction((*i)->flagZombieNoHeadWalkAnimation());
						(*i)->actionTag.insert(6);
					}
				}
				(*i)->runAction((*i)->zombieMoveWay((*i)->zombieSpeed));
				(*i)->actionTag.insert(13);
			}
		}
	}

}

void NormalZombieLayer::sendZombieStatus(float)
{
	for (auto x : _zombieVectorGlobalVariable)
	{
		string message = "2";
		message += x->_zombieName + ":" + to_string(x->getPositionX()) + "," + to_string(x->getPositionY())
			+ "," + to_string(x->zombieID) + ",";
		bool flag = false;
		for (auto y : x->actionTag)
		{
			flag = true;
			message += (to_string(y) + ",");
		}
		message.at(message.size() - 1) = ';';
		message += "\n";
		log(message.c_str());
		if (flag == true)
		{
			TCPSocket::getInstance()->writeIntoServer(message);
		}
		x->actionTag.erase(14);//ɾȥ��ͷ����
		//x->actionTag.erase(15);
		x->actionTag.erase(16);
	}
}

void NormalZombieLayer::delectZombieFromNormalZombieVector(int _ID)
{
	for (auto iter = _normalZombieVector.begin(); iter != _normalZombieVector.end(); iter++)
	{
		if ((*iter)->zombieID == _ID)
		{
			_normalZombieVector.erase(iter);
			break;
		}
	}
}

void NormalZombieLayer::update(float dt)
{
	//����ǽ�ʬ�����������κμ���
	if (_iAmPlantSideGolbalVariable == true  || isSinglePlayerGameMode == true)
	{
		//this->diedNormalZombie();
		this->normalZombieAttackPlant();
	}
	//ֲ�﷽��ʬ�����ͽ�ʬ��״̬��Ϣ
	/*if (_iAmPlantSideGolbalVariable == true && isSinglePlayerGameMode == false)
	{
		this->sendZombieStatus();
	}*/
	/*if (isSinglePlayerGameMode == true)
	{
		this->isZombieWin();
	}*/
}
