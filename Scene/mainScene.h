#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include <stdio.h>
#include "matchScene.h"
#include"SimpleAudioEngine.h"
#include"LogSignScene.h"
using namespace CocosDenshion;


USING_NS_CC;

class menuLayer : public cocos2d::Layer
{
public:
	static cocos2d::Layer* createLayer();

	CREATE_FUNC(menuLayer);

	virtual bool init();

};

class mainScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(mainScene);

	virtual bool init();

private:
	WSADATA wsaData;
	SOCKET clntSock;
	sockaddr_in clntAddr;
	menuLayer* menu;
	bool isMenuVisible = false;
};


