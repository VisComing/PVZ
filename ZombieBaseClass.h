#pragma once
#include "cocos2d.h"
USING_NS_CC;

class ZombieBaseClass : public Sprite
{
public:
	CREATE_FUNC(ZombieBaseClass);
	ZombieBaseClass();
	~ZombieBaseClass();
	virtual bool init();
	SpriteFrameCache* _normalZombieCache;
	int _hp;
	int _position[2];//��ʬ��λ��,��һ����ʾ�ڼ��У���9�У����ڶ�����ʾ�ڼ��У���5�У�
};