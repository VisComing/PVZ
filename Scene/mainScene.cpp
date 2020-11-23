#pragma once
#include "mainScene.h"

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
	auto bgSky = Sprite::create("Store_Background.jpg");
	if (bgSky == nullptr)
	{
		CCLOG("Store_Background.jpg wrong!");
	}
	else
	{
		this->addChild(bgSky);
		bgSky->setPosition(Vec2(visibleSizeWidth / 2 - 500, visibleSizeHeight / 2 ));
	}

	auto bgHouse = Sprite::create("SelectorScreen_BG_Center.png");
	if (bgHouse == nullptr)
	{
		CCLOG("titlescreen.jpg wrong!");
	}
	else
	{
		this->addChild(bgHouse);
		bgHouse->setPosition(Vec2(visibleSizeWidth / 2 - 50, visibleSizeHeight / 2 - 130));
	}

	auto bgTree = Sprite::create("SelectorScreen_BG_Left.png");
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
	auto stele = Sprite::create("SelectorScreen_BG_Right1.png");
	if (stele == nullptr)
	{
		CCLOG("SelectorScreen_BG_Right1.jpg wrong!");
	}
	else
	{
		this->addChild(stele);
		stele->setPosition(Vec2(visibleSizeWidth / 8 * 7 - 175, visibleSizeHeight / 4 + 118));
	}

	auto aiBtn = ui::Button::create("aiChallengeBtn.png");
	addChild(aiBtn);
	aiBtn->setPosition(Vec2(visibleSizeWidth / 8 * 7 - 50, visibleSizeHeight / 4 + 270));
	aiBtn->addClickEventListener([&](Ref* ref) {
		;
	});

	auto pkBtn = ui::Button::create("matchChallengeBtn.png");
	addChild(pkBtn);
	pkBtn->setPosition(Vec2(visibleSizeWidth / 8 * 7 - 50, visibleSizeHeight / 4 + 165));
	pkBtn->addClickEventListener([&](Ref* ref) {
		Director::getInstance()->pushScene(TransitionSlideInR::create(0.3f, matchScene::create()));
	});

	//创建僵尸动画
	//1
	auto cache1 = SpriteFrameCache::getInstance();
	cache1->addSpriteFramesWithFile("mainScene/FlagZombie/FlagZombie.plist");

	Sprite* FlagZombie = Sprite::createWithSpriteFrameName("FlagZombie_1.png");
	FlagZombie->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 4));
	this->addChild(FlagZombie);

	Vector<SpriteFrame*> images1;
	images1.pushBack(cache1->getSpriteFrameByName("FlagZombie_1.png"));
	images1.pushBack(cache1->getSpriteFrameByName("FlagZombie_2.png"));
	images1.pushBack(cache1->getSpriteFrameByName("FlagZombie_3.png"));
	images1.pushBack(cache1->getSpriteFrameByName("FlagZombie_4.png"));
	images1.pushBack(cache1->getSpriteFrameByName("FlagZombie_5.png"));
	images1.pushBack(cache1->getSpriteFrameByName("FlagZombie_6.png"));
	images1.pushBack(cache1->getSpriteFrameByName("FlagZombie_7.png"));
	images1.pushBack(cache1->getSpriteFrameByName("FlagZombie_8.png"));
	images1.pushBack(cache1->getSpriteFrameByName("FlagZombie_9.png"));
	images1.pushBack(cache1->getSpriteFrameByName("FlagZombie_10.png"));
	images1.pushBack(cache1->getSpriteFrameByName("FlagZombie_11.png"));
	images1.pushBack(cache1->getSpriteFrameByName("FlagZombie_12.png"));

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
	cache2->addSpriteFramesWithFile("mainScene/BucketheadZombie/BucketheadZombie.plist");

	Sprite* BucketheadZombie = Sprite::createWithSpriteFrameName("BucketheadZombie_1.png");
	BucketheadZombie->setPosition(Vec2(visibleSizeWidth / 2 + 80, visibleSizeHeight / 4 + 100));
	this->addChild(BucketheadZombie);

	Vector<SpriteFrame*> images2;
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_1.png"));
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_2.png"));
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_3.png"));
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_4.png"));
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_5.png"));
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_6.png"));
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_7.png"));
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_8.png"));
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_9.png"));
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_10.png"));
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_11.png"));
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_12.png"));
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_13.png"));
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_14.png"));
	images2.pushBack(cache2->getSpriteFrameByName("BucketheadZombie_15.png"));

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
	cache3->addSpriteFramesWithFile("mainScene/ConeheadZombie/ConeheadZombie.plist");

	Sprite* ConeheadZombie = Sprite::createWithSpriteFrameName("ConeheadZombie_1.png");
	ConeheadZombie->setPosition(Vec2(visibleSizeWidth / 2 + 70, visibleSizeHeight / 4 + 20));
	this->addChild(ConeheadZombie);

	Vector<SpriteFrame*> images3;
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_1.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_2.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_3.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_4.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_5.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_6.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_7.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_8.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_9.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_10.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_11.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_12.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_13.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_14.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_15.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_16.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_17.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_18.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_19.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_20.png"));
	images3.pushBack(cache3->getSpriteFrameByName("ConeheadZombie_21.png"));

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
	cache4->addSpriteFramesWithFile("mainScene/TallNut/TallNut.plist");

	Sprite* TallNut = Sprite::createWithSpriteFrameName("TallNut_1.png");
	TallNut->setPosition(Vec2(visibleSizeWidth / 2 - 150, visibleSizeHeight / 4 - 40));
	this->addChild(TallNut);

	Vector<SpriteFrame*> images4;
	images4.pushBack(cache4->getSpriteFrameByName("TallNut_1.png"));
	images4.pushBack(cache4->getSpriteFrameByName("TallNut_2.png"));
	images4.pushBack(cache4->getSpriteFrameByName("TallNut_3.png"));
	images4.pushBack(cache4->getSpriteFrameByName("TallNut_4.png"));
	images4.pushBack(cache4->getSpriteFrameByName("TallNut_5.png"));
	images4.pushBack(cache4->getSpriteFrameByName("TallNut_6.png"));
	images4.pushBack(cache4->getSpriteFrameByName("TallNut_7.png"));
	images4.pushBack(cache4->getSpriteFrameByName("TallNut_8.png"));
	images4.pushBack(cache4->getSpriteFrameByName("TallNut_9.png"));
	images4.pushBack(cache4->getSpriteFrameByName("TallNut_10.png"));
	images4.pushBack(cache4->getSpriteFrameByName("TallNut_11.png"));
	images4.pushBack(cache4->getSpriteFrameByName("TallNut_12.png"));
	images4.pushBack(cache4->getSpriteFrameByName("TallNut_13.png"));
	images4.pushBack(cache4->getSpriteFrameByName("TallNut_14.png"));

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
	cache5->addSpriteFramesWithFile("mainScene/Peashooter/Peashooter.plist");

	Sprite* Peashooter = Sprite::createWithSpriteFrameName("Peashooter_1.png");
	Peashooter->setPosition(Vec2(visibleSizeWidth / 2 - 350, visibleSizeHeight / 2 - 120));
	this->addChild(Peashooter);

	Vector<SpriteFrame*> images5;
	images5.pushBack(cache5->getSpriteFrameByName("Peashooter_1.png"));
	images5.pushBack(cache5->getSpriteFrameByName("Peashooter_2.png"));
	images5.pushBack(cache5->getSpriteFrameByName("Peashooter_3.png"));
	images5.pushBack(cache5->getSpriteFrameByName("Peashooter_4.png"));
	images5.pushBack(cache5->getSpriteFrameByName("Peashooter_5.png"));
	images5.pushBack(cache5->getSpriteFrameByName("Peashooter_6.png"));
	images5.pushBack(cache5->getSpriteFrameByName("Peashooter_7.png"));
	images5.pushBack(cache5->getSpriteFrameByName("Peashooter_8.png"));
	images5.pushBack(cache5->getSpriteFrameByName("Peashooter_9.png"));
	images5.pushBack(cache5->getSpriteFrameByName("Peashooter_10.png"));
	images5.pushBack(cache5->getSpriteFrameByName("Peashooter_11.png"));
	images5.pushBack(cache5->getSpriteFrameByName("Peashooter_12.png"));
	images5.pushBack(cache5->getSpriteFrameByName("Peashooter_13.png"));

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
	auto returnBtn = ui::Button::create("timg.png");
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
	auto menuBtn = ui::Button::create("Credits_PlayButton.png");
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

	auto bgMenu = Sprite::create("options_menuback.png");
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
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Laura Shigihara - Rigor Hormist.wav", true);
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
