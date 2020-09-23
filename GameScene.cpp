#include "GameScene.h"
#include "GameLayer.h"
Scene* GameScene::createScene()
{
	return GameScene::create();
}
bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	srand((unsigned)time(nullptr));//Ëæ»úÖÖ×Ó
	this->initGameLayer();

	return true;
}

void GameScene::initGameLayer()
{
	GameLayer* gameLayer = GameLayer::create();
	this->addChild(gameLayer);
}