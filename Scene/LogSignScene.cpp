#pragma once
#include "LogSignScene.h"
#include<iostream>

cocos2d::Scene* LogSignScene::createScene()
{
	return LogSignScene::create();
}

void LogSignScene::callServer(float)
{
	TCPSocket::getInstance()->writeIntoServer("HeartBeat;\n");
	//发送给服务器心跳包
}

bool LogSignScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	this->schedule(schedule_selector(LogSignScene::callServer), 1.f);

	//WSAStartup(MAKEWORD(2, 2), &wsaData);
	//clntSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//memset(&clntAddr, 0, sizeof(clntAddr));  //每个字节都用0填充
	//clntAddr.sin_family = PF_INET;  //使用IPv4地址
	//clntAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	//clntAddr.sin_port = htons(5550);  //端口
	//connect(clntSock, (SOCKADDR*)&clntAddr, sizeof(SOCKADDR));

	//tcp连接
	TCPSocket::getInstance()->connectToServer();

	auto visibleSizeWidth = Director::getInstance()->getVisibleSize().width;
	auto visibleSizeHeight = Director::getInstance()->getVisibleSize().height;

	//add background
	auto bg = Sprite::create("res/CYHres/test2.jpg");
	if (bg == nullptr) 
	{
		CCLOG("titlescreen.jpg wrong!");
	}
	else 
	{
		this->addChild(bg);
		bg->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2));
	}

	//创建蝴蝶动画
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/CYHres/LogSignScene/butterfly/butterfly.plist");

	Sprite* butterflySprite1 = Sprite::createWithSpriteFrameName("timg_1.png");
	butterflySprite1->setPosition(Vec2(visibleSizeWidth / 4 - 20, visibleSizeHeight / 4 * 3));
	this->addChild(butterflySprite1);

	Sprite* butterflySprite2 = Sprite::createWithSpriteFrameName("timg_20.png");
	butterflySprite2->setPosition(Vec2(visibleSizeWidth / 4 * 3 + 170, visibleSizeHeight / 2 - 100));
	this->addChild(butterflySprite2);

	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 30; i++)
	{
		images.pushBack(cache->getSpriteFrameByName(StringUtils::format("timg_%d.png", i)));
	}
	for (int i = 33; i <= 40; i++)
	{
		images.pushBack(cache->getSpriteFrameByName(StringUtils::format("timg_%d.png", i)));
	}
	

	Animation* animation1 = Animation::createWithSpriteFrames(images, 4.f / images.size());
	Animate* animate1 = Animate::create(animation1);
	butterflySprite1->runAction(RepeatForever::create(animate1));
	/*butterflySprite1->runAction(Sequence::createWithTwoActions
	(
		Repeat::create(animate1, 50000),
		CallFunc::create([butterflySprite1]()
	{
		butterflySprite1->removeFromParent();
	})
	));*/

	Animation* animation2 = Animation::createWithSpriteFrames(images, 4.f / images.size());
	Animate* animate2 = Animate::create(animation2);
	butterflySprite2->runAction(RepeatForever::create(animate2));
	/*butterflySprite2->runAction(Sequence::createWithTwoActions
	(
		Repeat::create(animate2, 50000),
		CallFunc::create([butterflySprite2]()
	{
		butterflySprite2->removeFromParent();
	})
	));*/

	//登录和注册面板设计
	auto logBg1 = Sprite::create("res/CYHres/LogSignScene/1.png");
	if (logBg1 == nullptr)
	{
		CCLOG("LogSignScene/1.png wrong!");
	}
	else
	{
		this->addChild(logBg1);
		logBg1->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - visibleSizeHeight / 8));
	}
	auto logBg2 = ui::Button::create("res/CYHres/LogSignScene/2.png");
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
	auto logBg3 = ui::Button::create("res/CYHres/LogSignScene/5.png");
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
		this->addChild(UsernameInput);
		this->addChild(PasswordInput);

		UsernameInput->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - 3));
		UsernameInput->setPlaceHolder("Username");
		UsernameInput->setCursorEnabled(true);
		UsernameInput->setFontSize(24);
		UsernameInput->setColor(Color3B::BLACK);
		UsernameInput->setMaxLengthEnabled(true);
		UsernameInput->setMaxLength(6);
		UsernameInput->ignoreContentAdaptWithSize(false);  //自动换行，使输入从左端开始
		
		PasswordInput->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - visibleSizeHeight / 8 - 3));
		PasswordInput->setPlaceHolder("Password");
		PasswordInput->setCursorEnabled(true);
		PasswordInput->setFontSize(24);
		PasswordInput->setColor(Color3B::BLACK);
		PasswordInput->setMaxLengthEnabled(true);
		PasswordInput->setMaxLength(9);
		PasswordInput->ignoreContentAdaptWithSize(false);  //自动换行，使输入从左端开始
		PasswordInput->setPasswordEnabled(true);
		
		//UsernameInput->addClickEventListener([&](Ref* ref)
		//{
		//		//UsernameInput->setPlaceHolder("");
		//	dynamic_cast<ui::TextField*>(ref)->setString("");
		//});
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

		/*PasswordInput->addClickEventListener([&](Ref* ref)
		{
			dynamic_cast<ui::TextField*>(ref)->setString("");
		});*/
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

	auto LoginBtn = ui::Button::create("res/CYHres/LogSignScene/6.png");
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
			if (username == nullptr || password == nullptr 
				|| username->getString().empty() == true || password->getString().empty() == true) {
				MessageBox("The username or password can not be empty!", "plants");
			}
			else 
			{
				string loginMsg = "LOGIN;";
				loginMsg = loginMsg + username->getString() + ";";
				loginMsg = loginMsg + password->getString() + ";\n";
				TCPSocket::getInstance()->writeIntoServer(loginMsg);
				string isloginSuc;
				while (1) 
				{
					isloginSuc = TCPSocket::getInstance()->readFromServer();
					if (isloginSuc.size() == 0 || isloginSuc == "HeartBeat;")
					{
						log(isloginSuc.c_str());
						continue;
					}
					else 
					{
						log(isloginSuc.c_str());
						break;
					}
				}
				log(isloginSuc.c_str());
				if (isloginSuc == "LOGIN;1;") 
				{
					Director::getInstance()->pushScene(TransitionFade::create(2.f, mainScene::create()));
				}
				else if (isloginSuc == "LOGIN;0;") 
				{
					MessageBox("The username or password is wrong!", "plants");
				}
			}
			
			
			//char sendMsg[20] = { "" };
			//strcat(sendMsg, username->getString().c_str());
			//strcat(sendMsg, "?");
			//strcat(sendMsg, password->getString().c_str());
			//log("sendMsg %s", sendMsg);
			//send(clntSock, sendMsg, strlen(sendMsg) + sizeof(char), NULL);

			////接收服务器传回的数据
			//char szBuffer[MAXBYTE] = { 0 };
			//recv(clntSock, szBuffer, MAXBYTE, NULL);

			////输出接收到的数据
			//log("Message form server: %s", szBuffer);
			//if (strcmp(szBuffer, "LoginFai") == 0) 
			//{
			//	MessageBox("Log in failed", "plants");
			//}
			//if (strcmp(szBuffer, "LoginSuc") == 0) 
			//{
			//	MessageBox("Log in succeed", "plants");
			//}
		});
	}

	
	//关闭套接字
	//closesocket(clntSock);
	//终止使用 DLL
	//WSACleanup();

	return true;
}

