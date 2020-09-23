#include "ZombieBaseClass.h"
ZombieBaseClass::ZombieBaseClass()
{

}
ZombieBaseClass::~ZombieBaseClass()
{

}
bool ZombieBaseClass::init()
{
	if (!Sprite::init()) return false;

	return true;
}