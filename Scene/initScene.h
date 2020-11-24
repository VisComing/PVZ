#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include"AppDelegate.h"
#include"LogSignScene.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include"../Base/socket.h"


class initScene : public cocos2d::Scene
{
public:

    static cocos2d::Scene* createScene();

    virtual bool init();

    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(initScene);
};