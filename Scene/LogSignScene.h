#pragma once

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "cocos2d.h"
#include"ui/CocosGUI.h"
#include <stdio.h>
#include"../Base/socket.h"
#include"SignupScene.h"
#include"../AppDelegate.h"
#include"matchScene.h"

USING_NS_CC;

class LogSignScene : public cocos2d::Scene {
public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(LogSignScene);

	void callServer(float);

	virtual bool init();

private:
	WSADATA wsaData;
	SOCKET clntSock;
	sockaddr_in clntAddr;
	ui::TextField* username;
	ui::TextField* password;
	Sprite* spriteLogSuc;
	Sprite* spriteLogFai;
	Sprite* spriteExistEmpty;
	Sprite* spriteOnlyEnglish;
	Sprite* spriteOnlyEngNum;
	//ui::Button* login;
	//ui::Button* signup;
};