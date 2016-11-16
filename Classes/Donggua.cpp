#include "Donggua.h"

Donggua::Donggua()
{
}

bool Donggua::init()
{
	this->setScale(0.18f);
	this->SetATK(100);
	this->SetHP(500);
	return true;
}