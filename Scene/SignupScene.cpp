#pragma once
#include "SignupScene.h"

cocos2d::Scene* SignupScene::createScene()
{
	return SignupScene::create();
}

bool SignupScene::init()
{
	this->schedule(schedule_selector(LogSignScene::callServer), 0.5f);

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	clntSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&clntAddr, 0, sizeof(clntAddr));  //每个字节都用0填充
	clntAddr.sin_family = PF_INET;  //使用IPv4地址
	clntAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	clntAddr.sin_port = htons(5550);  //端口
	connect(clntSock, (SOCKADDR*)&clntAddr, sizeof(SOCKADDR));

	if (!Scene::init())
	{
		return false;
	}

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

	//创建蝴蝶动画
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

	//登录和注册面板设计
	auto logBg1 = Sprite::create("LogSignScene/8.png");
	if (logBg1 == nullptr)
	{
		CCLOG("LogSignScene/1.png wrong!");
	}
	else
	{
		this->addChild(logBg1);
		logBg1->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - visibleSizeHeight / 8));
	}
	auto logBg2 = ui::Button::create("LogSignScene/3.png");
	if (logBg2 == nullptr)
	{
		CCLOG("LogSignScene/2.png wrong!");
	}
	else
	{
		this->addChild(logBg2);
		logBg2->setPosition(Vec2(visibleSizeWidth / 2 - 78, visibleSizeHeight / 2 + visibleSizeHeight / 8 + 38));
		logBg2->addClickEventListener([&](Ref* ref) {
			Director::getInstance()->replaceScene(LogSignScene::create());
		});

	}
	auto logBg3 = ui::Button::create("LogSignScene/4.png");
	if (logBg3 == nullptr)
	{
		CCLOG("LogSignScene/5.png wrong!");
	}
	else
	{
		this->addChild(logBg3);
		logBg3->setPosition(Vec2(visibleSizeWidth / 2 + 72, visibleSizeHeight / 2 + visibleSizeHeight / 8 + 40));
		logBg3->addClickEventListener([&](Ref* ref) {
			Director::getInstance()->replaceScene(SignupScene::create());
		});

	}

	//add UsernameInput and PasswordInput
	auto UsernameInput = ui::TextField::create();
	auto PasswordInput = ui::TextField::create();
	auto PasswordInput2 = ui::TextField::create();
	if (UsernameInput == nullptr || PasswordInput == nullptr)
	{
		CCLOG("UsernameInput and PasswordInput wrong!");
	}
	else
	{
		addChild(UsernameInput);
		addChild(PasswordInput);
		addChild(PasswordInput2);

		UsernameInput->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 + 20));
		UsernameInput->setPlaceHolder("Username");
		UsernameInput->setFontSize(24);
		UsernameInput->setColor(Color3B::BLACK);
		UsernameInput->setMaxLengthEnabled(true);
		UsernameInput->setMaxLength(6);
		UsernameInput->ignoreContentAdaptWithSize(false);  //自动换行，使输入从左端开始

		PasswordInput->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - visibleSizeHeight / 8 + 20));
		PasswordInput->setPlaceHolder("Password");
		PasswordInput->setFontSize(24);
		PasswordInput->setColor(Color3B::BLACK);
		PasswordInput->setMaxLengthEnabled(true);
		PasswordInput->setMaxLength(9);
		PasswordInput->ignoreContentAdaptWithSize(false);  //自动换行，使输入从左端开始
		PasswordInput->setPasswordEnabled(true);

		PasswordInput2->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - visibleSizeHeight / 4 + 25));
		PasswordInput2->setPlaceHolder("Password");
		PasswordInput2->setFontSize(24);
		PasswordInput2->setColor(Color3B::BLACK);
		PasswordInput2->setMaxLengthEnabled(true);
		PasswordInput2->setMaxLength(9);
		PasswordInput2->ignoreContentAdaptWithSize(false);  //自动换行，使输入从左端开始
		PasswordInput2->setPasswordEnabled(true);

		/*UsernameInput->addClickEventListener([&](Ref* ref)
		{
			dynamic_cast<ui::TextField*>(ref)->setString("");
		});*/
		UsernameInput->addEventListener([&](Ref* ref, ui::TextField::EventType type) {
			if (type == ui::TextField::EventType::INSERT_TEXT) {
				username = dynamic_cast<ui::TextField*>(ref);

				log("%s", username->getString().c_str());

				//username must only includes English words
				for (char c : username->getString()) {
					if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) {
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
		PasswordInput->addEventListener([&](Ref* ref, ui::TextField::EventType type) {
			if (type == ui::TextField::EventType::INSERT_TEXT) {
				password = dynamic_cast<ui::TextField*>(ref);

				log("%s", password->getString().c_str());

				//username must only includes English words
				for (char c : password->getString()) {
					if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) {
						password->setString("");
						log("please input English words and numbers!");
						break;
					}
				}
			}
		});

		PasswordInput2->addEventListener([&](Ref* ref, ui::TextField::EventType type) {
			if (type == ui::TextField::EventType::INSERT_TEXT) {
				password2 = dynamic_cast<ui::TextField*>(ref);

				log("%s", password2->getString().c_str());

				//username must only includes English words
				for (char c : password2->getString()) {
					if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) {
						password2->setString("");
						log("please input English words and numbers!");
						break;
					}
				}
			}
		});
	}

	//add login and signup button
	auto SignupBtn = ui::Button::create("LogSignScene/7.png");
	if (SignupBtn == nullptr)
	{
		log("LoginBtn and SignupBtn wrong!");
	}
	else
	{
		addChild(SignupBtn);
		SignupBtn->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 5 - 20));
		SignupBtn->addClickEventListener([&](Ref* ref) {
			/*if (username->getString() == "Username:") {
				MessageBox("The username cannot be empty", "plants");
			}*/
			//else if (password->getString() == "" || password2->getString() == "") {
			//	MessageBox("The password cannot be empty", "plants");
			//}
			if (strcmp(password->getString().c_str(), password2->getString().c_str()) == 0) {
				log("SignupBtn clicked!");
				char sendMsg[20] = { "" };
				strcat(sendMsg, username->getString().c_str());
				strcat(sendMsg, "+");
				strcat(sendMsg, password->getString().c_str());
				log("sendMsg %s", sendMsg);
				send(clntSock, sendMsg, strlen(sendMsg) + sizeof(char), NULL);

				//接收服务器传回的数据
				char szBuffer[MAXBYTE] = { 0 };
				recv(clntSock, szBuffer, MAXBYTE, NULL);

				//输出接收到的数据
				log("Message form server: %s", szBuffer);
				if (strcmp(szBuffer, "SignupFai") == 0) {
					MessageBox("Sign up failed", "plants");
				}
				if (strcmp(szBuffer, "SignupSuc") == 0) {
					MessageBox("Sign up succeed", "plants");
					Director::getInstance()->replaceScene(LogSignScene::create());
				}
			}
			//else {
			//	MessageBox("The passwords entered two times do not match", "plants");
			//}
		});
	}
	
	
	////创建帧动画
	//auto cache = SpriteFrameCache::getInstance();
	//cache->addSpriteFramesWithFile("test.plist");
	//Sprite* matchSprite = Sprite::createWithSpriteFrameName("maching2.png");
	//matchSprite->setPosition(Vec2(visibleSizeWidth / 4, visibleSizeHeight / 4));
	//this->addChild(matchSprite);

	////创建精灵帧集合
	//Vector<SpriteFrame*> images;
	//images.pushBack(cache->getSpriteFrameByName("maching2.png"));
	//images.pushBack(cache->getSpriteFrameByName("matching1.png"));

	////创建动画对象
	//Animation* animation = Animation::createWithSpriteFrames(images, 1.f / images.size());
	//Animate* animate = Animate::create(animation);

	//matchSprite->runAction(RepeatForever::create(animate));

	/*vampireSprite->runAction(Sequence::createWithTwoActions(
		Repeat::create(animate, 3),
		CallFunc::create([vampireSprite]() {
			vampireSprite->removeFromParent();
		})
	));*/

	//关闭套接字
	//closesocket(clntSock);
	//终止使用 DLL
	//WSACleanup();
	  
	return true;
}
