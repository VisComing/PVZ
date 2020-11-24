#pragma once
#include "matchScene.h"
#include "../Base/global.h"
#include "../Base/GameScene.h"
cocos2d::Scene* matchScene::createScene()
{
	return matchScene::create();
}

void matchScene::menuCloseCallback(cocos2d::Ref* pSender)
{
	TCPSocket::getInstance()->writeIntoServer("CANCELMATCH;\n");
	Director::getInstance()->pushScene(TransitionSlideInL::create(1.f, mainScene::createScene()));
}

bool matchScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	this->schedule(schedule_selector(LogSignScene::callServer), 1.f);
	this->schedule(schedule_selector(matchScene::matchSuccess), 0.1f);
	auto visibleSizeWidth = Director::getInstance()->getVisibleSize().width;
	auto visibleSizeHeight = Director::getInstance()->getVisibleSize().height;
	
	TCPSocket::getInstance()->writeIntoServer("MATCH;\n");

	//add background
	auto bg = Sprite::create("res/CYHres/matchingBG.png");
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
		"res/CYHres/matchCancelBtn1.png",
		"res/CYHres/matchCancelBtn2.png",
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


	auto cacheMatch = SpriteFrameCache::getInstance();
	cacheMatch->addSpriteFramesWithFile("res/CYHres/loading/loading.plist");

	Sprite* matchSprite = Sprite::createWithSpriteFrameName("loading_1.png");
	matchSprite->setPosition(Vec2(visibleSizeWidth / 4 * 3 + 50, visibleSizeHeight / 2 + 20));
	this->addChild(matchSprite);

	Vector<SpriteFrame*> imagesMatch;
	for (int i = 1; i <= 50; i++)
	{
		imagesMatch.pushBack(cacheMatch->getSpriteFrameByName(StringUtils::format("loading_%d.png", i)));
	}


	Animation* animationMatch = Animation::createWithSpriteFrames(imagesMatch, 2.f / imagesMatch.size());
	Animate* animateMatch = Animate::create(animationMatch);
	//matchSprite->runAction(RepeatForever::create(animate));
	matchSprite->runAction(RepeatForever::create(animateMatch));
	/*matchSprite->runAction(Sequence::createWithTwoActions
	(
		Repeat::create(animateMatch, 50000),
		CallFunc::create([matchSprite]()
	{
		matchSprite->removeFromParent();
	})
	));*/

	//关闭套接字
	//closesocket(clntSock);
	//终止使用 DLL
	//WSACleanup();

	return true;
}

void matchScene::matchSuccess(float)
{
	//注意此处是replaceScene
	string ans = TCPSocket::getInstance()->readFromServer();
	log(ans.c_str());
	if (ans == "MATCHSUCCESS;0;")
	{
		isSinglePlayerGameMode = false;
		_iAmPlantSideGolbalVariable = true;
		Director::getInstance()->replaceScene(GameScene::create());
	}
	else if (ans == "MATCHSUCCESS;1;")
	{
		isSinglePlayerGameMode = false;
		_iAmPlantSideGolbalVariable = false;
		Director::getInstance()->replaceScene(GameScene::create());
	}
}
