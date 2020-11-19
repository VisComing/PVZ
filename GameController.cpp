#include "GameController.h"
#include "GameLayer.h"
#include "GameScene.h"
GameController::GameController()
{
}
GameController::~GameController()
{
}
bool GameController::init()
{
	if (!Layer::init())
	{
		return false;
	}
	this->schedule(schedule_selector(GameController::produceZombieUpdate), 8);
	return true;
}
void GameController::update(float dt)
{
}
void GameController::produceChomperSprite(Vec2 position)
{
	((GameLayer*)this->getParent())->_peaShooterLayer->initPeaShooterSprite(position);
}

void GameController::producePeaShooterSprite(Vec2 position)
{
	((GameLayer*)this->getParent())->_potatoMineLayer->initPotatoMineSprite(position);
}

void GameController::producePotatoMineSprite(Vec2 position)
{
	((GameLayer*)this->getParent())->_wallNutLayer->initWallNutSprite(position);
}

void GameController::produceWallNutSprite(Vec2 position)
{
	((GameLayer*)this->getParent())->_chomperLayer->initChomperSprite(position);
}

void GameController::produceNormalZombieSprite(string zombieName, Vec2 position)
{
	((GameLayer*)this->getParent())->_normalZombieLayer->autoInitZombie(zombieName, position);
}

void GameController::produceZombieUpdate(float dlt)
{
	int random = rand() % 5;
	float x = 1045;
	float y;
	if(random == 0) y = 80;
	else if(random == 1) y = 175;
	else if(random == 2) y = 274;
	else if(random == 3) y = 375;
	else y = 475;
	Vec2 _pos = Vec2(x, y);
	random = rand() % 4;
	if (random == 0) produceNormalZombieSprite("NormalZombie", _pos);
	else if(random == 1) produceNormalZombieSprite("FlagZombie", _pos);
	else if(random == 2) produceNormalZombieSprite("ConeheadZombie", _pos);
	else produceNormalZombieSprite("BucketheadZombie", _pos);

}
