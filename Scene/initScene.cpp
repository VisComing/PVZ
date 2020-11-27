#pragma once
#include "initScene.h"

USING_NS_CC;
USING_NS_CC_EXT;

Scene* initScene::createScene()
{
    return initScene::create();
}

void initScene::menuCloseCallback(cocos2d::Ref* pSender)
{
    if (isConnectSuc == 0) 
    {
        Director::getInstance()->pushScene(TransitionFade::create(1.f, LogSignScene::create()));
    }
    else{
        MessageBox("CONNECTION FAILURE", "WARNING");
    }

}

// on "init" you need to initialize your instance

bool initScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    //connect to server
    isConnectSuc = TCPSocket::getInstance()->connectToServer();

    this->schedule(schedule_selector(LogSignScene::callServer), 1.f);

    //bgm
    SimpleAudioEngine::getInstance()->playBackgroundMusic("res/CYHres/Laura Shigihara - Rigor Hormist.wav", true);

    auto visibleSizeWidth = Director::getInstance()->getVisibleSize().width;
    auto visibleSizeHeight = Director::getInstance()->getVisibleSize().height;

    auto bgLogo = Sprite::create("res/CYHres/PopCap_Logo.jpg");
    if (bgLogo == nullptr)
    {
        CCLOG("PopCap_Logo.jpg wrong!");
    }
    else
    {
        this->addChild(bgLogo);
        bgLogo->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 + 50));
    }

    //add return button
    auto changeBtn = MenuItemImage::create(
        "res/CYHres/options_backtogamebutton0.png",
        "res/CYHres/options_backtogamebutton2.png",
        CC_CALLBACK_1(initScene::menuCloseCallback, this));

    if (changeBtn == nullptr ||
        changeBtn->getContentSize().width <= 0 ||
        changeBtn->getContentSize().height <= 0)
    {
        CCLOG("'options_backtogamebutton0.png' and 'options_backtogamebutton2.png'");
    }
    else
    {
        changeBtn->setPosition(Vec2(visibleSizeWidth / 64 * 51 + 50, visibleSizeHeight / 10 * 3 - 50));
    }
    auto gogogo = Menu::create(changeBtn, NULL);
    if (gogogo == nullptr) 
    {
        log("gogogo wrong");
    }
    else 
    {
        gogogo->setPosition(Vec2::ZERO);
        this->addChild(gogogo);
    }
    

    //add information of author and version
    auto info = Sprite::create("res/CYHres/info.png");
    if (info == nullptr)
    {
        CCLOG("info.png wrong!");
    }
    else
    {
        this->addChild(info);
        info->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - 150));
    }
    return true;
}

