#pragma once
#include "matchScene.h"

cocos2d::Scene* matchScene::createScene()
{
	return matchScene::create();
}

void matchScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	Director::getInstance()->pushScene(TransitionSlideInL::create(1.f, mainScene::createScene()));
}

bool matchScene::init()
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
	auto bg = Sprite::create("matchingBG.png");
	if (bg == nullptr)
	{
		CCLOG("titlescreen.jpg wrong!");
	}
	else
	{
		this->addChild(bg);
		bg->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2));
	}
	
	
	//add return button
	auto cancelBtn = MenuItemImage::create(
		"matchCancelBtn1.png",
		"matchCancelBtn2.png",
		CC_CALLBACK_1(matchScene::menuCloseCallback, this));

	if (cancelBtn == nullptr ||
		cancelBtn->getContentSize().width <= 0 ||
		cancelBtn->getContentSize().height <= 0)
	{
		CCLOG("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		cancelBtn->setPosition(Vec2(visibleSizeWidth / 2 - 100, visibleSizeHeight / 10 * 3 + 50));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(cancelBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
	/*auto returnBtn = ui::Button::create("returnBtn.png");
	addChild(returnBtn);
	returnBtn->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - visibleSizeHeight / 4));
	returnBtn->addClickEventListener([&](Ref* ref) {
		Director::getInstance()->replaceScene(mainScene::create());
	});*/

	////创建帧动画
	//auto cache = SpriteFrameCache::getInstance();
	//cache->addSpriteFramesWithFile("match.plist");
	//Sprite* matchSprite = Sprite::createWithSpriteFrameName("1.png");
	//matchSprite->setPosition(Vec2(visibleSizeWidth / 8 * 7, visibleSizeHeight / 4 * 3));
	//this->addChild(matchSprite);

	////创建精灵帧集合
	//Vector<SpriteFrame*> images;
	//images.pushBack(cache->getSpriteFrameByName("1.png"));
	//images.pushBack(cache->getSpriteFrameByName("2.png"));
	//images.pushBack(cache->getSpriteFrameByName("3.png"));
	//images.pushBack(cache->getSpriteFrameByName("4.png"));

	////创建动画对象
	//Animation* animation = Animation::createWithSpriteFrames(images, 1.f / images.size());
	//Animate* animate = Animate::create(animation);

	////matchSprite->runAction(RepeatForever::create(animate));

	//matchSprite->runAction(Sequence::createWithTwoActions(
	//	Repeat::create(animate, 50000),
	//	CallFunc::create([matchSprite]() {
	//		matchSprite->removeFromParent();
	//	})
	//));

	auto cacheMatch = SpriteFrameCache::getInstance();
	cacheMatch->addSpriteFramesWithFile("loading/loading.plist");

	Sprite* matchSprite = Sprite::createWithSpriteFrameName("loading_1.png");
	matchSprite->setPosition(Vec2(visibleSizeWidth / 4 * 3 + 50, visibleSizeHeight / 2 + 20));
	this->addChild(matchSprite);

	Vector<SpriteFrame*> imagesMatch;
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_1.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_2.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_3.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_4.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_5.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_6.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_7.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_8.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_9.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_10.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_11.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_12.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_13.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_14.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_15.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_16.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_17.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_18.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_19.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_20.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_21.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_22.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_23.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_24.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_25.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_26.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_27.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_28.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_29.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_30.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_31.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_32.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_33.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_34.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_35.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_36.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_37.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_38.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_39.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_40.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_41.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_42.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_43.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_44.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_45.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_46.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_47.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_48.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_49.png"));
	imagesMatch.pushBack(cacheMatch->getSpriteFrameByName("loading_50.png"));


	Animation* animationMatch = Animation::createWithSpriteFrames(imagesMatch, 2.f / imagesMatch.size());
	Animate* animateMatch = Animate::create(animationMatch);
	//matchSprite->runAction(RepeatForever::create(animate));
	matchSprite->runAction(Sequence::createWithTwoActions
	(
		Repeat::create(animateMatch, 50000),
		CallFunc::create([matchSprite]()
	{
		matchSprite->removeFromParent();
	})
	));

	//关闭套接字
	//closesocket(clntSock);
	//终止使用 DLL
	//WSACleanup();

	return true;
}
