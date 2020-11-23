#pragma once
#include "mainScene.h"
#include "../Base/GameScene.h"
#include "../Base/global.h"
cocos2d::Scene* mainScene::createScene()
{
	return mainScene::create();
}

bool mainScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	this->schedule(schedule_selector(LogSignScene::callServer), 0.5f);

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	clntSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&clntAddr, 0, sizeof(clntAddr));  //每个字节都用0填充
	clntAddr.sin_family = PF_INET;  //使用IPv4地址
	clntAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	clntAddr.sin_port = htons(5550);  //端口
	connect(clntSock, (SOCKADDR*)&clntAddr, sizeof(SOCKADDR));

	auto visibleSizeWidth = Director::getInstance()->getVisibleSize().width;
	auto visibleSizeHeight = Director::getInstance()->getVisibleSize().height;

	//add background
	auto bgSky = Sprite::create("res/CYHres/Store_Background.jpg");
	if (bgSky == nullptr)
	{
		CCLOG("Store_Background.jpg wrong!");
	}
	else
	{
		this->addChild(bgSky);
		bgSky->setPosition(Vec2(visibleSizeWidth / 2 - 500, visibleSizeHeight / 2 ));
	}

	auto bgHouse = Sprite::create("res/CYHres/SelectorScreen_BG_Center.png");
	if (bgHouse == nullptr)
	{
		CCLOG("titlescreen.jpg wrong!");
	}
	else
	{
		this->addChild(bgHouse);
		bgHouse->setPosition(Vec2(visibleSizeWidth / 2 - 50, visibleSizeHeight / 2 - 130));
	}

	auto bgTree = Sprite::create("res/CYHres/SelectorScreen_BG_Left.png");
	if (bgTree == nullptr)
	{
		CCLOG("SelectorScreen_BG_Left.png wrong!");
	}
	else
	{
		this->addChild(bgTree);
		bgTree->setPosition(Vec2(visibleSizeWidth / 5 - 5, visibleSizeHeight / 2 ));
	}

	//add challange choice background and button
	auto stele = Sprite::create("res/CYHres/SelectorScreen_BG_Right1.png");
	if (stele == nullptr)
	{
		CCLOG("SelectorScreen_BG_Right1.jpg wrong!");
	}
	else
	{
		this->addChild(stele);
		stele->setPosition(Vec2(visibleSizeWidth / 8 * 7 - 175, visibleSizeHeight / 4 + 118));
	}

	auto aiBtn = ui::Button::create("res/CYHres/aiChallengeBtn.png");
	addChild(aiBtn);
	aiBtn->setPosition(Vec2(visibleSizeWidth / 8 * 7 - 50, visibleSizeHeight / 4 + 270));
	aiBtn->addClickEventListener([&](Ref* ref) {
		//单机模式
		isSinglePlayerGameMode = true;
		Director::getInstance()->pushScene(GameScene::create());
	});

	auto pkBtn = ui::Button::create("res/CYHres/matchChallengeBtn.png");
	addChild(pkBtn);
	pkBtn->setPosition(Vec2(visibleSizeWidth / 8 * 7 - 50, visibleSizeHeight / 4 + 165));
	pkBtn->addClickEventListener([&](Ref* ref) {

		Director::getInstance()->pushScene(TransitionSlideInR::create(0.3f, matchScene::create()));
	});

	//创建僵尸动画
	//1
	auto cache1 = SpriteFrameCache::getInstance();
	cache1->addSpriteFramesWithFile("res/CYHres/mainScene/FlagZombie/FlagZombie.plist");

	Sprite* FlagZombie = Sprite::createWithSpriteFrameName("FlagZombie_1.png");
	FlagZombie->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 4));
	this->addChild(FlagZombie);

	Vector<SpriteFrame*> images1;
	for (int i = 1; i <= 12; i++)
	{
		images1.pushBack(cache1->getSpriteFrameByName(StringUtils::format("FlagZombie_%d.png", i)));
	}

	Animation* animation1 = Animation::createWithSpriteFrames(images1, 2.f / images1.size());
	Animate* animate1 = Animate::create(animation1);
	//matchSprite->runAction(RepeatForever::create(animate));
	FlagZombie->runAction(Sequence::createWithTwoActions
	(
		Repeat::create(animate1, 50000),
		CallFunc::create([FlagZombie]()
	{
		FlagZombie->removeFromParent();
	})
	));
	//2
	auto cache2 = SpriteFrameCache::getInstance();
	cache2->addSpriteFramesWithFile("res/CYHres/mainScene/BucketheadZombie/BucketheadZombie.plist");

	Sprite* BucketheadZombie = Sprite::createWithSpriteFrameName("BucketheadZombie_1.png");
	BucketheadZombie->setPosition(Vec2(visibleSizeWidth / 2 + 80, visibleSizeHeight / 4 + 100));
	this->addChild(BucketheadZombie);

	Vector<SpriteFrame*> images2;
	for (int i = 1; i <= 15; i++)
	{
		images2.pushBack(cache2->getSpriteFrameByName(StringUtils::format("BucketheadZombie_%d.png", i)));
	}
	Animation* animation2 = Animation::createWithSpriteFrames(images2, 2.f / images2.size());
	Animate* animate2 = Animate::create(animation2);
	//matchSprite->runAction(RepeatForever::create(animate));
	BucketheadZombie->runAction(Sequence::createWithTwoActions
	(
		Repeat::create(animate2, 50000),
		CallFunc::create([BucketheadZombie]()
	{
		BucketheadZombie->removeFromParent();
	})
	));
	//3
	auto cache3 = SpriteFrameCache::getInstance();
	cache3->addSpriteFramesWithFile("res/CYHres/mainScene/ConeheadZombie/ConeheadZombie.plist");

	Sprite* ConeheadZombie = Sprite::createWithSpriteFrameName("ConeheadZombie_1.png");
	ConeheadZombie->setPosition(Vec2(visibleSizeWidth / 2 + 70, visibleSizeHeight / 4 + 20));
	this->addChild(ConeheadZombie);

	Vector<SpriteFrame*> images3;
	for (int i = 1; i <= 21; i++)
	{
		images3.pushBack(cache3->getSpriteFrameByName(StringUtils::format("ConeheadZombie_%d.png", i)));
	}
	Animation* animation3 = Animation::createWithSpriteFrames(images3, 2.f / images3.size());
	Animate* animate3 = Animate::create(animation3);
	//matchSprite->runAction(RepeatForever::create(animate));
	ConeheadZombie->runAction(Sequence::createWithTwoActions
	(
		Repeat::create(animate3, 50000),
		CallFunc::create([ConeheadZombie]()
	{
		ConeheadZombie->removeFromParent();
	})
	));
	//4
	auto cache4 = SpriteFrameCache::getInstance();
	cache4->addSpriteFramesWithFile("res/CYHres/mainScene/TallNut/TallNut.plist");

	Sprite* TallNut = Sprite::createWithSpriteFrameName("TallNut_1.png");
	TallNut->setPosition(Vec2(visibleSizeWidth / 2 - 150, visibleSizeHeight / 4 - 40));
	this->addChild(TallNut);

	Vector<SpriteFrame*> images4;
	for (int i = 1; i <= 14; i++)
	{
		images4.pushBack(cache4->getSpriteFrameByName(StringUtils::format("TallNut_%d.png", i)));
	}
	Animation* animation4 = Animation::createWithSpriteFrames(images4, 2.f / images4.size());
	Animate* animate4 = Animate::create(animation4);
	//matchSprite->runAction(RepeatForever::create(animate));
	TallNut->runAction(Sequence::createWithTwoActions
	(
		Repeat::create(animate4, 50000),
		CallFunc::create([TallNut]()
	{
		TallNut->removeFromParent();
	})
	));
	//5
	auto cache5 = SpriteFrameCache::getInstance();
	cache5->addSpriteFramesWithFile("res/CYHres/mainScene/Peashooter/Peashooter.plist");

	Sprite* Peashooter = Sprite::createWithSpriteFrameName("Peashooter_1.png");
	Peashooter->setPosition(Vec2(visibleSizeWidth / 2 - 350, visibleSizeHeight / 2 - 120));
	this->addChild(Peashooter);

	Vector<SpriteFrame*> images5;
	for (int i = 1; i <= 13; i++)
	{
		images5.pushBack(cache5->getSpriteFrameByName(StringUtils::format("Peashooter_%d.png", i)));
	}

	Animation* animation5 = Animation::createWithSpriteFrames(images5, 2.f / images5.size());
	Animate* animate5 = Animate::create(animation5);
	//matchSprite->runAction(RepeatForever::create(animate));
	Peashooter->runAction(Sequence::createWithTwoActions
	(
		Repeat::create(animate5, 50000),
		CallFunc::create([Peashooter]()
	{
		Peashooter->removeFromParent();
	})
	));

	//add return button
	auto returnBtn = ui::Button::create("res/CYHres/timg.png");
	if (returnBtn == nullptr)
	{
		log("returnBtn wrong!");
	}
	/*returnBtn->setTitleText("exit");
	returnBtn->setTitleFontSize(30);
	returnBtn->setTitleColor(Color3B::WHITE);*/
	addChild(returnBtn);
	returnBtn->setPosition(Vec2(visibleSizeWidth / 4 * 3 + 40, visibleSizeHeight / 4 + 90));
	returnBtn->addClickEventListener([&](Ref* ref) {
		//this->addChild(menuLayer::create());
		Director::getInstance()->pushScene(TransitionFade::create(1.f, LogSignScene::create()));
	});

	//add menu button and create menuLayer
	auto menuBtn = ui::Button::create("res/CYHres/Credits_PlayButton.png");
	if (menuBtn == nullptr)
	{
		log("menuBtn wrong!");
	}
	//menuBtn->setTitleText("menu");
	//menuBtn->setTitleFontSize(30);
	//menuBtn->setTitleColor(Color3B::WHITE);
	addChild(menuBtn);
	menuBtn->setPosition(Vec2(visibleSizeWidth / 4 * 3 + 150, visibleSizeHeight / 4 + 70));

	menu = menuLayer::create();
	if (menu == nullptr)
	{
		log("menu wrong!");
	}
	else
	{
		this->addChild(menu);
		menu->setVisible(false);
	}

	menuBtn->addClickEventListener([&](Ref* ref) {
		if (isMenuVisible == false) {
			menu->setVisible(true);
			isMenuVisible = true;

		}
		else
		{
			menu->setVisible(false);
			isMenuVisible = false;
		}
	});

	//关闭套接字
	//closesocket(clntSock);
	//终止使用 DLL
	//WSACleanup();

	return true;
}

