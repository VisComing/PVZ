#pragma once
#include "cocos2d.h"
#include "BulletSprite.h"
USING_NS_CC;

class BulletLayer : public Layer
{
public:
	CREATE_FUNC(BulletLayer);
	BulletLayer();
	~BulletLayer();
	virtual bool init();
	BulletSprite* _bulletSprite;
	void initBulletSprite(float dlt);
	void bulletMoveWay();
	void removeBullet(Node*);

	Vector<Sprite*> _bulletVector;
};