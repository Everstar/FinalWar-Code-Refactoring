#include "Donggua.h"

Donggua* Donggua::Instance = new Donggua();

Donggua::Donggua()
{
}

bool Donggua::init()
{
	this->BindSprite(Sprite::createWithSpriteFrameName(PATH_MONSTER_DONGGUA));
	this->setScale(0.18f);
	this->SetATK(100);
	this->SetHP(500);
	this->type = MonsterType::DONGGUA;
	return true;
}

Monster* Donggua::clone()
{
	Donggua* self = new Donggua();
	self->init();
	return self;
}