cocos2d::Layer* menuLayer::createLayer()
{
	return menuLayer::create();
}

bool menuLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSizeWidth = Director::getInstance()->getVisibleSize().width;
	auto visibleSizeHeight = Director::getInstance()->getVisibleSize().height;

	auto bgMenu = Sprite::create("res/CYHres/options_menuback.png");
	if (bgMenu == nullptr)
	{
		CCLOG("options_menuback.png wrong!");
	}
	else
	{
		this->addChild(bgMenu);
		bgMenu->setPosition(Vec2(visibleSizeWidth / 2 , visibleSizeHeight / 2));
	}

	//add bgm and button
	auto bgplayBtn = ui::Button::create();
	if (bgplayBtn == nullptr)
	{
		log("bgplayBtn wrong!");
	}
	bgplayBtn->setTitleText("play");
	bgplayBtn->setTitleFontSize(36);
	bgplayBtn->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 + 100));
	bgplayBtn->addClickEventListener([](Ref* sender) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic("res/CYHres/Laura Shigihara - Rigor Hormist.wav", true);
	});
	this->addChild(bgplayBtn);

	auto bgpauseBtn = ui::Button::create();
	if (bgpauseBtn == nullptr)
	{
		log("bgpauseBtn wrong!");
	}
	bgpauseBtn->setTitleText("pause");
	bgpauseBtn->setTitleFontSize(36);
	bgpauseBtn->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 + 50));
	bgpauseBtn->addClickEventListener([](Ref* sender) {
		SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	});
	this->addChild(bgpauseBtn);

	auto bgresumeBtn = ui::Button::create();
	if (bgresumeBtn == nullptr)
	{
		log("bgresumeBtn wrong!");
	}
	bgresumeBtn->setTitleText("resume");
	bgresumeBtn->setTitleFontSize(36);
	bgresumeBtn->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - 0));
	bgresumeBtn->addClickEventListener([](Ref* sender) {
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	});
	this->addChild(bgresumeBtn);

	auto bgstopBtn = ui::Button::create();
	if (bgstopBtn == nullptr)
	{
		log("bgstopBtn wrong!");
	}
	bgstopBtn->setTitleText("stop");
	bgstopBtn->setTitleFontSize(36);
	bgstopBtn->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - 50));
	bgstopBtn->addClickEventListener([](Ref* sender) {
		SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	});
	this->addChild(bgstopBtn);

	return true;
}
