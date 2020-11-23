#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include <stdio.h>
#include "mainScene.h"
#include"LogSignScene.h"

USING_NS_CC;

class matchScene : public cocos2d::Scene 
{
public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(matchScene);

	void menuCloseCallback(cocos2d::Ref* pSender);

	virtual bool init();

private:
	WSADATA wsaData;
	SOCKET clntSock;
	sockaddr_in clntAddr;
};
