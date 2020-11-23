#pragma once
#include "LogSignScene.h"
#include<iostream>

cocos2d::Scene* LogSignScene::createScene()
{
	return LogSignScene::create();
}

void LogSignScene::callServer(float)
{
	log("HeartBeat;\n");
	//���͸�������������
}

bool LogSignScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	this->schedule(schedule_selector(LogSignScene::callServer), 3.f);

	//WSAStartup(MAKEWORD(2, 2), &wsaData);
	//clntSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//memset(&clntAddr, 0, sizeof(clntAddr));  //ÿ���ֽڶ���0���
	//clntAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	//clntAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
	//clntAddr.sin_port = htons(5550);  //�˿�
	//connect(clntSock, (SOCKADDR*)&clntAddr, sizeof(SOCKADDR));

	//tcp����
	TCPSocket::getInstance()->connectToServer();

	auto visibleSizeWidth = Director::getInstance()->getVisibleSize().width;
	auto visibleSizeHeight = Director::getInstance()->getVisibleSize().height;

	//add background
	auto bg = Sprite::create("test2.jpg");
	if (bg == nullptr) 
	{
		CCLOG("titlescreen.jpg wrong!");
	}
	else 
	{
		this->addChild(bg);
		bg->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2));
	}

	//������������
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("LogSignScene/butterfly/butterfly.plist");

	Sprite* butterflySprite1 = Sprite::createWithSpriteFrameName("timg_1.png");
	butterflySprite1->setPosition(Vec2(visibleSizeWidth / 4 - 20, visibleSizeHeight / 4 * 3));
	this->addChild(butterflySprite1);

	Sprite* butterflySprite2 = Sprite::createWithSpriteFrameName("timg_20.png");
	butterflySprite2->setPosition(Vec2(visibleSizeWidth / 4 * 3 + 170, visibleSizeHeight / 2 - 100));
	this->addChild(butterflySprite2);

	Vector<SpriteFrame*> images;
	images.pushBack(cache->getSpriteFrameByName("timg_1.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_2.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_3.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_4.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_5.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_6.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_7.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_8.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_9.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_10.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_11.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_12.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_13.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_14.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_15.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_16.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_17.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_18.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_19.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_20.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_21.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_22.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_23.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_24.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_25.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_26.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_27.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_28.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_29.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_30.png"));
	//images.pushBack(cache->getSpriteFrameByName("timg_31.png"));
	//images.pushBack(cache->getSpriteFrameByName("timg_32.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_33.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_34.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_35.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_36.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_37.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_38.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_39.png"));
	images.pushBack(cache->getSpriteFrameByName("timg_40.png"));

	Animation* animation1 = Animation::createWithSpriteFrames(images, 4.f / images.size());
	Animate* animate1 = Animate::create(animation1);
	//matchSprite->runAction(RepeatForever::create(animate));
	butterflySprite1->runAction(Sequence::createWithTwoActions
	(
		Repeat::create(animate1, 50000),
		CallFunc::create([butterflySprite1]()
	{
		butterflySprite1->removeFromParent();
	})
	));

	Animation* animation2 = Animation::createWithSpriteFrames(images, 4.f / images.size());
	Animate* animate2 = Animate::create(animation2);
	butterflySprite2->runAction(Sequence::createWithTwoActions
	(
		Repeat::create(animate2, 50000),
		CallFunc::create([butterflySprite2]()
	{
		butterflySprite2->removeFromParent();
	})
	));

	//��¼��ע��������
	auto logBg1 = Sprite::create("LogSignScene/1.png");
	if (logBg1 == nullptr)
	{
		CCLOG("LogSignScene/1.png wrong!");
	}
	else
	{
		this->addChild(logBg1);
		logBg1->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - visibleSizeHeight / 8));
	}
	auto logBg2 = ui::Button::create("LogSignScene/2.png");
	if (logBg2 == nullptr)
	{
		CCLOG("LogSignScene/2.png wrong!");
	}
	else
	{
		this->addChild(logBg2);
		logBg2->setPosition(Vec2(visibleSizeWidth / 2 - 78, visibleSizeHeight / 2 + visibleSizeHeight / 8 + 38));
		logBg2->addClickEventListener([&](Ref* ref) 
		{
			Director::getInstance()->replaceScene(LogSignScene::create());
		});

	}
	auto logBg3 = ui::Button::create("LogSignScene/5.png");
	if (logBg3 == nullptr)
	{
		CCLOG("LogSignScene/5.png wrong!");
	}
	else
	{
		this->addChild(logBg3);
		logBg3->setPosition(Vec2(visibleSizeWidth / 2 + 72, visibleSizeHeight / 2 + visibleSizeHeight / 8 + 40));
		logBg3->addClickEventListener([&](Ref* ref) 
		{
			Director::getInstance()->replaceScene(SignupScene::create());
		});

	}
	//add UsernameInput and PasswordInput
	auto UsernameInput = ui::TextField::create();
	auto PasswordInput = ui::TextField::create();
	if (UsernameInput == nullptr || PasswordInput == nullptr)
	{
		CCLOG("UsernameInput and PasswordInput wrong!");
	}
	else
	{
		addChild(UsernameInput);
		addChild(PasswordInput);

		UsernameInput->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - 3));
		UsernameInput->setPlaceHolder("Username");
		UsernameInput->setFontSize(24);
		UsernameInput->setColor(Color3B::BLACK);
		UsernameInput->setMaxLengthEnabled(true);
		UsernameInput->setMaxLength(6);
		UsernameInput->ignoreContentAdaptWithSize(false);  //�Զ����У�ʹ�������˿�ʼ

		PasswordInput->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - visibleSizeHeight / 8 - 3));
		PasswordInput->setPlaceHolder("Password");
		PasswordInput->setFontSize(24);
		PasswordInput->setColor(Color3B::BLACK);
		PasswordInput->setMaxLengthEnabled(true);
		PasswordInput->setMaxLength(9);
		PasswordInput->ignoreContentAdaptWithSize(false);  //�Զ����У�ʹ�������˿�ʼ
		PasswordInput->setPasswordEnabled(true);

		/*UsernameInput->addClickEventListener([&](Ref* ref)
		{
			dynamic_cast<ui::TextField*>(ref)->setString("");
		});*/
		UsernameInput->addEventListener([&](Ref* ref, ui::TextField::EventType type) 
		{
			if (type == ui::TextField::EventType::INSERT_TEXT) 
			{
				username = dynamic_cast<ui::TextField*>(ref);

				log("%s", username->getString().c_str());

				//username must only includes English words
				for (char c : username->getString()) 
				{
					if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) 
					{
						username->setString("");
						log("please input English words!");
						break;
					}
				}

			}
		});

		PasswordInput->addClickEventListener([&](Ref* ref)
		{
			dynamic_cast<ui::TextField*>(ref)->setString("");
		});
		PasswordInput->addEventListener([&](Ref* ref, ui::TextField::EventType type) 
		{
			if (type == ui::TextField::EventType::INSERT_TEXT) 
			{
				password = dynamic_cast<ui::TextField*>(ref);

				log("%s", password->getString().c_str());

				//username must only includes English words
				for (char c : password->getString()) 
				{
					if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) 
					{
						password->setString("");
						log("please input English words and numbers!");
						break;
					}
				}
			}
		});
	}

	auto LoginBtn = ui::Button::create("LogSignScene/6.png");
	if (LoginBtn == nullptr)
	{
		log("LoginBtn wrong!");
	}
	else
	{
		addChild(LoginBtn);

		LoginBtn->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 5 - 20));
		LoginBtn->addClickEventListener([&](Ref* ref)
		{
			TCPSocket::getInstance()->writeIntoServer("cyhhh?123456");
			/*string a = TCPSocket::getInstance()->readFromServer();
			log(a.c_str());
			while (a.size() == 0) {
				log("111111");
				a = TCPSocket::getInstance()->readFromServer();
			}
			log(a.c_str());*/
			string a;
			while (1) {
				a = TCPSocket::getInstance()->readFromServer();
				if (a.empty() == false) {
					break;
				}
			}
			log(a.c_str());
			
			//char sendMsg[20] = { "" };
			//strcat(sendMsg, username->getString().c_str());
			//strcat(sendMsg, "?");
			//strcat(sendMsg, password->getString().c_str());
			//log("sendMsg %s", sendMsg);
			//send(clntSock, sendMsg, strlen(sendMsg) + sizeof(char), NULL);

			////���շ��������ص�����
			//char szBuffer[MAXBYTE] = { 0 };
			//recv(clntSock, szBuffer, MAXBYTE, NULL);

			////������յ�������
			//log("Message form server: %s", szBuffer);
			//if (strcmp(szBuffer, "LoginFai") == 0) 
			//{
			//	MessageBox("Log in failed", "plants");
			//}
			//if (strcmp(szBuffer, "LoginSuc") == 0) 
			//{
			//	MessageBox("Log in succeed", "plants");
				Director::getInstance()->pushScene(TransitionFade::create(2.f, mainScene::create()));
			//}
		});
	}

	
	//�ر��׽���
	//closesocket(clntSock);
	//��ֹʹ�� DLL
	//WSACleanup();

	return true;
}

