#include "CardSprite.h"

CardSprite::CardSprite()
{
	
}

CardSprite::~CardSprite()
{
}

bool CardSprite::init()
{

	if (!CardBaseSprite::initWithFile("res/Peashooter.png"))//�������ĳ�ʼ������������ʹ����ֱ�ӳ�Ϊһ������
		//������Ҫ��������ӽڵ㾫�飬ע�ⲻ��Ҫcreate�����ڵ��ø���ʹcreate��  2020/9/24/20��40
	{
		return false;
	}
	return true;
}
