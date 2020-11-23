#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include <stdio.h>
#include"socket.h"
#include"LogSignScene.h"

USING_NS_CC;

class SignupScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(SignupScene);

	virtual bool init();

private:
	WSADATA wsaData;
	SOCKET clntSock;
	sockaddr_in clntAddr;
	ui::TextField* username;
	ui::TextField* password;
	ui::TextField* password2;
};
