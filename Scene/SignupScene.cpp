#pragma once
#include "SignupScene.h"

cocos2d::Scene* SignupScene::createScene()
{
	return SignupScene::create();
}

bool SignupScene::init()
{
	this->schedule(schedule_selector(LogSignScene::callServer), 1.f);

	if (!Scene::init())
	{
		return false;
	}

	auto visibleSizeWidth = Director::getInstance()->getVisibleSize().width;
	auto visibleSizeHeight = Director::getInstance()->getVisibleSize().height;

	//add background
	auto bg = Sprite::create("res/CYHres/test2.jpg");
	if (bg == nullptr)
	{
		CCLOG("titlescreen.jpg wrong!");
	}
	else
	{
		this->addChild(bg);
		bg->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2));
	}

	//创建蝴蝶动画
	auto cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("res/CYHres/LogSignScene/butterfly/butterfly.plist");

	Sprite* butterflySprite1 = Sprite::createWithSpriteFrameName("timg_1.png");
	butterflySprite1->setPosition(Vec2(visibleSizeWidth / 4 - 20, visibleSizeHeight / 4 * 3));
	this->addChild(butterflySprite1);

	Sprite* butterflySprite2 = Sprite::createWithSpriteFrameName("timg_20.png");
	butterflySprite2->setPosition(Vec2(visibleSizeWidth / 4 * 3 + 170, visibleSizeHeight / 2 - 100));
	this->addChild(butterflySprite2);

	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 30; i++)
	{
		images.pushBack(cache->getSpriteFrameByName(StringUtils::format("timg_%d.png", i)));
	}
	for (int i = 33; i <= 40; i++)
	{
		images.pushBack(cache->getSpriteFrameByName(StringUtils::format("timg_%d.png", i)));
	}

	Animation* animation1 = Animation::createWithSpriteFrames(images, 4.f / images.size());
	Animate* animate1 = Animate::create(animation1);
	//matchSprite->runAction(RepeatForever::create(animate));
	butterflySprite1->runAction(RepeatForever::create(animate1));
	/*butterflySprite1->runAction(Sequence::createWithTwoActions
	(
		Repeat::create(animate1, 50000),
		CallFunc::create([butterflySprite1]()
	{
		butterflySprite1->removeFromParent();
	})
	));*/

	Animation* animation2 = Animation::createWithSpriteFrames(images, 4.f / images.size());
	Animate* animate2 = Animate::create(animation2);
	butterflySprite2->runAction(RepeatForever::create(animate2));
	/*butterflySprite2->runAction(Sequence::createWithTwoActions
	(
		Repeat::create(animate2, 50000),
		CallFunc::create([butterflySprite2]()
	{
		butterflySprite2->removeFromParent();
	})
	));*/

	//登录和注册面板设计
	auto logBg1 = Sprite::create("res/CYHres/LogSignScene/8.png");
	if (logBg1 == nullptr)
	{
		CCLOG("LogSignScene/1.png wrong!");
	}
	else
	{
		this->addChild(logBg1);
		logBg1->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - visibleSizeHeight / 8));
	}
	auto logBg2 = ui::Button::create("res/CYHres/LogSignScene/3.png");
	if (logBg2 == nullptr)
	{
		CCLOG("LogSignScene/2.png wrong!");
	}
	else
	{
		this->addChild(logBg2);
		logBg2->setPosition(Vec2(visibleSizeWidth / 2 - 78, visibleSizeHeight / 2 + visibleSizeHeight / 8 + 38));
		logBg2->addClickEventListener([&](Ref* ref) {
			Director::getInstance()->replaceScene(LogSignScene::create());
			});

	}
	auto logBg3 = ui::Button::create("res/CYHres/LogSignScene/4.png");
	if (logBg3 == nullptr)
	{
		CCLOG("LogSignScene/5.png wrong!");
	}
	else
	{
		this->addChild(logBg3);
		logBg3->setPosition(Vec2(visibleSizeWidth / 2 + 72, visibleSizeHeight / 2 + visibleSizeHeight / 8 + 40));
		logBg3->addClickEventListener([&](Ref* ref) {
			Director::getInstance()->replaceScene(SignupScene::create());
			});

	}

	spriteOnlyEnglish = Sprite::create("onlyEnglish.png");
	if (spriteOnlyEnglish == nullptr)
	{
		CCLOG("onlyEnglish.png wrong!");
	}
	this->addChild(spriteOnlyEnglish);
	spriteOnlyEnglish->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2));
	spriteOnlyEnglish->setVisible(false);

	spriteOnlyEngNum = Sprite::create("onlyEngNum.png");
	if (spriteOnlyEngNum == nullptr)
	{
		CCLOG("onlyEngNum.png wrong!");
	}
	this->addChild(spriteOnlyEngNum);
	spriteOnlyEngNum->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2));
	spriteOnlyEngNum->setVisible(false);

	//add UsernameInput and PasswordInput
	auto UsernameInput = ui::TextField::create();
	auto PasswordInput = ui::TextField::create();
	auto PasswordInput2 = ui::TextField::create();
	if (UsernameInput == nullptr || PasswordInput == nullptr)
	{
		CCLOG("UsernameInput and PasswordInput wrong!");
	}
	else
	{
		addChild(UsernameInput);
		addChild(PasswordInput);
		addChild(PasswordInput2);
		UsernameInput->setCursorEnabled(true);
		UsernameInput->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 + 20));
		UsernameInput->setPlaceHolder("Username");

		UsernameInput->setFontSize(24);
		UsernameInput->setColor(Color3B::BLACK);
		UsernameInput->setMaxLengthEnabled(true);
		UsernameInput->setMaxLength(6);
		UsernameInput->ignoreContentAdaptWithSize(false);  //自动换行，使输入从左端开始
		
		PasswordInput->setCursorEnabled(true);
		PasswordInput->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - visibleSizeHeight / 8 + 20));
		PasswordInput->setPlaceHolder("Password");

		PasswordInput->setFontSize(24);
		PasswordInput->setColor(Color3B::BLACK);
		PasswordInput->setMaxLengthEnabled(true);
		PasswordInput->setMaxLength(9);
		PasswordInput->ignoreContentAdaptWithSize(false);  //自动换行，使输入从左端开始
		PasswordInput->setPasswordEnabled(true);
		PasswordInput2->setCursorEnabled(true);
		PasswordInput2->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2 - visibleSizeHeight / 4 + 25));
		PasswordInput2->setPlaceHolder("Password");

		PasswordInput2->setFontSize(24);
		PasswordInput2->setColor(Color3B::BLACK);
		PasswordInput2->setMaxLengthEnabled(true);
		PasswordInput2->setMaxLength(9);
		PasswordInput2->ignoreContentAdaptWithSize(false);  //自动换行，使输入从左端开始
		PasswordInput2->setPasswordEnabled(true);

		/*UsernameInput->addClickEventListener([&](Ref* ref)
		{
			dynamic_cast<ui::TextField*>(ref)->setString("");
		});*/
		UsernameInput->addEventListener([&](Ref* ref, ui::TextField::EventType type)
			{
				if (type == ui::TextField::EventType::INSERT_TEXT)
				{
					username = dynamic_cast<ui::TextField*>(ref);

					log("%s", username->getString().c_str());

					//username must only includes English words
					for (char c : username->getString())
					{
						if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')))
						{
							username->setString("");
							spriteOnlyEnglish->setVisible(true);
							auto fadein = FadeIn::create(0.3f);
							auto fadeout = FadeOut::create(0.2f);
							auto delay = DelayTime::create(0.3f);
							spriteOnlyEnglish->runAction(Sequence::create(
								fadein,
								delay,
								fadeout,
								nullptr
							));
							//log("please input English words!");
							break;
						}
					}

				}
			});

		/*PasswordInput->addClickEventListener([&](Ref* ref)
		{
			dynamic_cast<ui::TextField*>(ref)->setString("");
		});*/
		PasswordInput->addEventListener([&](Ref* ref, ui::TextField::EventType type)
			{
				if (type == ui::TextField::EventType::INSERT_TEXT)
				{
					password = dynamic_cast<ui::TextField*>(ref);

					log("%s", password->getString().c_str());

					//username must only includes English words
					for (char c : password->getString())
					{
						if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')))
						{
							password->setString("");
							spriteOnlyEngNum->setVisible(true);
							auto fadein = FadeIn::create(0.3f);
							auto fadeout = FadeOut::create(0.2f);
							auto delay = DelayTime::create(0.3f);
							spriteOnlyEngNum->runAction(Sequence::create(
								fadein,
								delay,
								fadeout,
								nullptr
							));
							//log("please input English words and numbers!");
							break;
						}
					}
				}
			});

		PasswordInput2->addEventListener([&](Ref* ref, ui::TextField::EventType type)
			{
				if (type == ui::TextField::EventType::INSERT_TEXT)
				{
					password2 = dynamic_cast<ui::TextField*>(ref);

					log("%s", password2->getString().c_str());

					//username must only includes English words
					for (char c : password2->getString())
					{
						if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')))
						{
							password2->setString("");
							spriteOnlyEngNum->setVisible(true);
							auto fadein = FadeIn::create(0.3f);
							auto fadeout = FadeOut::create(0.2f);
							auto delay = DelayTime::create(0.3f);
							spriteOnlyEngNum->runAction(Sequence::create(
								fadein,
								delay,
								fadeout,
								nullptr
							));
							//log("please input English words and numbers!");
							break;
						}
					}
				}
			});
	}

	spriteSignSuc = Sprite::create("signSuc.png");
	if (spriteSignSuc == nullptr)
	{
		CCLOG("loginSuc.png wrong!");
	}
	this->addChild(spriteSignSuc);
	spriteSignSuc->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2));
	spriteSignSuc->setVisible(false);

	spriteSignFai = Sprite::create("signFai.png");
	if (spriteSignFai == nullptr)
	{
		CCLOG("loginFai.png wrong!");
	}
	this->addChild(spriteSignFai);
	spriteSignFai->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2));
	spriteSignFai->setVisible(false);

	spriteExistEmpty = Sprite::create("existEmpty.png");
	if (spriteExistEmpty == nullptr)
	{
		CCLOG("loginFai.png wrong!");
	}
	this->addChild(spriteExistEmpty);
	spriteExistEmpty->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2));
	spriteExistEmpty->setVisible(false);

	spritePass2NotMatch = Sprite::create("pass2NotMatch.png");
	if (spritePass2NotMatch == nullptr)
	{
		CCLOG("loginFai.png wrong!");
	}
	this->addChild(spritePass2NotMatch);
	spritePass2NotMatch->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 2));
	spritePass2NotMatch->setVisible(false);

	//add login and signup button
	auto SignupBtn = ui::Button::create("res/CYHres/LogSignScene/7.png");
	if (SignupBtn == nullptr)
	{
		log("LoginBtn and SignupBtn wrong!");
	}
	else
	{
		addChild(SignupBtn);
		SignupBtn->setPosition(Vec2(visibleSizeWidth / 2, visibleSizeHeight / 5 - 20));
		SignupBtn->addClickEventListener([&](Ref* ref) {

			if (username == nullptr || password == nullptr || password2 == nullptr
				|| username->getString().empty() == true || password->getString().empty() == true
				|| password2->getString().empty() == true)
			{
				spriteExistEmpty->setVisible(true);
				auto fadein = FadeIn::create(0.3f);
				auto fadeout = FadeOut::create(0.2f);
				auto delay = DelayTime::create(0.3f);
				spriteExistEmpty->runAction(Sequence::create(
					fadein,
					delay,
					fadeout,
					nullptr
				));
				//MessageBox("The username or password can not be empty!", "plants");
			}
			else if (password->getString() != password2->getString())
			{
				spritePass2NotMatch->setVisible(true);
				auto fadein = FadeIn::create(0.3f);
				auto fadeout = FadeOut::create(0.2f);
				auto delay = DelayTime::create(0.3f);
				spritePass2NotMatch->runAction(Sequence::create(
					fadein,
					delay,
					fadeout,
					nullptr
				));
				//MessageBox("The passwords entered two times do not match!", "plants");
			}
			else
			{
				string signMsg = "REGISTER;";
				signMsg = signMsg + username->getString() + ";";
				signMsg = signMsg + password->getString() + ";\n";
				TCPSocket::getInstance()->writeIntoServer(signMsg);
				string isSignupSuc;
				while (1)
				{
					isSignupSuc = TCPSocket::getInstance()->readFromServer();
					if (isSignupSuc.size() == 0 || isSignupSuc == "HeartBeat;")
					{
						log(isSignupSuc.c_str());
						continue;
					}
					else
					{
						log(isSignupSuc.c_str());
						break;
					}
				}
				log(isSignupSuc.c_str());
				if (isSignupSuc == "REGISTER;1;")
				{
					spriteSignSuc->setVisible(true);
					auto fadeout = FadeOut::create(1.0f);
					auto delay = DelayTime::create(1.0f);
					spriteSignSuc->runAction(Sequence::create(
						fadeout,
						delay,
						nullptr
					));
					Director::getInstance()->pushScene(TransitionFade::create(0.5f, LogSignScene::create()));
					//MessageBox("Sign up succeed!", "plants");
				}
				else if (isSignupSuc == "REGISTER;0;")
				{
					spriteSignFai->setVisible(true);
					auto fadein = FadeIn::create(0.3f);
					auto fadeout = FadeOut::create(0.2f);
					auto delay = DelayTime::create(0.3f);
					spriteSignFai->runAction(Sequence::create(
						fadein,
						delay,
						fadeout,
						nullptr
					));
					//MessageBox("Sign up failed!", "plants");
				}
			}
			});
	}

	//关闭套接字
	//closesocket(clntSock);
	//终止使用 DLL
	//WSACleanup();

	return true;
}
