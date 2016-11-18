#include "Banana.h"

Banana* Banana::Instance = new Banana();

Banana::Banana()
{
}

bool Banana::init()
{
	this->BindSprite(Sprite::createWithSpriteFrameName(PATH_MONSTER_BANANA));
	this->setScale(0.18f);
	this->SetATK(40);
	this->SetHP(200);
	this->type = MonsterType::BANANA;
	return true;
}

Monster* Banana::clone()
{
	Banana* self = new Banana();
	self->init();
	return self;
}