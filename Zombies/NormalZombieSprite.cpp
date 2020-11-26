#include "NormalZombieSprite.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

NormalZombieSprite::NormalZombieSprite()
{
	this->_hp = 100;
	attacting = false;
	this->zombieID = 0;
}
NormalZombieSprite::~NormalZombieSprite()
{

}

bool NormalZombieSprite::init()
{
	if (!ZombieBaseClass::init())
	{
		return false;
	}

	return true;
}


RepeatForever * NormalZombieSprite::normalZombieWalkAnimation()
{

	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 22; i++)
	{
		images.pushBack(_normalZombieCache->getSpriteFrameByName(StringUtils::format("Zombie_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 22);
	this->_normalZombieWalkAction = RepeatForever::create(Animate::create(_animation));
	this->_normalZombieWalkAction->setTag(1);
	return this->_normalZombieWalkAction;
}


FiniteTimeAction* NormalZombieSprite::normalZombieNoHeadWalkAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 18; i++)
	{
		images.pushBack(_normalZombieCache->getSpriteFrameByName(StringUtils::format("ZombieLostHead_%d.png", i)));
	}
	Animation* noHeadAnimation = Animation::createWithSpriteFrames(images, 0.2f);
	this->_normalZombieNoHeadWalkAction = RepeatForever::create(Animate::create(noHeadAnimation));
	this->_normalZombieNoHeadWalkAction->setTag(2);
	return this->_normalZombieNoHeadWalkAction;
}

RepeatForever * NormalZombieSprite::normalZombieAttackAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 21; i++)
	{
		images.pushBack(_normalZombieCache->getSpriteFrameByName(StringUtils::format("ZombieAttack_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 0.1f);
	this->_normalZombieAttackAction = RepeatForever::create(Animate::create(_animation));
	this->_normalZombieAttackAction->setTag(3);
	return this->_normalZombieAttackAction;
}

RepeatForever * NormalZombieSprite::normalZombieLostHeadAttackAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 9; i++)
	{
		images.pushBack(_normalZombieCache->getSpriteFrameByName(StringUtils::format("ZombieLostHeadAttack_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 9);
	this->_normalZombieLostHeadAttackAction = RepeatForever::create(Animate::create(_animation));
	this->_normalZombieLostHeadAttackAction->setTag(4);
	return this->_normalZombieLostHeadAttackAction;
}

RepeatForever * NormalZombieSprite::flagZombieWalkAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 12; i++)
	{
		images.pushBack(_armedNormalZombieCache->getSpriteFrameByName(StringUtils::format("FlagZombie_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 12);
	this->_flagZombieWalkAction = RepeatForever::create(Animate::create(_animation));
	this->_flagZombieWalkAction->setTag(5);
	return this->_flagZombieWalkAction;
}

FiniteTimeAction * NormalZombieSprite::flagZombieNoHeadWalkAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 12; i++)
	{
		images.pushBack(_armedNormalZombieCache->getSpriteFrameByName(StringUtils::format("FlagZombieLostHead_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 12);
	this->_flagZombieNoHeadWalkAction = RepeatForever::create(Animate::create(_animation));
	this->_flagZombieNoHeadWalkAction->setTag(6);
	return this->_flagZombieNoHeadWalkAction;
}

RepeatForever * NormalZombieSprite::flagZombieAttackAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 11; i++)
	{
		images.pushBack(_armedNormalZombieCache->getSpriteFrameByName(StringUtils::format("FlagZombieAttack_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 11);
	this->_flagZombieAttackAction = RepeatForever::create(Animate::create(_animation));
	this->_flagZombieAttackAction->setTag(7);
	return this->_flagZombieAttackAction;
}

RepeatForever * NormalZombieSprite::flagZombieLostHeadAttackAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 11; i++)
	{
		images.pushBack(_armedNormalZombieCache->getSpriteFrameByName(StringUtils::format("FlagZombieLostHeadAttack_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 11);
	this->_flagZombieLostHeadAttackAction = RepeatForever::create(Animate::create(_animation));
	this->_flagZombieLostHeadAttackAction->setTag(8);
	return this->_flagZombieLostHeadAttackAction;
}

RepeatForever * NormalZombieSprite::coneheadZombieWalkAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 21; i++)
	{
		images.pushBack(_armedNormalZombieCache->getSpriteFrameByName(StringUtils::format("ConeheadZombie_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 21);
	this->_coneheadZombieWalkAction = RepeatForever::create(Animate::create(_animation));
	this->_coneheadZombieWalkAction->setTag(9);
	return this->_coneheadZombieWalkAction;
}


RepeatForever * NormalZombieSprite::coneheadZombieAttackAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 11; i++)
	{
		images.pushBack(_armedNormalZombieCache->getSpriteFrameByName(StringUtils::format("ConeheadZombieAttack_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 11);
	this->_coneheadZombieAttackAction = RepeatForever::create(Animate::create(_animation));
	this->_coneheadZombieAttackAction->setTag(10);
	return this->_coneheadZombieAttackAction;
}

RepeatForever * NormalZombieSprite::bucketheadZombieWalkAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 15; i++)
	{
		images.pushBack(_armedNormalZombieCache->getSpriteFrameByName(StringUtils::format("BucketheadZombie_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 15);
	this->_bucketheadZombieWalkAction = RepeatForever::create(Animate::create(_animation));
	this->_bucketheadZombieWalkAction->setTag(11);
	return this->_bucketheadZombieWalkAction;
}

RepeatForever * NormalZombieSprite::bucketheadZombieAttackAnimation()
{
	Vector<SpriteFrame*> images;
	for (int i = 1; i <= 11; i++)
	{
		images.pushBack(_armedNormalZombieCache->getSpriteFrameByName(StringUtils::format("BucketheadZombieAttack_%d.png", i)));
	}
	Animation* _animation = Animation::createWithSpriteFrames(images, 1.f / 11);
	this->_bucketheadZombieAttackAction = RepeatForever::create(Animate::create(_animation));
	this->_bucketheadZombieAttackAction->setTag(12);
	return this->_bucketheadZombieAttackAction;
}

void NormalZombieSprite::startMusic()
{
	const int random = rand() % 3;
	if(random == 0)
		_effectMusicID = SimpleAudioEngine::getInstance()->playEffect("res/music/zombieChomp.wma", true);
	else if(random == 1)
		_effectMusicID = SimpleAudioEngine::getInstance()->playEffect("res/music/zombieChomp2.wma", true);
	else
		_effectMusicID = SimpleAudioEngine::getInstance()->playEffect("res/music/zombieChomp3.wma", true);
}

void NormalZombieSprite::stopMusic()
{
	SimpleAudioEngine::getInstance()->stopEffect(_effectMusicID);
}


